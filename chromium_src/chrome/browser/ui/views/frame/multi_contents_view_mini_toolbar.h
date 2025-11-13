/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_MULTI_CONTENTS_VIEW_MINI_TOOLBAR_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_MULTI_CONTENTS_VIEW_MINI_TOOLBAR_H_

#include <memory>

#include "chrome/browser/ui/tabs/split_tab_menu_model.h"

namespace gfx {
struct VectorIcon;
}  // namespace gfx

// Both static methods are defined at qorai_multi_contents_view_mini_toolbar.cc
// to avoid qorai dependency here.
#define UpdateState(...)                                                    \
  virtual UpdateState(__VA_ARGS__);                                         \
  static const gfx::VectorIcon& GetMoreVerticalIcon();                      \
  static std::unique_ptr<ui::SimpleMenuModel> CreateQoraiSplitTabMenuModel( \
      TabStripModel* tab_strip_model, SplitTabMenuModel::MenuSource source, \
      int split_tab_index);                                                 \
  FRIEND_TEST_ALL_PREFIXES(SideBySideEnabledBrowserTest, SelectTabTest);    \
  friend class QoraiMultiContentsViewMiniToolbar

#include <chrome/browser/ui/views/frame/multi_contents_view_mini_toolbar.h>  // IWYU pragma: export

#undef UpdateState

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_MULTI_CONTENTS_VIEW_MINI_TOOLBAR_H_
