// Copyright (c) 2023 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/qorai_vpn_helper_utils.h"

#include <windows.h>
#include <winerror.h>
#include <winsvc.h>
#include <winuser.h>

#include <algorithm>
#include <ios>

#include "base/check.h"
#include "base/logging.h"
#include "base/notreached.h"
#include "base/path_service.h"
#include "base/strings/utf_string_conversions.h"
#include "base/win/registry.h"
#include "base/win/windows_types.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/qorai_vpn_helper_constants.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "qorai/components/qorai_vpn/common/win/scoped_sc_handle.h"
#include "qorai/components/qorai_vpn/common/win/utils.h"
#include "chrome/install_static/install_modes.h"
#include "chrome/install_static/install_util.h"
#include "chrome/common/channel_info.h"
#include "components/version_info/channel.h"

namespace qorai_vpn {

// The service starts under system user so we save crashes to
// %PROGRAMDATA%\QorAISoftware\{service name}\Crashpad
base::FilePath GetVpnHelperServiceProfileDir() {
  std::wstring program_data =
      install_static::GetEnvironmentString(L"PROGRAMDATA");
  if (program_data.empty()) {
    return base::FilePath();
  }
  return base::FilePath(program_data)
      .Append(install_static::kCompanyPathName)
      .Append(qorai_vpn::GetQorAIVpnHelperServiceName());
}

bool IsQorAIVPNHelperServiceInstalled() {
  ScopedScHandle scm(::OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT));
  if (!scm.IsValid()) {
    VLOG(1) << "::OpenSCManager failed. service_name: "
            << qorai_vpn::GetQorAIVpnHelperServiceName()
            << ", error: " << std::hex << HRESULTFromLastError();
    return false;
  }
  ScopedScHandle service(::OpenService(
      scm.Get(), qorai_vpn::GetQorAIVpnHelperServiceName().c_str(),
      SERVICE_QUERY_STATUS));

  // Service registered and has not exceeded the number of auto-configured
  // restarts.
  return service.IsValid();
}

bool IsNetworkFiltersInstalled() {
  DCHECK(IsQorAIVPNHelperServiceInstalled());
  base::win::RegKey service_storage_key(
      HKEY_LOCAL_MACHINE, GetQorAIVpnHelperRegistryStoragePath().c_str(),
      KEY_READ);
  if (!service_storage_key.Valid()) {
    return false;
  }
  DWORD current = -1;
  if (service_storage_key.ReadValueDW(
          qorai_vpn::kQorAIVpnHelperFiltersInstalledValue, &current) !=
      ERROR_SUCCESS) {
    return false;
  }
  return current > 0;
}

std::wstring GetQorAIVPNConnectionName() {
  return base::UTF8ToWide(
      qorai_vpn::GetQorAIVPNEntryName(chrome::GetChannel()));
}

std::wstring GetQorAIVpnHelperServiceDisplayName() {
  static constexpr wchar_t kQorAIVpnServiceDisplayName[] = L" Vpn Service";
  return install_static::GetBaseAppName() + kQorAIVpnServiceDisplayName;
}

std::wstring GetQorAIVpnHelperServiceName() {
  std::wstring name = GetQorAIVpnHelperServiceDisplayName();
  std::erase_if(name, isspace);
  return name;
}

std::wstring GetQorAIVpnHelperServiceDescription() {
  return L"Protects QorAI VPN against DNS leaks with Smart Multi-Homed Name "
         L"Resolution when using IKEv2";
}

std::wstring GetQorAIVpnHelperRegistryStoragePath() {
  switch (chrome::GetChannel()) {
    case version_info::Channel::CANARY:
      return L"Software\\QorAISoftware\\QorAI\\Vpn\\HelperServiceNightly";
    case version_info::Channel::DEV:
      return L"Software\\QorAISoftware\\QorAI\\Vpn\\HelperServiceDev";
    case version_info::Channel::BETA:
      return L"Software\\QorAISoftware\\QorAI\\Vpn\\HelperServiceBeta";
    case version_info::Channel::STABLE:
      return L"Software\\QorAISoftware\\QorAI\\Vpn\\HelperService";
    case version_info::Channel::UNKNOWN:
      return L"Software\\QorAISoftware\\QorAI\\Vpn\\HelperServiceDevelopment";
  }

  NOTREACHED();
}

std::wstring GetQorAIVpnOneTimeServiceCleanupStoragePath() {
  switch (chrome::GetChannel()) {
    case version_info::Channel::CANARY:
      return L"Software\\QorAISoftware\\QorAI\\Vpn\\OneTimeServiceCleanupNightl"
             L"y";
    case version_info::Channel::DEV:
      return L"Software\\QorAISoftware\\QorAI\\Vpn\\OneTimeServiceCleanupDev";
    case version_info::Channel::BETA:
      return L"Software\\QorAISoftware\\QorAI\\Vpn\\OneTimeServiceCleanupBeta";
    case version_info::Channel::STABLE:
      return L"Software\\QorAISoftware\\QorAI\\Vpn\\OneTimeServiceCleanup";
    case version_info::Channel::UNKNOWN:
      return L"Software\\QorAISoftware\\QorAI\\Vpn\\OneTimeServiceCleanupDevelo"
             L"pment";
  }

  NOTREACHED();
}

}  // namespace qorai_vpn
