/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/sidebar/sidebar_web_panel_controller.h"

#include "qorai/browser/ui/sidebar/sidebar_utils.h"
#include "qorai/browser/ui/views/frame/split_view/qorai_multi_contents_view.h"
#include "chrome/browser/ui/views/frame/browser_view.h"

namespace sidebar {

SidebarWebPanelController::SidebarWebPanelController(BrowserView& browser_view)
    : browser_view_(browser_view) {
  CHECK(IsWebPanelFeatureEnabled());
}

SidebarWebPanelController::~SidebarWebPanelController() = default;

void SidebarWebPanelController::OpenWebPanel(const SidebarItem& item) {
  GetMultiContentsView()->SetWebPanelVisible(true);
}

void SidebarWebPanelController::CloseWebPanel() {
  GetMultiContentsView()->SetWebPanelVisible(false);
}

bool SidebarWebPanelController::IsShowingWebPanel() const {
  return GetMultiContentsView()->IsWebPanelVisible();
}

QoraiMultiContentsView* SidebarWebPanelController::GetMultiContentsView() {
  return const_cast<QoraiMultiContentsView*>(
      std::as_const(*this).GetMultiContentsView());
}

const QoraiMultiContentsView* SidebarWebPanelController::GetMultiContentsView()
    const {
  return static_cast<QoraiMultiContentsView*>(
      browser_view_->multi_contents_view());
}

}  // namespace sidebar
