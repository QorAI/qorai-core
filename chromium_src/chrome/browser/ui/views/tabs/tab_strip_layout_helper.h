/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TABS_TAB_STRIP_LAYOUT_HELPER_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TABS_TAB_STRIP_LAYOUT_HELPER_H_

#include "qorai/browser/ui/views/tabs/qorai_tab_strip_layout_helper.h"

class QoraiTabStrip;

// As TabStripLayoutHelper's destructor is not virtual, it'd be safer not to
// make virtual methods and child class of it
#define UpdateIdealBounds                                           \
  UnUsed() {                                                        \
    return {};                                                      \
  }                                                                 \
  void set_use_vertical_tabs(bool vertical) {                       \
    use_vertical_tabs_ = vertical;                                  \
  }                                                                 \
  void set_tab_strip(TabStrip* tab_strip) {                         \
    tab_strip_ = tab_strip;                                         \
  }                                                                 \
                                                                    \
 private:                                                           \
  friend class QoraiTabContainer;                                   \
  bool FillGroupInfo(std::vector<TabWidthConstraints>& tab_widths); \
  QoraiTabStrip* GetQoraiTabStrip() const;                          \
  bool use_vertical_tabs_ = false;                                  \
  raw_ptr<TabStrip> tab_strip_ = nullptr;                           \
                                                                    \
 public:                                                            \
  int UpdateIdealBounds

#include <chrome/browser/ui/views/tabs/tab_strip_layout_helper.h>  // IWYU pragma: export

#undef UpdateIdealBounds

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TABS_TAB_STRIP_LAYOUT_HELPER_H_
