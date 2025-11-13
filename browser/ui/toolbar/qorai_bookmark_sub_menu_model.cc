/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/toolbar/qorai_bookmark_sub_menu_model.h"

#include "chrome/app/chrome_command_ids.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/grit/generated_resources.h"

QoraiBookmarkSubMenuModel::QoraiBookmarkSubMenuModel(
    ui::SimpleMenuModel::Delegate* delegate,
    Browser* browser)
    : BookmarkSubMenuModel(delegate, browser) {
  Build(browser);
}

QoraiBookmarkSubMenuModel::~QoraiBookmarkSubMenuModel() = default;

void QoraiBookmarkSubMenuModel::Build(Browser* browser) {
  auto index = GetIndexOfCommandId(IDC_SHOW_BOOKMARK_BAR);
  if (!index.has_value())
    return;
  RemoveItemAt(index.value());
  qorai_bookmarks_submenu_model_ =
      std::make_unique<BookmarkBarSubMenuModel>(browser->profile());
  InsertSubMenuWithStringIdAt(index.value(), IDC_QORAI_BOOKMARK_BAR_SUBMENU,
                              IDS_SHOW_BOOKMARK_BAR,
                              qorai_bookmarks_submenu_model_.get());
}
