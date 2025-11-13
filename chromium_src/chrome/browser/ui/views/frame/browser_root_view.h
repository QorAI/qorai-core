/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_ROOT_VIEW_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_ROOT_VIEW_H_

#define on_filtering_complete_closure_ \
  on_filtering_complete_closure_;      \
  friend class VerticalTabStripRootViewBrowserTest

#include <chrome/browser/ui/views/frame/browser_root_view.h>  // IWYU pragma: export
#undef on_filtering_complete_closure_

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_ROOT_VIEW_H_
