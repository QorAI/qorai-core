/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PAGE_INFO_PAGE_INFO_BUBBLE_VIEW_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PAGE_INFO_PAGE_INFO_BUBBLE_VIEW_H_

#include "chrome/browser/ui/views/page_info/page_info_bubble_view_base.h"

// Friend the Qorai subclass so that it can access a private constructor. Also,
// make the `AnnouncePageOpened` method virtual so that subclasses can hook into
// page switch events. This can be used to update the view hierarchy after a new
// page or subpage is displayed.
#define AnnouncePageOpened(...)            \
  virtual AnnouncePageOpened(__VA_ARGS__); \
  friend class QoraiPageInfoBubbleView

#include <chrome/browser/ui/views/page_info/page_info_bubble_view.h>  // IWYU pragma: export

#undef AnnouncePageOpened

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PAGE_INFO_PAGE_INFO_BUBBLE_VIEW_H_
