/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/browser_window/public/browser_window_features.h"

#include "base/memory/ptr_util.h"
#include "base/notreached.h"
#include "qorai/browser/qorai_rewards/rewards_service_factory.h"
#include "qorai/browser/ui/qorai_browser_window.h"
#include "qorai/browser/ui/qorai_rewards/rewards_panel_coordinator.h"
#include "qorai/browser/ui/sidebar/sidebar_controller.h"
#include "qorai/browser/ui/sidebar/sidebar_utils.h"
#include "qorai/browser/ui/tabs/features.h"
#include "qorai/browser/ui/views/side_panel/playlist/playlist_side_panel_coordinator.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/playlist/core/common/features.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_window/public/browser_window_interface.h"
#include "chrome/browser/ui/views/frame/browser_view.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/ui/qorai_vpn/qorai_vpn_controller.h"
#endif

#if !BUILDFLAG(ENABLE_QORAI_VPN)
// Use stub class to avoid incomplete type build error.
class QoraiVPNController {};
#endif

BrowserWindowFeatures::BrowserWindowFeatures() = default;
BrowserWindowFeatures::~BrowserWindowFeatures() = default;

QoraiVPNController* BrowserWindowFeatures::qorai_vpn_controller() {
#if BUILDFLAG(ENABLE_QORAI_VPN)
  return qorai_vpn_controller_.get();
#else
  NOTREACHED();
#endif
}

void BrowserWindowFeatures::Init(BrowserWindowInterface* browser) {
  BrowserWindowFeatures_ChromiumImpl::Init(browser);

  if (qorai_rewards::RewardsServiceFactory::GetForProfile(
          browser->GetProfile())) {
    rewards_panel_coordinator_ =
        std::make_unique<qorai_rewards::RewardsPanelCoordinator>(browser);
  }
}

void BrowserWindowFeatures::InitPostBrowserViewConstruction(
    BrowserView* browser_view) {
  if (sidebar::CanUseSidebar(browser_view->browser())) {
    sidebar_controller_ = std::make_unique<sidebar::SidebarController>(
        browser_view->browser(), browser_view->GetProfile());
    if (base::FeatureList::IsEnabled(playlist::features::kPlaylist)) {
      playlist_side_panel_coordinator_ =
          std::make_unique<PlaylistSidePanelCoordinator>(
              browser_view->browser(), sidebar_controller_.get(),
              browser_view->GetProfile());
    }
  }

#if BUILDFLAG(ENABLE_QORAI_VPN)
  qorai_vpn_controller_ = std::make_unique<QoraiVPNController>(browser_view);
#endif

  BrowserWindowFeatures_ChromiumImpl::InitPostBrowserViewConstruction(
      browser_view);
}

void BrowserWindowFeatures::TearDownPreBrowserWindowDestruction() {
  BrowserWindowFeatures_ChromiumImpl::TearDownPreBrowserWindowDestruction();
#if BUILDFLAG(ENABLE_QORAI_VPN)
  qorai_vpn_controller_.reset();
#endif
  if (sidebar_controller_) {
    sidebar_controller_->TearDownPreBrowserWindowDestruction();
    playlist_side_panel_coordinator_.reset();
  }
}
