/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_WIDGET_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_WIDGET_H_

#define OnMenuClosed               \
  OnMenuClosed_Unused() {}         \
  friend class QoraiBrowserWidget; \
  void OnMenuClosed

#define SetTabDragKind virtual SetTabDragKind

#include <chrome/browser/ui/views/frame/browser_widget.h>  // IWYU pragma: export

#undef SetTabDragKind

#undef OnMenuClosed

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_WIDGET_H_
