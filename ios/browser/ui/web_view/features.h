// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_UI_WEB_VIEW_FEATURES_H_
#define QORAI_IOS_BROWSER_UI_WEB_VIEW_FEATURES_H_

#include "base/feature_list.h"

namespace qorai::features {

BASE_DECLARE_FEATURE(kUseChromiumWebViews);
BASE_DECLARE_FEATURE(kUseChromiumWebViewsAutofill);

}  // namespace qorai::features

#endif  // QORAI_IOS_BROWSER_UI_WEB_VIEW_FEATURES_H_
