/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_TABS_FEATURES_H_
#define QORAI_BROWSER_UI_TABS_FEATURES_H_

#include "base/feature_list.h"
namespace tabs::features {

#if BUILDFLAG(IS_LINUX)
// This flag controls the behavior of browser_default::kScrollEventChangesTab,
// which is true only when it's Linux.
BASE_DECLARE_FEATURE(kQoraiChangeActiveTabOnScrollEvent);
#endif  // BUILDFLAG(IS_LINUX)

BASE_DECLARE_FEATURE(kQoraiSharedPinnedTabs);

BASE_DECLARE_FEATURE(kQoraiHorizontalTabsUpdate);

BASE_DECLARE_FEATURE(kQoraiCompactHorizontalTabs);

BASE_DECLARE_FEATURE(kQoraiVerticalTabScrollBar);

BASE_DECLARE_FEATURE(kQoraiVerticalTabHideCompletely);

BASE_DECLARE_FEATURE(kQoraiTreeTab);

BASE_DECLARE_FEATURE(kQoraiRenamingTabs);

bool HorizontalTabsUpdateEnabled();

}  // namespace tabs::features

#endif  // QORAI_BROWSER_UI_TABS_FEATURES_H_
