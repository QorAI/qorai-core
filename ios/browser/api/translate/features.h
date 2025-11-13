// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_API_TRANSLATE_FEATURES_H_
#define QORAI_IOS_BROWSER_API_TRANSLATE_FEATURES_H_

#import "base/feature_list.h"

namespace qorai::features {

// Whether or not to use the new Qorai-Translate feature
BASE_DECLARE_FEATURE(kQoraiTranslateEnabled);

// Whether or not to use the new Qorai-Translate with Apple feature
BASE_DECLARE_FEATURE(kQoraiAppleTranslateEnabled);

}  // namespace qorai::features

#endif  // QORAI_IOS_BROWSER_API_TRANSLATE_FEATURES_H_
