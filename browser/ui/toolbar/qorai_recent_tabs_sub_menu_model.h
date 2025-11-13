/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_TOOLBAR_QORAI_RECENT_TABS_SUB_MENU_MODEL_H_
#define QORAI_BROWSER_UI_TOOLBAR_QORAI_RECENT_TABS_SUB_MENU_MODEL_H_

#include "chrome/browser/ui/tabs/recent_tabs_sub_menu_model.h"

class Browser;

namespace ui {
class AcceleratorProvider;
}

class QoraiRecentTabsSubMenuModel : public RecentTabsSubMenuModel {
 public:
  QoraiRecentTabsSubMenuModel(ui::AcceleratorProvider* accelerator_provider,
                         Browser* browser);

  QoraiRecentTabsSubMenuModel(const QoraiRecentTabsSubMenuModel&) = delete;
  QoraiRecentTabsSubMenuModel& operator=(const QoraiRecentTabsSubMenuModel&) =
      delete;

  ~QoraiRecentTabsSubMenuModel() override;

  void ExecuteCommand(int command_id, int event_flags) override;
};

#endif  // QORAI_BROWSER_UI_TOOLBAR_QORAI_RECENT_TABS_SUB_MENU_MODEL_H_
