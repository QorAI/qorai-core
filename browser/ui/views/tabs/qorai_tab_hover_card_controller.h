// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_HOVER_CARD_CONTROLLER_H_
#define QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_HOVER_CARD_CONTROLLER_H_

#include "chrome/browser/ui/views/tabs/tab_hover_card_controller.h"

class Tab;

class QoraiTabHoverCardController : public TabHoverCardController {
 public:
  using TabHoverCardController::TabHoverCardController;
  ~QoraiTabHoverCardController() override;

  void SetIsVerticalTabs(bool is_vertical_tabs);

 protected:
  void UpdateHoverCardArrow();

  void OnHovercardImagesEnabledChanged() override;

  // TabHoverCardController:
  void CreateHoverCard(Tab* tab) override;

  bool is_vertical_tabs_ = false;
};

#endif  // QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_HOVER_CARD_CONTROLLER_H_
