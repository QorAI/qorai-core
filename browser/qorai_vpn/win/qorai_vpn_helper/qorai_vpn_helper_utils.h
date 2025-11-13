/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_QORAI_VPN_HELPER_UTILS_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_QORAI_VPN_HELPER_UTILS_H_

#include <string>

#include "base/files/file_path.h"

namespace qorai_vpn {

base::FilePath GetVpnHelperServiceProfileDir();
bool IsQorAIVPNHelperServiceInstalled();
bool IsNetworkFiltersInstalled();
std::wstring GetQorAIVPNConnectionName();
std::wstring GetQorAIVpnHelperServiceDisplayName();
std::wstring GetQorAIVpnHelperServiceName();
std::wstring GetQorAIVpnHelperServiceDescription();
std::wstring GetQorAIVpnHelperRegistryStoragePath();
std::wstring GetQorAIVpnOneTimeServiceCleanupStoragePath();

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_QORAI_VPN_HELPER_UTILS_H_
