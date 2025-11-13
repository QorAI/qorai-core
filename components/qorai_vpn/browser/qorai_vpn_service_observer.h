/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_VPN_BROWSER_QORAI_VPN_SERVICE_OBSERVER_H_
#define QORAI_COMPONENTS_QORAI_VPN_BROWSER_QORAI_VPN_SERVICE_OBSERVER_H_

#include <optional>
#include <string>

#include "qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.h"
#include "build/build_config.h"
#include "mojo/public/cpp/bindings/receiver.h"

namespace qorai_vpn {

class QoraiVpnService;

class QoraiVPNServiceObserver : public mojom::ServiceObserver {
 public:
  QoraiVPNServiceObserver();
  ~QoraiVPNServiceObserver() override;
  QoraiVPNServiceObserver(const QoraiVPNServiceObserver&) = delete;
  QoraiVPNServiceObserver& operator=(const QoraiVPNServiceObserver&) = delete;

  void Observe(QoraiVpnService* service);

  // mojom::ServiceObserver overrides:
  void OnPurchasedStateChanged(
      mojom::PurchasedState state,
      const std::optional<std::string>& description) override {}
#if !BUILDFLAG(IS_ANDROID)
  void OnConnectionStateChanged(mojom::ConnectionState state) override {}
  void OnSelectedRegionChanged(mojom::RegionPtr region) override {}
  void OnSmartProxyRoutingStateChanged(bool enabled) override {}
#endif  // !BUILDFLAG(IS_ANDROID)

 private:
  mojo::Receiver<mojom::ServiceObserver> receiver_{this};
};

}  // namespace qorai_vpn

#endif  // QORAI_COMPONENTS_QORAI_VPN_BROWSER_QORAI_VPN_SERVICE_OBSERVER_H_
