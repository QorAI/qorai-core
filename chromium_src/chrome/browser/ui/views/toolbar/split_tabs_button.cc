/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/views/toolbar/split_tabs_button.h"

#define SplitTabsToolbarButton SplitTabsToolbarButton_ChromiumImpl

#include <chrome/browser/ui/views/toolbar/split_tabs_button.cc>

#undef SplitTabsToolbarButton

// defined at qorai_split_tab_menu_model.cc to avoid QoraiSplitTabMenuModel
// dependency here.
std::unique_ptr<ui::SimpleMenuModel> CreateQoraiSplitTabMenuModel(
    TabStripModel* tab_strip_model,
    SplitTabMenuModel::MenuSource source);

SplitTabsToolbarButton::SplitTabsToolbarButton(Browser* browser)
    : SplitTabsToolbarButton_ChromiumImpl(browser) {
  split_tab_menu_ = CreateQoraiSplitTabMenuModel(
      browser_->tab_strip_model(),
      SplitTabMenuModel::MenuSource::kToolbarButton);
}

SplitTabsToolbarButton::~SplitTabsToolbarButton() = default;

BEGIN_METADATA(SplitTabsToolbarButton)
END_METADATA
