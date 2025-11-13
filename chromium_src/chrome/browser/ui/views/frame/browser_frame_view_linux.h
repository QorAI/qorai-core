/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_FRAME_VIEW_LINUX_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_FRAME_VIEW_LINUX_H_

#include "chrome/browser/ui/views/frame/opaque_browser_frame_view.h"

// Make BrowserFrameViewLinux extends our QoraiOpaqueBrowserFrameView
#include "qorai/browser/ui/views/frame/qorai_opaque_browser_frame_view.h"
#define OpaqueBrowserFrameView QoraiOpaqueBrowserFrameView

#include <chrome/browser/ui/views/frame/browser_frame_view_linux.h>  // IWYU pragma: export

#undef OpaqueBrowserFrameView

// Sanity check at compile time.
static_assert(
    std::is_base_of_v<QoraiOpaqueBrowserFrameView, BrowserFrameViewLinux>,
    "BrowserFrameViewLinux should be a child of QoraiOpaqueBrowserFrameView");

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_FRAME_VIEW_LINUX_H_
