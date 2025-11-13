/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TABS_TAB_SLOT_CONTROLLER_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TABS_TAB_SLOT_CONTROLLER_H_

#define IsGroupCollapsed(...)                                  \
  IsGroupCollapsed(__VA_ARGS__) const = 0;                     \
  virtual void SetCustomTitleForTab(                           \
      Tab* tab, const std::optional<std::u16string>& title) {} \
  virtual const Browser* GetBrowser()

#include <chrome/browser/ui/views/tabs/tab_slot_controller.h>  // IWYU pragma: export

#undef IsGroupCollapsed

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TABS_TAB_SLOT_CONTROLLER_H_
