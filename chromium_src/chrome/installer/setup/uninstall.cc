/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/logging.h"
#include "base/process/launch.h"
#include "base/process/process.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/installer/util/qorai_shell_util.h"
#include "chrome/installer/setup/modify_params.h"
#include "chrome/installer/util/registry_util.h"
#include "chrome/installer/util/shell_util.h"
#include "chrome/installer/util/util_constants.h"
#include "chrome/installer/util/work_item.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/qorai_vpn_helper_constants.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/qorai_vpn_helper_utils.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_service/install_utils.h"
#include "qorai/browser/qorai_vpn/win/service_details.h"
#include "qorai/components/qorai_vpn/browser/connection/ikev2/win/ras_utils.h"
#endif
#define UninstallProduct UninstallProduct_ChromiumImpl

#include <chrome/installer/setup/uninstall.cc>

#undef UninstallProduct

namespace installer {

namespace {

void DeleteQoraiFileKeys(HKEY root) {
  // Delete Software\Classes\QoraiXXXFile.
  std::wstring reg_prog_id(ShellUtil::kRegClasses);
  reg_prog_id.push_back(base::FilePath::kSeparators[0]);
  reg_prog_id.append(GetProgIdForFileType());
  DeleteRegistryKey(root, reg_prog_id, WorkItem::kWow64Default);

  // Cleanup OpenWithList and OpenWithProgids:
  // http://msdn.microsoft.com/en-us/library/bb166549
  std::wstring file_assoc_key;
  std::wstring open_with_progids_key;
  for (int i = 0;
       UNSAFE_TODO(ShellUtil::kPotentialFileAssociations[i]) != nullptr; ++i) {
    file_assoc_key.assign(ShellUtil::kRegClasses);
    file_assoc_key.push_back(base::FilePath::kSeparators[0]);
    file_assoc_key.append(
        UNSAFE_TODO(ShellUtil::kPotentialFileAssociations[i]));
    file_assoc_key.push_back(base::FilePath::kSeparators[0]);

    open_with_progids_key.assign(file_assoc_key);
    open_with_progids_key.append(ShellUtil::kRegOpenWithProgids);
    if (ShouldUseFileTypeProgId(
            UNSAFE_TODO(ShellUtil::kPotentialFileAssociations[i]))) {
      DeleteRegistryValue(root, open_with_progids_key, WorkItem::kWow64Default,
                          GetProgIdForFileType());
    }
  }
}

}  // namespace

InstallStatus UninstallProduct(const ModifyParams& modify_params,
                               bool remove_all,
                               bool force_uninstall,
                               const base::CommandLine& cmd_line) {
  InstallStatus ret = UninstallProduct_ChromiumImpl(modify_params, remove_all,
                                                    force_uninstall, cmd_line);

  // Early return if user cancelled.
  if (ret == installer::UNINSTALL_CANCELLED) {
    return ret;
  }

  DeleteQoraiFileKeys(HKEY_CURRENT_USER);

  const auto installer_state = modify_params.installer_state;
  const base::FilePath chrome_exe(
      installer_state->target_path().Append(installer::kChromeExe));
  const std::wstring suffix(
      ShellUtil::GetCurrentInstallationSuffix(chrome_exe));
  if (installer_state->system_install() ||
      (remove_all &&
       ShellUtil::QuickIsChromeRegisteredInHKLM(chrome_exe, suffix))) {
    DeleteQoraiFileKeys(HKEY_LOCAL_MACHINE);
  }
#if BUILDFLAG(ENABLE_QORAI_VPN)
  if (installer_state->system_install()) {
    // TODO(bsclifton): move this to a method
    if (!InstallServiceWorkItem::DeleteService(
            qorai_vpn::GetQoraiVpnHelperServiceName(),
            qorai_vpn::GetQoraiVpnHelperRegistryStoragePath(), {}, {})) {
      LOG(WARNING) << "Failed to delete "
                   << qorai_vpn::GetQoraiVpnHelperServiceName();
    }

    if (!qorai_vpn::UninstallQoraiWireguardService() ||
        !qorai_vpn::UninstallStatusTrayIcon()) {
      LOG(WARNING) << "Failed to delete "
                   << qorai_vpn::GetQoraiVpnWireguardServiceName();
    }
  }
  qorai_vpn::ras::RemoveEntry(qorai_vpn::GetQoraiVPNConnectionName());
#endif

  return ret;
}

}  // namespace installer
