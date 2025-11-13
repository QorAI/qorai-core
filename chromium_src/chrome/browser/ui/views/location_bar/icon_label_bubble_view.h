/* Copyright (c) 2015 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_ICON_LABEL_BUBBLE_VIEW_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_ICON_LABEL_BUBBLE_VIEW_H_

class QoraiLocationBarView;

// Making this class friend of `QoraiLocationBarView`, so `GetMinimumSize` can
// be called for its icons, as this function is now overridden in
// `IconLabelBubbleView` and made protected.
#define UpdateLabelColors            \
  UpdateLabelColors_Unused();        \
  friend class QoraiLocationBarView; \
  void UpdateLabelColors

#include <chrome/browser/ui/views/location_bar/icon_label_bubble_view.h>  // IWYU pragma: export

#undef UpdateLabelColors

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_ICON_LABEL_BUBBLE_VIEW_H_
