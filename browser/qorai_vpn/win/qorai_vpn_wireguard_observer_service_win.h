/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_OBSERVER_SERVICE_WIN_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_OBSERVER_SERVICE_WIN_H_

#include <optional>
#include <utility>

#include "qorai/components/qorai_vpn/browser/qorai_vpn_service_observer.h"
#include "components/keyed_service/core/keyed_service.h"

namespace qorai_vpn {

class QoraiVpnWireguardObserverService
    : public qorai_vpn::QoraiVPNServiceObserver,
      public KeyedService {
 public:
  QoraiVpnWireguardObserverService();
  ~QoraiVpnWireguardObserverService() override;
  QoraiVpnWireguardObserverService(const QoraiVpnWireguardObserverService&) =
      delete;
  QoraiVpnWireguardObserverService operator=(
      const QoraiVpnWireguardObserverService&) = delete;

  // qorai_vpn::QoraiVPNServiceObserver
  void OnConnectionStateChanged(
      qorai_vpn::mojom::ConnectionState state) override;

 private:
  friend class QoraiVpnWireguardObserverServiceUnitTest;

  void SetDialogCallbackForTesting(base::RepeatingClosure callback) {
    dialog_callback_ = std::move(callback);
  }

  void SetFallbackForTesting(bool should_fallback_for_testing) {
    should_fallback_for_testing_ = should_fallback_for_testing;
  }

  void ShowFallbackDialog();
  bool ShouldShowFallbackDialog() const;

  std::optional<bool> should_fallback_for_testing_;
  base::RepeatingClosure dialog_callback_;
};

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_OBSERVER_SERVICE_WIN_H_
