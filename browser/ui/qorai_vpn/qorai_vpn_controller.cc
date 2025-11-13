/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/qorai_vpn/qorai_vpn_controller.h"

#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#include "qorai/browser/ui/views/frame/qorai_browser_view.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "chrome/browser/ui/singleton_tabs.h"
#include "url/gurl.h"

QoraiVPNController::QoraiVPNController(BrowserView* browser_view)
    : browser_view_(browser_view) {}

QoraiVPNController::~QoraiVPNController() = default;

void QoraiVPNController::ShowQoraiVPNBubble(bool show_select) {
  GetQoraiBrowserView()->ShowQoraiVPNBubble(show_select);
}

void QoraiVPNController::OpenVPNAccountPage(
    qorai_vpn::mojom::ManageURLType type) {
  auto* browser = browser_view_->browser();
  auto* profile = browser->profile();
  auto* vpn_service = qorai_vpn::QoraiVpnServiceFactory::GetForProfile(profile);
  const auto url =
      GURL(qorai_vpn::GetManageUrl(vpn_service->GetCurrentEnvironment()));
  ShowSingletonTab(browser, qorai_vpn::GetManageURLForUIType(type, url));
}

QoraiBrowserView* QoraiVPNController::GetQoraiBrowserView() {
  return static_cast<QoraiBrowserView*>(browser_view_);
}
