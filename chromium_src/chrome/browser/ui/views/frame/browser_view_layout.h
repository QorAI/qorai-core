// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_VIEW_LAYOUT_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_VIEW_LAYOUT_H_

// Make override-able
#define LayoutTabStripRegion           \
  UnUsed();                            \
  friend class QoraiBrowserViewLayout; \
  virtual void LayoutTabStripRegion

#define IsImmersiveModeEnabledWithoutToolbar \
  virtual IsImmersiveModeEnabledWithoutToolbar
#define LayoutBookmarkBar virtual LayoutBookmarkBar
#define LayoutInfoBar virtual LayoutInfoBar
#define LayoutContentsContainerView virtual LayoutContentsContainerView

// Add a new method: NotifyDialogPositionRequiresUpdate(). This is needed for
// split view to update the dialog position when the split view is resized.
#define set_webui_tab_strip                  \
  set_webui_tab_strip_unused();              \
  void NotifyDialogPositionRequiresUpdate(); \
  void set_webui_tab_strip

#include <chrome/browser/ui/views/frame/browser_view_layout.h>  // IWYU pragma: export

#undef set_webui_tab_strip
#undef LayoutContentsContainerView
#undef LayoutInfoBar
#undef LayoutBookmarkBar
#undef IsImmersiveModeEnabledWithoutToolbar
#undef LayoutTabStripRegion

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_VIEW_LAYOUT_H_
