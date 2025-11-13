/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/frame/qorai_system_menu_model_builder.h"

#include "qorai/app/qorai_command_ids.h"
#include "qorai/browser/ui/views/tabs/vertical_tab_utils.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/app/chrome_command_ids.h"
#include "ui/menus/simple_menu_model.h"

QoraiSystemMenuModelBuilder::~QoraiSystemMenuModelBuilder() = default;

void QoraiSystemMenuModelBuilder::InsertQoraiSystemMenuForBrowserWindow(
    ui::SimpleMenuModel* model) {
  if (tabs::utils::SupportsVerticalTabs(browser())) {
    std::optional<size_t> bookmark_all_tabs_index =
        model->GetIndexOfCommandId(IDC_BOOKMARK_ALL_TABS);

    if (bookmark_all_tabs_index.has_value()) {
      model->InsertCheckItemWithStringIdAt(bookmark_all_tabs_index.value() + 1,
                                           IDC_TOGGLE_VERTICAL_TABS,
                                           IDS_TAB_CXMENU_SHOW_VERTICAL_TABS);
    }
  }
}

void QoraiSystemMenuModelBuilder::BuildSystemMenuForBrowserWindow(
    ui::SimpleMenuModel* model) {
  SystemMenuModelBuilder::BuildSystemMenuForBrowserWindow(model);
  InsertQoraiSystemMenuForBrowserWindow(model);
}
