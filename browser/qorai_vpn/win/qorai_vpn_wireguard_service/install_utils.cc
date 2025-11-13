/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_service/install_utils.h"

#include <windows.h>
#include <winerror.h>
#include <winnt.h>
#include <winsvc.h>
#include <winuser.h>

#include <ios>

#include "base/base_paths.h"
#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/logging.h"
#include "base/path_service.h"
#include "base/win/registry.h"
#include "base/win/windows_types.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/qorai_vpn_helper_constants.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/qorai_vpn_helper_utils.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_service/service/wireguard_tunnel_service.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_service/status_tray/qorai_vpn_tray_command_ids.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_service/status_tray/status_icon/constants.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_service/status_tray/status_icon/icon_utils.h"
#include "qorai/browser/qorai_vpn/win/service_constants.h"
#include "qorai/browser/qorai_vpn/win/service_details.h"
#include "qorai/browser/qorai_vpn/win/storage_utils.h"
#include "qorai/components/qorai_vpn/common/win/scoped_sc_handle.h"
#include "qorai/components/qorai_vpn/common/win/utils.h"
#include "chrome/installer/util/install_service_work_item.h"

namespace qorai_vpn {

namespace {

constexpr wchar_t kAutoRunKeyPath[] =
    L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";

bool RemoveWireguardConfigDirectory(const base::FilePath& last_used_config) {
  auto wireguard_config_folder = last_used_config.DirName();
  if (wireguard_config_folder.empty() ||
      !base::PathExists(wireguard_config_folder)) {
    return true;
  }

  return base::DeletePathRecursively(wireguard_config_folder);
}

void AddToStartup(const std::wstring& value,
                  const base::CommandLine& command_line) {
  base::win::RegKey key(HKEY_LOCAL_MACHINE, kAutoRunKeyPath, KEY_WRITE);
  if (!key.Valid()) {
    VLOG(1) << "Failed to write wireguard service to startup";
    return;
  }
  key.WriteValue(value.c_str(), command_line.GetCommandLineString().c_str());
}

void RemoveFromStartup(const std::wstring& value) {
  base::win::RegKey key(HKEY_LOCAL_MACHINE, kAutoRunKeyPath, KEY_WRITE);
  if (!key.Valid()) {
    VLOG(1) << "Failed to write wireguard service to startup";
    return;
  }
  key.DeleteValue(value.c_str());
}

// Microsoft-Windows-NetworkProfile
// fbcfac3f-8459-419f-8e48-1f0b49cdb85e
constexpr GUID kNetworkProfileGUID = {
    0xfbcfac3f,
    0x8459,
    0x419f,
    {0x8e, 0x48, 0x1f, 0x0b, 0x49, 0xcd, 0xb8, 0x5e}};

bool SetServiceTriggerForVPNConnection(SC_HANDLE hService,
                                       const std::wstring& qorai_vpn_entry) {
  std::wstring qorai_vpn_entry_with_null(qorai_vpn_entry);
  qorai_vpn_entry_with_null += L'\0';
  // Allocate and set the SERVICE_TRIGGER_SPECIFIC_DATA_ITEM structure
  SERVICE_TRIGGER_SPECIFIC_DATA_ITEM deviceData = {0};
  deviceData.dwDataType = SERVICE_TRIGGER_DATA_TYPE_STRING;
  // Exclude EOL
  deviceData.cbData = qorai_vpn_entry_with_null.size() *
                      sizeof(qorai_vpn_entry_with_null.front());
  deviceData.pData = (PBYTE)qorai_vpn_entry_with_null.c_str();
  // Allocate and set the SERVICE_TRIGGER structure
  SERVICE_TRIGGER serviceTrigger = {0};
  serviceTrigger.dwTriggerType = SERVICE_TRIGGER_TYPE_CUSTOM;
  serviceTrigger.dwAction = SERVICE_TRIGGER_ACTION_SERVICE_START;
  serviceTrigger.pTriggerSubtype = const_cast<GUID*>(&kNetworkProfileGUID);
  serviceTrigger.cDataItems = 1;
  serviceTrigger.pDataItems = &deviceData;

  // Allocate and set the SERVICE_TRIGGER_INFO structure
  SERVICE_TRIGGER_INFO serviceTriggerInfo = {0};
  serviceTriggerInfo.cTriggers = 1;
  serviceTriggerInfo.pTriggers = &serviceTrigger;

  // Call ChangeServiceConfig2 with the SERVICE_CONFIG_TRIGGER_INFO level
  // and pass to it the address of the SERVICE_TRIGGER_INFO structure
  return ChangeServiceConfig2(hService, SERVICE_CONFIG_TRIGGER_INFO,
                              &serviceTriggerInfo);
}

bool ConfigureServiceAutoRestart(const std::wstring& service_name,
                                 const std::wstring& qorai_vpn_entry) {
  ScopedScHandle scm(::OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT));
  if (!scm.IsValid()) {
    VLOG(1) << "::OpenSCManager failed. service_name: " << service_name
            << ", error: " << std::hex << HRESULTFromLastError();
    return false;
  }
  ScopedScHandle service(
      ::OpenService(scm.Get(), service_name.c_str(), SERVICE_ALL_ACCESS));
  if (!service.IsValid()) {
    VLOG(1) << "::OpenService failed. service_name: " << service_name
            << ", error: " << std::hex << HRESULTFromLastError();
    return false;
  }

  if (!qorai_vpn::SetServiceFailureActions(service.Get())) {
    VLOG(1) << "SetServiceFailureActions failed:" << std::hex
            << HRESULTFromLastError();
    return false;
  }
  if (!SetServiceTriggerForVPNConnection(service.Get(), qorai_vpn_entry)) {
    VLOG(1) << "SetServiceTriggerForVPNConnection failed:" << std::hex
            << HRESULTFromLastError();
    return false;
  }
  return true;
}

base::FilePath GetQorAIVpnHelperServicePath(const base::FilePath& root_dir) {
  return root_dir.Append(qorai_vpn::kQorAIVPNHelperExecutable);
}

}  // namespace

bool ConfigureQorAIWireguardService(const std::wstring& service_name) {
  ScopedScHandle scm(::OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS));
  if (!scm.IsValid()) {
    VLOG(1) << "::OpenSCManager failed. service_name: " << service_name
            << ", error: " << std::hex << HRESULTFromLastError();
    return false;
  }

  ScopedScHandle service(
      ::OpenService(scm.Get(), service_name.c_str(), SERVICE_ALL_ACCESS));
  if (!service.IsValid()) {
    VLOG(1) << "Failed to create service_name: " << service_name
            << ", error: " << std::hex << HRESULTFromLastError();
    return false;
  }
  SERVICE_SID_INFO info = {};
  info.dwServiceSidType = SERVICE_SID_TYPE_UNRESTRICTED;
  if (!ChangeServiceConfig2(service.Get(), SERVICE_CONFIG_SERVICE_SID_INFO,
                            &info)) {
    VLOG(1) << "ChangeServiceConfig2 failed:" << std::hex
            << HRESULTFromLastError();
    return false;
  }
  return true;
}

// Installs QorAI VPN Wireguard Windows service and configures the service
// config.
bool InstallQorAIWireguardService(const base::FilePath& root_dir) {
  base::CommandLine service_cmd(
      GetQorAIVPNWireguardServiceExecutablePath(root_dir));
  installer::InstallServiceWorkItem install_service_work_item(
      qorai_vpn::GetQorAIVpnWireguardServiceName(),
      qorai_vpn::GetQorAIVpnWireguardServiceDisplayName(),
      qorai_vpn::GetQorAIVpnWireguardServiceDescription(), SERVICE_DEMAND_START,
      service_cmd, base::CommandLine(base::CommandLine::NO_PROGRAM),
      qorai_vpn::wireguard::GetQorAIVpnWireguardServiceRegistryStoragePath(),
      {qorai_vpn::GetQorAIVpnWireguardServiceClsid()},
      {qorai_vpn::GetQorAIVpnWireguardServiceIid()});
  install_service_work_item.set_best_effort(true);
  install_service_work_item.set_rollback_enabled(false);
  if (install_service_work_item.Do()) {
    auto success = qorai_vpn::ConfigureQorAIWireguardService(
        qorai_vpn::GetQorAIVpnWireguardServiceName());
    if (success) {
      service_cmd.AppendSwitch(
          qorai_vpn::kQorAIVpnWireguardServiceInteractiveSwitchName);
      AddToStartup(qorai_vpn::GetQorAIVpnWireguardServiceName().c_str(),
                   service_cmd);
    }
    return success;
  }
  return false;
}

// Uninstalling and clearing QorAI VPN service data.
bool UninstallQorAIWireguardService() {
  qorai_vpn::wireguard::RemoveExistingWireguardService();
  auto last_used_config = qorai_vpn::wireguard::GetLastUsedConfigPath();
  if (last_used_config.has_value() &&
      !RemoveWireguardConfigDirectory(last_used_config.value())) {
    LOG(WARNING) << "Failed to delete config directory"
                 << last_used_config.value().DirName();
  }
  RemoveFromStartup(qorai_vpn::GetQorAIVpnWireguardServiceName().c_str());
  wireguard::RemoveStorageKey();

  if (!installer::InstallServiceWorkItem::DeleteService(
          qorai_vpn::GetQorAIVpnWireguardServiceName(),
          qorai_vpn::wireguard::
              GetQorAIVpnWireguardServiceRegistryStoragePath(),
          {}, {})) {
    LOG(WARNING) << "Failed to delete "
                 << qorai_vpn::GetQorAIVpnWireguardServiceName();
    return false;
  }
  return true;
}

bool UninstallStatusTrayIcon() {
  auto* hWnd = GetQorAIVpnStatusTrayIconHWND();
  if (!hWnd) {
    return true;
  }

  return SendMessage(hWnd,
                     RegisterWindowMessage(kQorAIVpnStatusTrayMessageName),
                     IDC_QORAI_VPN_TRAY_EXIT, 0) == TRUE;
}

bool InstallQorAIVPNHelperService(const base::FilePath& root_dir) {
  base::CommandLine service_cmd(GetQorAIVpnHelperServicePath(root_dir));
  installer::InstallServiceWorkItem install_service_work_item(
      qorai_vpn::GetQorAIVpnHelperServiceName(),
      qorai_vpn::GetQorAIVpnHelperServiceDisplayName(),
      qorai_vpn::GetQorAIVpnHelperServiceDescription(), SERVICE_DEMAND_START,
      service_cmd, base::CommandLine(base::CommandLine::NO_PROGRAM),
      GetQorAIVpnHelperRegistryStoragePath(), {}, {});
  install_service_work_item.set_best_effort(true);
  install_service_work_item.set_rollback_enabled(false);
  if (install_service_work_item.Do()) {
    auto success =
        ConfigureServiceAutoRestart(qorai_vpn::GetQorAIVpnHelperServiceName(),
                                    qorai_vpn::GetQorAIVPNConnectionName());
    return success;
  }
  return false;
}

}  // namespace qorai_vpn
