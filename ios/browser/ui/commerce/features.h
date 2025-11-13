// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_UI_COMMERCE_FEATURES_H_
#define QORAI_IOS_BROWSER_UI_COMMERCE_FEATURES_H_

#import "base/feature_list.h"

namespace qorai::features {

// Whether or not to allow Qorai to present external purchase links for Qorai
// Premium products on iOS paywalls.
BASE_DECLARE_FEATURE(kQoraiAllowExternalPurchaseLinks);

}  // namespace qorai::features

#endif  // QORAI_IOS_BROWSER_UI_COMMERCE_FEATURES_H_
