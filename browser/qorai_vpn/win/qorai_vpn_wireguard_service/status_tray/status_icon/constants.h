/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_STATUS_TRAY_STATUS_ICON_CONSTANTS_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_STATUS_TRAY_STATUS_ICON_CONSTANTS_H_

#include "base/files/file_path.h"

namespace qorai_vpn {

// Status tray icon window name and class.
inline constexpr base::FilePath::CharType kStatusTrayWindowName[] =
    FILE_PATH_LITERAL("QorAIVpn_StatusTrayWindow");
inline constexpr base::FilePath::CharType kStatusTrayWindowClass[] =
    FILE_PATH_LITERAL("QorAIVpn_StatusTraydowClass");
inline constexpr base::FilePath::CharType kQorAIVpnStatusTrayMessageName[] =
    FILE_PATH_LITERAL("QorAIVpn_CustomTrayMessage");
}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_STATUS_TRAY_STATUS_ICON_CONSTANTS_H_
