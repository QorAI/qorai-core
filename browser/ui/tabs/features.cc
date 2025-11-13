/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/tabs/features.h"

#include "chrome/browser/ui/ui_features.h"

namespace tabs::features {

#if BUILDFLAG(IS_LINUX)
BASE_FEATURE(kQoraiChangeActiveTabOnScrollEvent,
             base::FEATURE_ENABLED_BY_DEFAULT);
#endif  // BUILDFLAG(IS_LINUX)

BASE_FEATURE(kQoraiSharedPinnedTabs,
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiHorizontalTabsUpdate,
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiCompactHorizontalTabs,
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiVerticalTabScrollBar,
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiVerticalTabHideCompletely,
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiTreeTab, base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiRenamingTabs,
             base::FEATURE_DISABLED_BY_DEFAULT);

bool HorizontalTabsUpdateEnabled() {
  return base::FeatureList::IsEnabled(kQoraiHorizontalTabsUpdate);
}

}  // namespace tabs::features
