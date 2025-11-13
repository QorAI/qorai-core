/* Copyright (c) 2024 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_SERVICE_DELEGATE_WIN_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_SERVICE_DELEGATE_WIN_H_

#include "qorai/components/qorai_vpn/browser/qorai_vpn_service_delegate.h"

namespace qorai_vpn {

class QorAIVPNServiceDelegateWin : public QorAIVPNServiceDelegate {
 public:
  QorAIVPNServiceDelegateWin();
  ~QorAIVPNServiceDelegateWin() override;

  QorAIVPNServiceDelegateWin(const QorAIVPNServiceDelegateWin&) = delete;
  QorAIVPNServiceDelegateWin& operator=(const QorAIVPNServiceDelegateWin&) =
      delete;

  void WriteConnectionState(mojom::ConnectionState state) override;
  void ShowQorAIVpnStatusTrayIcon() override;
};

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_SERVICE_DELEGATE_WIN_H_
