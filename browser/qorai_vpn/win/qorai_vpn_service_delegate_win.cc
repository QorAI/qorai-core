/* Copyright (c) 2024 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_vpn/win/qorai_vpn_service_delegate_win.h"

#include "qorai/browser/qorai_vpn/win/storage_utils.h"
#include "qorai/browser/qorai_vpn/win/wireguard_utils_win.h"

namespace qorai_vpn {

QorAIVPNServiceDelegateWin::QorAIVPNServiceDelegateWin() = default;

QorAIVPNServiceDelegateWin::~QorAIVPNServiceDelegateWin() = default;

void QorAIVPNServiceDelegateWin::WriteConnectionState(
    mojom::ConnectionState state) {
  ::qorai_vpn::WriteConnectionState(static_cast<int>(state));
}

void QorAIVPNServiceDelegateWin::ShowQorAIVpnStatusTrayIcon() {
  wireguard::ShowQorAIVpnStatusTrayIcon();
}

}  // namespace qorai_vpn
