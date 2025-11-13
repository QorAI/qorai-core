// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_SIDE_PANEL_BOOKMARKS_BOOKMARKS_SIDE_PANEL_COORDINATOR_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_SIDE_PANEL_BOOKMARKS_BOOKMARKS_SIDE_PANEL_COORDINATOR_H_

#define CreateAndRegisterEntry              \
  CreateAndRegisterEntry_UnUsed() {}        \
  friend class QoraiBookmarksSidePanelView; \
  virtual void CreateAndRegisterEntry

#include <chrome/browser/ui/views/side_panel/bookmarks/bookmarks_side_panel_coordinator.h>  // IWYU pragma: export
#undef CreateAndRegisterEntry

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_SIDE_PANEL_BOOKMARKS_BOOKMARKS_SIDE_PANEL_COORDINATOR_H_
