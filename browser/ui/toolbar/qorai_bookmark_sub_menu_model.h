/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_TOOLBAR_QORAI_BOOKMARK_SUB_MENU_MODEL_H_
#define QORAI_BROWSER_UI_TOOLBAR_QORAI_BOOKMARK_SUB_MENU_MODEL_H_

#include <memory>

#include "qorai/browser/ui/toolbar/bookmark_bar_sub_menu_model.h"
#include "chrome/browser/ui/toolbar/bookmark_sub_menu_model.h"

class Browser;

class QoraiBookmarkSubMenuModel : public BookmarkSubMenuModel {
 public:
  QoraiBookmarkSubMenuModel(ui::SimpleMenuModel::Delegate* delegate,
                            Browser* browser);

  QoraiBookmarkSubMenuModel(const QoraiBookmarkSubMenuModel&) = delete;
  QoraiBookmarkSubMenuModel& operator=(const QoraiBookmarkSubMenuModel&) =
      delete;

  ~QoraiBookmarkSubMenuModel() override;

 private:
  void Build(Browser* browser);

  std::unique_ptr<BookmarkBarSubMenuModel> qorai_bookmarks_submenu_model_;
};

#endif  // QORAI_BROWSER_UI_TOOLBAR_QORAI_BOOKMARK_SUB_MENU_MODEL_H_
