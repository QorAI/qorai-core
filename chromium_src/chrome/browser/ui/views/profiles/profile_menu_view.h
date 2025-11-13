/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PROFILES_PROFILE_MENU_VIEW_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PROFILES_PROFILE_MENU_VIEW_H_

#define QORAI_PROFILE_MENU_VIEW_H friend class QoraiProfileMenuView;

#define OnExitProfileButtonClicked virtual OnExitProfileButtonClicked
#define BuildFeatureButtons virtual BuildFeatureButtons
#define MaybeBuildCloseBrowsersButton virtual MaybeBuildCloseBrowsersButton

#include <chrome/browser/ui/views/profiles/profile_menu_view.h>  // IWYU pragma: export
#undef MaybeBuildCloseBrowsersButton
#undef BuildFeatureButtons
#undef OnExitProfileButtonClicked
#undef QORAI_PROFILE_MENU_VIEW_H

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PROFILES_PROFILE_MENU_VIEW_H_
