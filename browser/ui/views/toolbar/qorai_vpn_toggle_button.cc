/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/toolbar/qorai_vpn_toggle_button.h"

#include <utility>

#include "base/check.h"
#include "base/functional/bind.h"
#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/color/color_id.h"

using ConnectionState = qorai_vpn::mojom::ConnectionState;
using PurchasedState = qorai_vpn::mojom::PurchasedState;

QoraiVPNToggleButton::QoraiVPNToggleButton(Browser* browser)
    : browser_(browser),
      service_(qorai_vpn::QoraiVpnServiceFactory::GetForProfile(
          browser_->profile())) {
  CHECK(service_);

  Observe(service_);

  SetCallback(base::BindRepeating(&QoraiVPNToggleButton::OnButtonPressed,
                                  base::Unretained(this)));
  UpdateState();

  if (const ui::ColorProvider* provider =
          BrowserView::GetBrowserViewForBrowser(browser_)->GetColorProvider()) {
    SetThumbOnColor(provider->GetColor(ui::kColorToggleButtonThumbOn));
    SetThumbOffColor(provider->GetColor(ui::kColorToggleButtonThumbOff));
    SetTrackOnColor(provider->GetColor(ui::kColorToggleButtonTrackOn));
    SetTrackOffColor(provider->GetColor(ui::kColorToggleButtonTrackOff));
  }

  // TODO(simonhong): Re-visit this name.
  SetAccessibleName(
      l10n_util::GetStringUTF16(IDS_QORAI_VPN_TOGGLE_MENU_ITEM_TEXT));
}

QoraiVPNToggleButton::~QoraiVPNToggleButton() = default;

void QoraiVPNToggleButton::OnConnectionStateChanged(ConnectionState state) {
  UpdateState();
}

void QoraiVPNToggleButton::OnButtonPressed(const ui::Event& event) {
  service_->ToggleConnection();
}

void QoraiVPNToggleButton::UpdateState() {
  const auto state = service_->GetConnectionState();
  bool is_on = (state == ConnectionState::CONNECTING ||
                state == ConnectionState::CONNECTED);
  SetIsOn(is_on);
}

BEGIN_METADATA(QoraiVPNToggleButton)
END_METADATA
