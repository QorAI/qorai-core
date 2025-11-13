/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PROFILES_PROFILE_MENU_COORDINATOR_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PROFILES_PROFILE_MENU_COORDINATOR_H_

#define GetProfileMenuViewBaseForTesting() \
  GetProfileMenuViewBaseForTesting();      \
  friend class QoraiProfileMenuViewTest

#include <chrome/browser/ui/views/profiles/profile_menu_coordinator.h>  // IWYU pragma: export

#undef GetProfileMenuViewBaseForTesting

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PROFILES_PROFILE_MENU_COORDINATOR_H_
