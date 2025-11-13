/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/qorai_education/qorai_education_page_delegate_desktop.h"

#include "base/check.h"
#include "qorai/browser/ui/qorai_rewards/rewards_panel_coordinator.h"
#include "qorai/browser/ui/qorai_vpn/qorai_vpn_controller.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "chrome/browser/ui/browser_window/public/browser_window_features.h"
#include "chrome/browser/ui/browser_window/public/browser_window_interface.h"
#include "chrome/browser/ui/views/side_panel/side_panel_entry.h"
#include "chrome/browser/ui/views/side_panel/side_panel_ui.h"

namespace qorai_education {

QoraiEducationPageDelegateDesktop::QoraiEducationPageDelegateDesktop(
    BrowserWindowInterface& window_interface)
    : window_interface_(window_interface) {}

QoraiEducationPageDelegateDesktop::~QoraiEducationPageDelegateDesktop() =
    default;

void QoraiEducationPageDelegateDesktop::OpenURL(
    const GURL& url,
    WindowOpenDisposition disposition) {
  window_interface_->OpenGURL(url, disposition);
}

void QoraiEducationPageDelegateDesktop::OpenRewardsPanel() {
  auto* panel_coordinator =
      window_interface_->GetFeatures().rewards_panel_coordinator();
  if (panel_coordinator) {
    panel_coordinator->OpenRewardsPanel();
  }
}

void QoraiEducationPageDelegateDesktop::OpenVPNPanel() {
#if BUILDFLAG(ENABLE_QORAI_VPN)
  window_interface_->GetFeatures().qorai_vpn_controller()->ShowQoraiVPNBubble(
      /* show_select */ false);
#endif
}

void QoraiEducationPageDelegateDesktop::OpenAIChat() {
  window_interface_->GetFeatures().side_panel_ui()->Show(
      SidePanelEntry::Key(SidePanelEntryId::kChatUI));
}

}  // namespace qorai_education
