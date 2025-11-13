/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_QORAI_VPN_HELPER_CONSTANTS_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_QORAI_VPN_HELPER_CONSTANTS_H_

namespace qorai_vpn {

inline constexpr char kQorAIVpnHelperCrashMe[] = "crash-me";
inline constexpr wchar_t kQorAIVPNHelperExecutable[] = L"qorai_vpn_helper.exe";
inline constexpr wchar_t kQorAIVpnHelperFiltersInstalledValue[] = L"filters";
inline constexpr wchar_t kQorAIVpnOneTimeServiceCleanupValue[] = L"ran";

// Repeating interval to check the connection is live.
inline constexpr int kCheckConnectionIntervalInSeconds = 3;

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_QORAI_VPN_HELPER_CONSTANTS_H_
