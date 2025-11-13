/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_OPAQUE_BROWSER_FRAME_VIEW_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_OPAQUE_BROWSER_FRAME_VIEW_H_

#define WebAppOpaqueBrowserFrameViewWindowControlsOverlayTest \
  WebAppOpaqueBrowserFrameViewWindowControlsOverlayTest;      \
  friend class QoraiOpaqueBrowserFrameView
#define UpdateCaptionButtonPlaceholderContainerBackground \
  virtual UpdateCaptionButtonPlaceholderContainerBackground
#define PaintClientEdge virtual PaintClientEdge

#include <chrome/browser/ui/views/frame/opaque_browser_frame_view.h>  // IWYU pragma: export

#undef PaintClientEdge
#undef UpdateCaptionButtonPlaceholderContainerBackground
#undef WebAppOpaqueBrowserFrameViewWindowControlsOverlayTest

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_OPAQUE_BROWSER_FRAME_VIEW_H_
