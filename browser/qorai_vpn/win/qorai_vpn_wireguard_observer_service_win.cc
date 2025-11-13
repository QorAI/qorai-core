/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_observer_service_win.h"

#include "base/logging.h"
#include "qorai/browser/qorai_vpn/win/storage_utils.h"
#include "qorai/browser/ui/browser_dialogs.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "chrome/browser/browser_process.h"

namespace qorai_vpn {

QoraiVpnWireguardObserverService::QoraiVpnWireguardObserverService() = default;

QoraiVpnWireguardObserverService::~QoraiVpnWireguardObserverService() = default;

void QoraiVpnWireguardObserverService::ShowFallbackDialog() {
  if (dialog_callback_) {
    dialog_callback_.Run();
    return;
  }
  qorai::ShowQoraiVpnIKEv2FallbackDialog();
}

void QoraiVpnWireguardObserverService::OnConnectionStateChanged(
    qorai_vpn::mojom::ConnectionState state) {
  // Check because WG settings could be changed in runtime.
  if (!qorai_vpn::IsQoraiVPNWireguardEnabled(
          g_browser_process->local_state())) {
    return;
  }

  VLOG(2) << __func__ << state;
  if (state == qorai_vpn::mojom::ConnectionState::DISCONNECTED ||
      state == qorai_vpn::mojom::ConnectionState::CONNECT_FAILED) {
    if (ShouldShowFallbackDialog()) {
      ShowFallbackDialog();
    }
  }
}

bool QoraiVpnWireguardObserverService::ShouldShowFallbackDialog() const {
  if (should_fallback_for_testing_.has_value()) {
    return should_fallback_for_testing_.value();
  }

  return ShouldFallbackToIKEv2();
}

}  // namespace qorai_vpn
