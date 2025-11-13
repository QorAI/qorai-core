/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_VPN_BROWSER_QORAI_VPN_SERVICE_DELEGATE_H_
#define QORAI_COMPONENTS_QORAI_VPN_BROWSER_QORAI_VPN_SERVICE_DELEGATE_H_

#include "qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.h"

namespace qorai_vpn {

class QoraiVPNServiceDelegate {
 public:
  QoraiVPNServiceDelegate() = default;
  virtual ~QoraiVPNServiceDelegate() = default;

  QoraiVPNServiceDelegate(const QoraiVPNServiceDelegate&) = delete;
  QoraiVPNServiceDelegate& operator=(const QoraiVPNServiceDelegate&) = delete;

  virtual void WriteConnectionState(mojom::ConnectionState state) = 0;
  virtual void ShowQoraiVpnStatusTrayIcon() = 0;
};

}  // namespace qorai_vpn

#endif  // QORAI_COMPONENTS_QORAI_VPN_BROWSER_QORAI_VPN_SERVICE_DELEGATE_H_
