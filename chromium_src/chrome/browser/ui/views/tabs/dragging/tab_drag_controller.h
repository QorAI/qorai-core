/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TABS_DRAGGING_TAB_DRAG_CONTROLLER_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TABS_DRAGGING_TAB_DRAG_CONTROLLER_H_

// In order to replace TabDragController with ours easily, rename upstream's
// implementation. Ours is in qorai/browser/ui/views/tabs/tab_drag_controller.h
// and the file will be included at the end of this file.
class TabDragController;
using TabDragControllerQorai = TabDragController;

#define TabDragController TabDragControllerChromium

#define CompleteDrag             \
  CompleteDrag_Unused();         \
  friend TabDragControllerQorai; \
  void CompleteDrag

#define GetAttachedBrowserWidget      \
  GetAttachedBrowserWidget_Unused() { \
    return {};                        \
  }                                   \
  virtual views::Widget* GetAttachedBrowserWidget

#define CalculateWindowDragOffset      \
  CalculateWindowDragOffset_Unused() { \
    return {};                         \
  }                                    \
  virtual gfx::Vector2d CalculateWindowDragOffset

#define GetLocalProcessWindow virtual GetLocalProcessWindow
#define DetachAndAttachToNewContext virtual DetachAndAttachToNewContext
#define StartDraggingTabsSession virtual StartDraggingTabsSession

#include <chrome/browser/ui/views/tabs/dragging/tab_drag_controller.h>  // IWYU pragma: export

#undef StartDraggingTabsSession
#undef DetachAndAttachToNewContext
#undef GetLocalProcessWindow
#undef CalculateWindowDragOffset
#undef GetAttachedBrowserWidget
#undef TabDragController
#undef CompleteDrag

#include "qorai/browser/ui/views/tabs/dragging/tab_drag_controller.h"

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TABS_DRAGGING_TAB_DRAG_CONTROLLER_H_
