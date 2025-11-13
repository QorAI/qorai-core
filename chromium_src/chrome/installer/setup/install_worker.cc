/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/installer/setup/install_worker.h"

#include <shlobj.h>

#include "base/check.h"
#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "base/logging.h"
#include "base/process/launch.h"
#include "base/process/process.h"
#include "base/version.h"
#include "base/win/registry.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "build/buildflag.h"
#include "chrome/install_static/install_util.h"
#include "chrome/installer/setup/setup_util.h"
#include "chrome/installer/util/callback_work_item.h"
#include "chrome/installer/util/install_service_work_item.h"
#include "chrome/installer/util/work_item_list.h"

#if defined(OFFICIAL_BUILD)
// clang-format off
// NOLINTBEGIN(sort-order)
#include "chrome/install_static/buildflags.h"
#include "chrome/install_static/install_constants.h"
#include "chrome/install_static/qorai_stash_google_update_integration.h"
#define BUILDFLAG_INTERNAL_USE_GOOGLE_UPDATE_INTEGRATION() (1)
// NOLINTEND(sort-order)
// clang-format on
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/qorai_vpn_helper_constants.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/qorai_vpn_helper_utils.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_service/install_utils.h"
#include "qorai/browser/qorai_vpn/win/wireguard_utils_win.h"

namespace {

// delete `QoraiVpnWireguardService` from services and remove the tray icon.
bool UninstallQoraiVPNWireguardService(const CallbackWorkItem&) {
  // Safe to ignore result as this is being called during installation.
  // If false is returned, it will abort the installation.
  qorai_vpn::UninstallQoraiWireguardService() &&
      qorai_vpn::UninstallStatusTrayIcon();
  return true;
}

// Qorai 1.50.114+ would register `QoraiVpnService` for system level installs.
//
// This change removes the service if it exists. We'll be updating the browser
// to install the services post-purchase (if possible) when the user has
// purchased Qorai VPN and has credentials or when VPN is used.
//
// See https://github.com/qorai/qorai-browser/issues/33726 for more info
void AddUninstallVpnServiceWorkItems() {
  DCHECK(::IsUserAnAdmin());
  // delete `QoraiVpnService` from services
  if (!installer::InstallServiceWorkItem::DeleteService(
          qorai_vpn::GetQoraiVpnHelperServiceName(),
          qorai_vpn::GetQoraiVpnHelperRegistryStoragePath(), {}, {})) {
    VLOG(1) << "Failed to delete " << qorai_vpn::GetQoraiVpnHelperServiceName();
  }
}

// Qorai 1.57.47+ would register `QoraiVpnWireguardService` for system level
// installs.
//
// This change removes the service if it exists. We'll be updating the browser
// to install the services post-purchase (if possible) when the user has
// purchased Qorai VPN and has credentials or when VPN is used.
//
// See https://github.com/qorai/qorai-browser/issues/33726 for more info
void AddUninstallWireguardServiceWorkItems(WorkItemList* list) {
  DCHECK(::IsUserAnAdmin());
  list->AddCallbackWorkItem(base::BindOnce(&UninstallQoraiVPNWireguardService),
                            base::NullCallback());
}

}  // namespace

namespace installer {

// We can consider removing this code and the registry key sometime in the
// future once enough time has gone by and we're confident folks have ran this
// cleanup. This same service cleanup happens on uninstall.
//
// For more info see https://github.com/qorai/qorai-browser/issues/33726
bool OneTimeVpnServiceCleanup(const base::FilePath& target_path,
                              const base::Version& new_version,
                              WorkItemList* install_list,
                              bool is_test) {
  // Check registry for `ran` value.
  // Only run the clean up logic if this hasn't ran yet.
  base::win::RegKey key;
  LONG rv = key.Create(
      HKEY_LOCAL_MACHINE,
      qorai_vpn::GetQoraiVpnOneTimeServiceCleanupStoragePath().c_str(),
      KEY_ALL_ACCESS);
  if (rv != ERROR_SUCCESS) {
    VLOG(1) << "Failed to open registry key:"
            << qorai_vpn::GetQoraiVpnOneTimeServiceCleanupStoragePath() << "\n"
            << logging::SystemErrorCodeToString(rv);
    return false;
  }

  if (!key.Valid()) {
    VLOG(1) << "Registry key not valid:"
            << qorai_vpn::GetQoraiVpnOneTimeServiceCleanupStoragePath();
    return false;
  }

  DWORD cleanup_ran = 0;
  if (key.ReadValueDW(qorai_vpn::kQoraiVpnOneTimeServiceCleanupValue,
                      &cleanup_ran) == ERROR_SUCCESS) {
    if (cleanup_ran == 1) {
      VLOG(1) << "OneTimeVpnServiceCleanup has already ran; skipping";
      return false;
    }
  }

  // If is_test=true, the removal won't happen. Default is false.
  // See chromium_src/chrome/installer/setup/install_worker_unittest.cc
  if (!is_test) {
    AddUninstallWireguardServiceWorkItems(install_list);
    AddUninstallVpnServiceWorkItems();
  }

  // Write registry value
  cleanup_ran = 1;
  rv = key.WriteValue(qorai_vpn::kQoraiVpnOneTimeServiceCleanupValue,
                      &cleanup_ran, REG_DWORD, sizeof(DWORD));
  if (rv != ERROR_SUCCESS) {
    VLOG(1) << "Failed to write registry key value: "
            << qorai_vpn::GetQoraiVpnOneTimeServiceCleanupStoragePath() << ":"
            << qorai_vpn::kQoraiVpnOneTimeServiceCleanupValue << "\n"
            << logging::SystemErrorCodeToString(rv);
  }
  return true;
}

void UpdateQoraiVpn(const base::FilePath& target_path,
                    const base::Version& new_version,
                    WorkItemList* install_list) {
  // When one time cleanup happens, we don't want to install the services at
  // that time. Service will be installed at the time of purchase.
  if (OneTimeVpnServiceCleanup(target_path, new_version, install_list)) {
    return;
  }

  // If the VPN service is installed, we should update installed services to
  // make it have latest executable path.
  if (qorai_vpn::IsQoraiVPNHelperServiceInstalled()) {
    install_list->AddCallbackWorkItem(
        base::BindOnce(
            [](const base::FilePath& target_path, const CallbackWorkItem&) {
              return qorai_vpn::InstallQoraiVPNHelperService(target_path);
            },
            target_path.AppendASCII(new_version.GetString())),
        base::DoNothing());
  }

  if (qorai_vpn::wireguard::IsWireguardServiceInstalled()) {
    install_list->AddCallbackWorkItem(
        base::BindOnce(
            [](const base::FilePath& target_path, const CallbackWorkItem&) {
              return qorai_vpn::InstallQoraiWireguardService(target_path);
            },
            target_path.AppendASCII(new_version.GetString())),
        base::DoNothing());
  }
}

}  // namespace installer

#define AddUpdateDowngradeVersionItem                     \
  UpdateQoraiVpn(target_path, new_version, install_list); \
  AddUpdateDowngradeVersionItem

#endif  // BUILDFLAG(ENABLE_QORAI_VPN)

#include <chrome/installer/setup/install_worker.cc>
#if BUILDFLAG(ENABLE_QORAI_VPN)
#undef AddUpdateDowngradeVersionItem
#endif  // BUILDFLAG(ENABLE_QORAI_VPN)
#if defined(OFFICIAL_BUILD)
#include "chrome/install_static/qorai_restore_google_update_integration.h"
#endif
