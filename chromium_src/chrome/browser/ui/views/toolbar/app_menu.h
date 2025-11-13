/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TOOLBAR_APP_MENU_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TOOLBAR_APP_MENU_H_

#define SetTimerForTesting                         \
  UnusedMethod1() {}                               \
  friend class QoraiAppMenu;                       \
                                                   \
  std::unique_ptr<views::Background>               \
  CreateInMenuButtonBackgroundWithLeadingBorder(); \
                                                   \
  void SetTimerForTesting

#define RunMenu virtual RunMenu

#include <chrome/browser/ui/views/toolbar/app_menu.h>  // IWYU pragma: export

#undef SetTimerForTesting
#undef RunMenu

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TOOLBAR_APP_MENU_H_
