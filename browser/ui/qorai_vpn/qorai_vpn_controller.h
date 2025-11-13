/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_VPN_QORAI_VPN_CONTROLLER_H_
#define QORAI_BROWSER_UI_QORAI_VPN_QORAI_VPN_CONTROLLER_H_

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.h"

class QoraiBrowserView;
class BrowserView;

class QoraiVPNController {
 public:
  explicit QoraiVPNController(BrowserView* browser_view);
  ~QoraiVPNController();
  QoraiVPNController(const QoraiVPNController&) = delete;
  QoraiVPNController& operator=(const QoraiVPNController&) = delete;

  void ShowQoraiVPNBubble(bool show_select = false);
  void OpenVPNAccountPage(qorai_vpn::mojom::ManageURLType type);

 private:
  QoraiBrowserView* GetQoraiBrowserView();

  raw_ptr<BrowserView> browser_view_ = nullptr;
};

#endif  // QORAI_BROWSER_UI_QORAI_VPN_QORAI_VPN_CONTROLLER_H_
