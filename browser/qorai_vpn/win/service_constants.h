/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_SERVICE_CONSTANTS_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_SERVICE_CONSTANTS_H_

namespace qorai_vpn {

inline constexpr wchar_t kQorAIVpnWireguardServiceExecutable[] =
    L"qorai_vpn_wireguard_service.exe";

// Registry flag to count service launches for the fallback.
inline constexpr wchar_t kQorAIVpnWireguardCounterOfTunnelUsage[] =
    L"tunnel_launches_counter";

// Load wireguard binaries and connect to vpn using passed config.
inline constexpr char kQorAIVpnWireguardServiceConnectSwitchName[] = "connect";

// In this mode the service started on user level and expose UI interfaces
// to work with the service for a user.
inline constexpr char kQorAIVpnWireguardServiceInteractiveSwitchName[] =
    "interactive";

// Notifies users about connected state of the vpn using system notifications.
inline constexpr char kQorAIVpnWireguardServiceNotifyConnectedSwitchName[] =
    "notify-connected";

// Notifies users about disconnected state of the vpn using system
// notifications.
inline constexpr char kQorAIVpnWireguardServiceNotifyDisconnectedSwitchName[] =
    "notify-disconnected";

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_SERVICE_CONSTANTS_H_
