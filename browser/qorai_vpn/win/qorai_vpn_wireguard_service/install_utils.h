/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_INSTALL_UTILS_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_INSTALL_UTILS_H_

#include <string>

#include "base/files/file_path.h"

namespace base {
class FilePath;
}  // namespace base

namespace qorai_vpn {

bool ConfigureQorAIWireguardService(const std::wstring& service_name);
bool InstallQorAIWireguardService(const base::FilePath& root_dir);
bool UninstallQorAIWireguardService();
bool UninstallStatusTrayIcon();
bool InstallQorAIVPNHelperService(const base::FilePath& root_dir);

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_INSTALL_UTILS_H_
