/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_OVERLAY_VIDEO_OVERLAY_WINDOW_VIEWS_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_OVERLAY_VIDEO_OVERLAY_WINDOW_VIEWS_H_

class QoraiBackToTabLabelButton;

#define SetUpViews                           \
  SetUpViews_Unused();                       \
  friend class QoraiVideoOverlayWindowViews; \
  virtual void SetUpViews

#define OnUpdateControlsBounds virtual OnUpdateControlsBounds
#define BackToTabLabelButton QoraiBackToTabLabelButton
#define ControlsHitTestContainsPoint virtual ControlsHitTestContainsPoint
#define IsTrustedForMediaPlayback virtual IsTrustedForMediaPlayback

#include <chrome/browser/ui/views/overlay/video_overlay_window_views.h>  // IWYU pragma: export

#undef IsTrustedForMediaPlayback
#undef ControlsHitTestContainsPoint
#undef BackToTabLabelButton
#undef OnUpdateControlsBounds
#undef SetUpViews

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_OVERLAY_VIDEO_OVERLAY_WINDOW_VIEWS_H_
