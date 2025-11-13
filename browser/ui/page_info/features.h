/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_PAGE_INFO_FEATURES_H_
#define QORAI_BROWSER_UI_PAGE_INFO_FEATURES_H_

#include "base/feature_list.h"

namespace page_info::features {

// Enables Qorai Shields integration in the Page Info bubble with a tab
// switcher to toggle between Shields settings and Site Settings.
BASE_DECLARE_FEATURE(kShowQoraiShieldsInPageInfo);

// Returns true if Qorai Shields should be shown in the Page Info bubble.
bool IsShowQoraiShieldsInPageInfoEnabled();

}  // namespace page_info::features

#endif  // QORAI_BROWSER_UI_PAGE_INFO_FEATURES_H_
