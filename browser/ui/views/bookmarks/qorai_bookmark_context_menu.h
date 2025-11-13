/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_BOOKMARKS_QORAI_BOOKMARK_CONTEXT_MENU_H_
#define QORAI_BROWSER_UI_VIEWS_BOOKMARKS_QORAI_BOOKMARK_CONTEXT_MENU_H_

#include <vector>

#include "chrome/browser/ui/views/bookmarks/bookmark_context_menu.h"

class QoraiBookmarkContextMenu : public BookmarkContextMenu {
 public:
  // |browser| is used to open bookmarks as well as the bookmark manager, and
  // is NULL in tests.
  QoraiBookmarkContextMenu(
      views::Widget* parent_widget,
      Browser* browser,
      Profile* profile,
      BookmarkLaunchLocation opened_from,
      const std::vector<raw_ptr<const bookmarks::BookmarkNode,
                                VectorExperimental>>& selection,
      bool close_on_remove);

  QoraiBookmarkContextMenu(const QoraiBookmarkContextMenu&) = delete;
  QoraiBookmarkContextMenu& operator=(const QoraiBookmarkContextMenu&) = delete;

  ~QoraiBookmarkContextMenu() override;

 private:
  friend class QoraiBookmarkContextMenuTest;

  QoraiBookmarkContextMenuController* GetControllerForTesting();
};

#endif  // QORAI_BROWSER_UI_VIEWS_BOOKMARKS_QORAI_BOOKMARK_CONTEXT_MENU_H_
