/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/toolbar/qorai_vpn_status_label.h"

#include <utility>

#include "base/check.h"
#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#include "qorai/browser/ui/color/qorai_color_id.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/metadata/metadata_impl_macros.h"

using ConnectionState = qorai_vpn::mojom::ConnectionState;
using PurchasedState = qorai_vpn::mojom::PurchasedState;

namespace {

int GetStringIdForConnectionState(ConnectionState state) {
  switch (state) {
    case ConnectionState::CONNECTING:
      return IDS_QORAI_VPN_STATUS_LABEL_CONNECTING;
    case ConnectionState::CONNECTED:
      return IDS_QORAI_VPN_STATUS_LABEL_CONNECTED;
    case ConnectionState::DISCONNECTING:
      return IDS_QORAI_VPN_STATUS_LABEL_DISCONNECTING;
    default:
      break;
  }
  return IDS_QORAI_VPN_STATUS_LABEL_DISCONNECTED;
}

int GetLongestStringIdForConnectionState() {
  size_t max = 0;
  int longest_string_id =
      GetStringIdForConnectionState(ConnectionState::DISCONNECTED);
  for (auto state :
       {ConnectionState::CONNECTING, ConnectionState::CONNECTED,
        ConnectionState::DISCONNECTING, ConnectionState::DISCONNECTED}) {
    auto id = GetStringIdForConnectionState(state);
    auto text = l10n_util::GetStringUTF16(id);
    if (text.length() > max) {
      max = text.length();
      longest_string_id = id;
    }
  }
  return longest_string_id;
}
}  // namespace

QoraiVPNStatusLabel::QoraiVPNStatusLabel(Browser* browser)
    : browser_(browser),
      service_(qorai_vpn::QoraiVpnServiceFactory::GetForProfile(
          browser_->profile())) {
  CHECK(service_);

  Observe(service_);
  SetAutoColorReadabilityEnabled(false);
  UpdateState();

  if (const ui::ColorProvider* provider =
          BrowserView::GetBrowserViewForBrowser(browser_)->GetColorProvider()) {
    SetEnabledColor(provider->GetColor(kColorMenuItemSubText));
  }
  longest_state_string_id_ = GetLongestStringIdForConnectionState();
}

QoraiVPNStatusLabel::~QoraiVPNStatusLabel() = default;

void QoraiVPNStatusLabel::OnConnectionStateChanged(ConnectionState state) {
  UpdateState();
}

void QoraiVPNStatusLabel::UpdateState() {
  const auto state = service_->GetConnectionState();

  SetText(l10n_util::GetStringUTF16(GetStringIdForConnectionState(state)));
}

BEGIN_METADATA(QoraiVPNStatusLabel)
END_METADATA
