/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_SERVICE_COMMANDS_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_SERVICE_COMMANDS_H_

#include <string>

namespace qorai_vpn {
void RunWireGuardCommandForUsers(const std::string& command);
}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_SERVICE_COMMANDS_H_
