/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_TOOLBAR_QORAI_VPN_TOGGLE_BUTTON_H_
#define QORAI_BROWSER_UI_VIEWS_TOOLBAR_QORAI_VPN_TOGGLE_BUTTON_H_

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service_observer.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/controls/button/toggle_button.h"

namespace qorai_vpn {
class QoraiVpnService;
}  // namespace qorai_vpn

class Browser;

class QoraiVPNToggleButton : public views::ToggleButton,
                             public qorai_vpn::QoraiVPNServiceObserver {
  METADATA_HEADER(QoraiVPNToggleButton, views::ToggleButton)
 public:
  explicit QoraiVPNToggleButton(Browser* browser);
  ~QoraiVPNToggleButton() override;

  QoraiVPNToggleButton(const QoraiVPNToggleButton&) = delete;
  QoraiVPNToggleButton& operator=(const QoraiVPNToggleButton&) = delete;

 private:
  // QoraiVPNServiceObserver overrides:
  void OnConnectionStateChanged(
      qorai_vpn::mojom::ConnectionState state) override;

  void OnButtonPressed(const ui::Event& event);
  void UpdateState();

  raw_ptr<Browser> browser_ = nullptr;
  raw_ptr<qorai_vpn::QoraiVpnService> service_ = nullptr;
};

#endif  // QORAI_BROWSER_UI_VIEWS_TOOLBAR_QORAI_VPN_TOGGLE_BUTTON_H_
