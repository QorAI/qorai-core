// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/qorai_vpn/vpn_panel_handler.h"

#include <utility>

#include "base/check.h"
#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#include "qorai/browser/ui/webui/qorai_vpn/vpn_panel_ui.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_constants.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/browser_tabstrip.h"
#include "chrome/browser/ui/singleton_tabs.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"

namespace {

bool ShouldOpenSingletonTab(qorai_vpn::mojom::ManageURLType type) {
  return type == qorai_vpn::mojom::ManageURLType::MANAGE ||
         type == qorai_vpn::mojom::ManageURLType::PRIVACY ||
         type == qorai_vpn::mojom::ManageURLType::ABOUT_SMART_PROXY ||
         type == qorai_vpn::mojom::ManageURLType::ABOUT;
}

void ShowSingletonVPNTab(Browser* browser, const GURL& url) {
  for (auto i = 0; i < browser->tab_strip_model()->GetTabCount(); i++) {
    auto* web_contents = browser->tab_strip_model()->GetWebContentsAt(i);
    const GURL& contents_url = web_contents->GetVisibleURL();
    bool is_equal = contents_url.SchemeIs(url.scheme()) &&
                    contents_url.DomainIs(url.host()) &&
                    contents_url.path() == url.path();
    if (is_equal) {
      browser->tab_strip_model()->ActivateTabAt(i);
      return;
    }
  }
  chrome::AddTabAt(browser, url, -1, true);
}

}  // namespace

VPNPanelHandler::VPNPanelHandler(
    mojo::PendingReceiver<qorai_vpn::mojom::PanelHandler> receiver,
    VPNPanelUI* panel_controller,
    Profile* profile)
    : receiver_(this, std::move(receiver)),
      panel_controller_(panel_controller),
      profile_(profile) {}

VPNPanelHandler::~VPNPanelHandler() = default;

void VPNPanelHandler::ShowUI() {
  auto embedder = panel_controller_->embedder();
  qorai_vpn::QoraiVpnService* vpn_service =
      qorai_vpn::QoraiVpnServiceFactory::GetForProfile(profile_);
  CHECK(vpn_service);
  if (embedder) {
    embedder->ShowUI();
    vpn_service->ReloadPurchasedState();
  }
}

void VPNPanelHandler::CloseUI() {
  auto embedder = panel_controller_->embedder();
  if (embedder) {
    embedder->CloseUI();
  }
}

void VPNPanelHandler::OpenVpnUIUrl(
    qorai_vpn::mojom::ManageURLType type,
    qorai_vpn::mojom::ProductUrlsPtr product_urls) {
  auto* browser = chrome::FindLastActiveWithProfile(profile_);
  const auto url =
      qorai_vpn::GetManageURLForUIType(type, GURL(product_urls->manage));
  if (ShouldOpenSingletonTab(type)) {
    ShowSingletonVPNTab(browser, url);
  } else {
    chrome::AddTabAt(browser, url, -1, true);
  }
}

void VPNPanelHandler::OpenVpnUI(qorai_vpn::mojom::ManageURLType type) {
  qorai_vpn::QoraiVpnService* vpn_service =
      qorai_vpn::QoraiVpnServiceFactory::GetForProfile(profile_);
  CHECK(vpn_service);
  vpn_service->GetProductUrls(base::BindOnce(&VPNPanelHandler::OpenVpnUIUrl,
                                             base::Unretained(this), type));
}
