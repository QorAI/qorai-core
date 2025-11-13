/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_MULTI_CONTENTS_VIEW_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_MULTI_CONTENTS_VIEW_H_

#define UpdateSplitRatio(...)       \
  UpdateSplitRatio(__VA_ARGS__);    \
  virtual void ResetResizeArea() {} \
  friend class QoraiMultiContentsView

#include <chrome/browser/ui/views/frame/multi_contents_view.h>  // IWYU pragma: export

#undef UpdateSplitRatio

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_MULTI_CONTENTS_VIEW_H_
