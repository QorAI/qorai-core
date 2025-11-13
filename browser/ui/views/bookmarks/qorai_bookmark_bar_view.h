
/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_BOOKMARKS_QORAI_BOOKMARK_BAR_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_BOOKMARKS_QORAI_BOOKMARK_BAR_VIEW_H_

#include "chrome/browser/ui/views/bookmarks/bookmark_bar_view.h"
#include "components/prefs/pref_member.h"
#include "ui/base/metadata/metadata_header_macros.h"

class QoraiBookmarkBarView : public BookmarkBarView {
  METADATA_HEADER(QoraiBookmarkBarView, BookmarkBarView)
 public:

  QoraiBookmarkBarView(Browser* browser, BrowserView* browser_view);
  ~QoraiBookmarkBarView() override;

  // BookmarkBarView:
  bool UpdateOtherAndManagedButtonsVisibility() override;

 private:
  // Note that so-called "Others button" is renamed to "All bookmarks button"
  void OnShowAllBookmarksButtonPrefChanged();

  void MaybeUpdateOtherAndManagedButtonsVisibility();

  BooleanPrefMember show_all_bookmarks_button_pref_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_BOOKMARKS_QORAI_BOOKMARK_BAR_VIEW_H_
