/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_TABS_TAB_STRIP_MODEL_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_TABS_TAB_STRIP_MODEL_H_

#define SelectRelativeTab(...)            \
  virtual SelectRelativeTab(__VA_ARGS__); \
  friend class QoraiTabStripModel

#define DraggingTabsSession DraggingTabsSessionChromium
#define IsReadLaterSupportedForAny virtual IsReadLaterSupportedForAny
#define UpdateWebContentsStateAt virtual UpdateWebContentsStateAt

// Moved to public to call from split_tabs::QoraiGetIndexOfLastActiveTab().
#define CanActivateTabAt            \
  CanActivateTabAt_Unused() {       \
    return false;                   \
  }                                 \
                                    \
 public:                            \
  bool CanActivateTabAt(int index); \
                                    \
 private:                           \
  bool Unused

#include <chrome/browser/ui/tabs/tab_strip_model.h>  // IWYU pragma: export

#undef CanActivateTabAt
#undef UpdateWebContentsStateAt
#undef IsReadLaterSupportedForAny
#undef DraggingTabsSession
#undef SelectRelativeTab

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_TABS_TAB_STRIP_MODEL_H_
