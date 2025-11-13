/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_vpn/browser/qorai_vpn_service_observer.h"

#include <utility>

#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"

namespace qorai_vpn {

QoraiVPNServiceObserver::QoraiVPNServiceObserver() = default;

QoraiVPNServiceObserver::~QoraiVPNServiceObserver() = default;

void QoraiVPNServiceObserver::Observe(QoraiVpnService* service) {
  if (!service)
    return;

  if (service->IsQoraiVPNEnabled()) {
    mojo::PendingRemote<mojom::ServiceObserver> listener;
    receiver_.Bind(listener.InitWithNewPipeAndPassReceiver());
    service->AddObserver(std::move(listener));
  }
}

}  // namespace qorai_vpn
