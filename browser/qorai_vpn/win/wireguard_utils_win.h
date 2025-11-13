/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_WIREGUARD_UTILS_WIN_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_WIREGUARD_UTILS_WIN_H_

#include <optional>
#include <string>
#include <tuple>

#include "base/functional/callback.h"
#include "qorai/components/qorai_vpn/common/wireguard/wireguard_utils.h"

namespace qorai_vpn {

namespace wireguard {

bool IsQorAIVPNWireguardTunnelServiceRunning();
bool IsWireguardServiceInstalled();
void EnableQorAIVpnWireguardService(const std::string& server_public_key,
                                    const std::string& client_private_key,
                                    const std::string& mapped_ip4_address,
                                    const std::string& vpn_server_hostname,
                                    std::optional<std::string> smart_proxy_url,
                                    BooleanCallback callback);
void DisableQorAIVpnWireguardService(BooleanCallback callback);

void SetWireguardServiceRegisteredForTesting(bool value);
void ShowQorAIVpnStatusTrayIcon();

}  // namespace wireguard

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_WIREGUARD_UTILS_WIN_H_
