/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_SIDE_PANEL_QORAI_BOOKMARKS_SIDE_PANEL_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_SIDE_PANEL_QORAI_BOOKMARKS_SIDE_PANEL_VIEW_H_

#include "qorai/browser/ui/views/side_panel/qorai_side_panel_view_base.h"

class SidePanelEntryScope;

// Gives bookmarks panel specific header view with web view.
class QoraiBookmarksSidePanelView : public QoraiSidePanelViewBase {
 public:
  explicit QoraiBookmarksSidePanelView(SidePanelEntryScope& scope);
  ~QoraiBookmarksSidePanelView() override;
  QoraiBookmarksSidePanelView(const QoraiBookmarksSidePanelView&) = delete;
  QoraiBookmarksSidePanelView& operator=(const QoraiBookmarksSidePanelView&) =
      delete;
};

#endif  // QORAI_BROWSER_UI_VIEWS_SIDE_PANEL_QORAI_BOOKMARKS_SIDE_PANEL_VIEW_H_
