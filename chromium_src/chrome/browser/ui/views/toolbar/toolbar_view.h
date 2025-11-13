/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TOOLBAR_TOOLBAR_VIEW_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TOOLBAR_TOOLBAR_VIEW_H_

#include "chrome/browser/ui/views/frame/browser_root_view.h"
#include "chrome/browser/ui/views/intent_picker_bubble_view.h"
#include "chrome/browser/ui/views/location_bar/custom_tab_bar_view.h"

#define Init virtual Init
#define Update virtual Update
#define ShowBookmarkBubble virtual ShowBookmarkBubble
#define UpdateRecedingCornerRadius virtual UpdateRecedingCornerRadius
#define LoadImages(...)                                                       \
  virtual LoadImages(__VA_ARGS__);                                            \
  friend class QoraiToolbarView;                                              \
  FRIEND_TEST_ALL_PREFIXES(QoraiToolbarViewTest, SplitTabsToolbarButtonTest); \
  FRIEND_TEST_ALL_PREFIXES(QoraiToolbarViewTest, ToolbarCornerRadiusTest)

#include <chrome/browser/ui/views/toolbar/toolbar_view.h>  // IWYU pragma: export

#undef LoadImages
#undef UpdateRecedingCornerRadius
#undef ShowBookmarkBubble
#undef Update
#undef Init

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TOOLBAR_TOOLBAR_VIEW_H_
