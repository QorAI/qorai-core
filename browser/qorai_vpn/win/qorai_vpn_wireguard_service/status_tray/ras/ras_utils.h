/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_STATUS_TRAY_RAS_RAS_UTILS_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_STATUS_TRAY_RAS_RAS_UTILS_H_

namespace qorai_vpn {
namespace ras {

bool IsRasConnected();
bool ConnectRasEntry();
bool DisconnectRasEntry();

}  // namespace ras
}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_STATUS_TRAY_RAS_RAS_UTILS_H_
