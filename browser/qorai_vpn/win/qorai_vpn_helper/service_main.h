/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_SERVICE_MAIN_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_SERVICE_MAIN_H_

#include <windows.h>

#include "base/functional/callback.h"
#include "base/memory/scoped_refptr.h"
#include "base/no_destructor.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/qorai_vpn_dns_delegate.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/vpn_dns_handler.h"

namespace base {
class CommandLine;
}  // namespace base

namespace qorai_vpn {

class ServiceMain : public qorai_vpn::QorAIVpnDnsDelegate {
 public:
  static ServiceMain* GetInstance();

  ServiceMain(const ServiceMain&) = delete;
  ServiceMain& operator=(const ServiceMain&) = delete;

  // This function parses the command line and selects the action routine.
  bool InitWithCommandLine(const base::CommandLine* command_line);

  // Start() is the entry point called by WinMain.
  int Start();

  // qorai_vpn::QorAIVpnDnsDelegate:
  void SignalExit() override;

 private:
  friend class base::NoDestructor<ServiceMain>;

  ServiceMain();
  ~ServiceMain();

  // This function handshakes with the service control manager and starts
  // the service.
  int RunAsService();

  // Runs the service on the service thread.
  void ServiceMainImpl();

  // Runs as a local server for testing purposes. RunInteractive returns an
  // HRESULT, not a Win32 error code.
  int RunInteractive();

  // The control handler of the service.
  static void WINAPI ServiceControlHandler(DWORD control);

  // The main service entry point.
  static void WINAPI ServiceMainEntry(DWORD argc, wchar_t* argv[]);

  // Calls ::SetServiceStatus().
  void SetServiceStatus(DWORD state);

  // Handles object registration, message loop, and unregistration. Returns
  // when all registered objects are released.
  HRESULT Run();

  // The action routine to be executed.
  int (ServiceMain::*run_routine_)();

  VpnDnsHandler dns_handler_{this};
  SERVICE_STATUS_HANDLE service_status_handle_;
  SERVICE_STATUS service_status_;
  base::OnceClosure quit_;
};

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_SERVICE_MAIN_H_
