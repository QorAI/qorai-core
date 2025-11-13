/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TABS_TAB_GROUP_HIGHLIGHT_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TABS_TAB_GROUP_HIGHLIGHT_H_

#define GetPath                        \
  GetPath_Unused() { return {}; }      \
  friend class QoraiTabGroupHighlight; \
  virtual SkPath GetPath
#include <chrome/browser/ui/views/tabs/tab_group_highlight.h>  // IWYU pragma: export
#undef GetPath

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TABS_TAB_GROUP_HIGHLIGHT_H_
