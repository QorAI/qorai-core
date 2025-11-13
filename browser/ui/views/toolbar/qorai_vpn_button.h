/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_TOOLBAR_QORAI_VPN_BUTTON_H_
#define QORAI_BROWSER_UI_VIEWS_TOOLBAR_QORAI_VPN_BUTTON_H_

#include <memory>
#include <optional>
#include <string>

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service_observer.h"
#include "chrome/browser/ui/views/toolbar/toolbar_button.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/controls/button/menu_button_controller.h"

namespace qorai_vpn {
class QoraiVpnService;
class QoraiVpnButtonUnitTest;
}  // namespace qorai_vpn

namespace views {
class Border;
}  // namespace views

class Browser;

class QoraiVPNButton : public ToolbarButton,
                       public qorai_vpn::QoraiVPNServiceObserver {
  METADATA_HEADER(QoraiVPNButton, ToolbarButton)
 public:

  explicit QoraiVPNButton(Browser* browser);
  ~QoraiVPNButton() override;

  QoraiVPNButton(const QoraiVPNButton&) = delete;
  QoraiVPNButton& operator=(const QoraiVPNButton&) = delete;

  // QoraiVPNServiceObserver overrides:
  void OnConnectionStateChanged(
      qorai_vpn::mojom::ConnectionState state) override;
  void OnPurchasedStateChanged(
      qorai_vpn::mojom::PurchasedState state,
      const std::optional<std::string>& description) override;

 private:
  friend class qorai_vpn::QoraiVpnButtonUnitTest;

  // ToolbarButton overrides:
  void UpdateColorsAndInsets() override;
  std::u16string GetRenderedTooltipText(const gfx::Point& p) const override;
  void OnThemeChanged() override;
  void InkDropRippleAnimationEnded(views::InkDropState state) override;

  void SetVpnConnectionStateForTesting(
      qorai_vpn::mojom::ConnectionState state) {
    connection_state_for_testing_ = state;
  }
  qorai_vpn::mojom::ConnectionState GetVpnConnectionState() const;
  bool IsErrorState() const { return is_error_state_; }
  bool IsConnected() const;
  bool IsConnectError() const;
  bool IsPurchased() const;
  std::unique_ptr<views::Border> GetBorder(SkColor border_color) const;
  void OnButtonPressed(const ui::Event& event);
  void UpdateButtonState();
  SkColor GetIconColor();
  SkColor GetBadgeColor();
  const gfx::VectorIcon& GetBadgeIcon();

  bool is_error_state_ = false;
  bool is_connected_ = false;
  std::optional<qorai_vpn::mojom::ConnectionState>
      connection_state_for_testing_;
  raw_ptr<Browser, DanglingUntriaged> browser_ = nullptr;
  raw_ptr<qorai_vpn::QoraiVpnService, DanglingUntriaged> service_ = nullptr;
  raw_ptr<views::MenuButtonController> menu_button_controller_ = nullptr;
  base::WeakPtrFactory<QoraiVPNButton> weak_ptr_factory_{this};
};

#endif  // QORAI_BROWSER_UI_VIEWS_TOOLBAR_QORAI_VPN_BUTTON_H_
