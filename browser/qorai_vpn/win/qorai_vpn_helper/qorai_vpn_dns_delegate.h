// Copyright (c) 2022 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_QORAI_VPN_DNS_DELEGATE_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_QORAI_VPN_DNS_DELEGATE_H_

namespace qorai_vpn {

class QorAIVpnDnsDelegate {
 public:
  virtual void SignalExit() = 0;
};

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_QORAI_VPN_DNS_DELEGATE_H_
