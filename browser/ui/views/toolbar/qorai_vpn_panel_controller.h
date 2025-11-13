/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_TOOLBAR_QORAI_VPN_PANEL_CONTROLLER_H_
#define QORAI_BROWSER_UI_VIEWS_TOOLBAR_QORAI_VPN_PANEL_CONTROLLER_H_

#include <memory>

#include "base/memory/raw_ptr.h"
#include "qorai/browser/ui/webui/qorai_vpn/vpn_panel_ui.h"
#include "chrome/browser/ui/views/bubble/webui_bubble_manager.h"

class QoraiBrowserView;

class QoraiVPNPanelController {
 public:
  explicit QoraiVPNPanelController(QoraiBrowserView* browser_view);
  ~QoraiVPNPanelController();
  QoraiVPNPanelController(const QoraiVPNPanelController&) = delete;
  QoraiVPNPanelController& operator=(const QoraiVPNPanelController&) = delete;

  // Pass true to |show_select| when we want to show server selection
  // in the main panel at startup.
  void ShowQoraiVPNPanel(bool show_select = false);
  // Manager should be reset to use different anchor view for bubble.
  void ResetBubbleManager();

 private:
  raw_ptr<QoraiBrowserView> browser_view_ = nullptr;
  std::unique_ptr<WebUIBubbleManager> webui_bubble_manager_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_TOOLBAR_QORAI_VPN_PANEL_CONTROLLER_H_
