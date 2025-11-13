/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_search_conversion/features.h"

namespace qorai_search_conversion::features {

// Qorai search promotion match located at last low in omnibox popup.
// This type seems more like ads banner.
BASE_FEATURE(kOmniboxBanner,
             "QoraiSearchOmniboxBanner",
             base::FEATURE_DISABLED_BY_DEFAULT);

const base::FeatureParam<std::string> kBannerType{&kOmniboxBanner,
                                                  kBannerTypeParamName, ""};

BASE_FEATURE(kOmniboxDDGBanner,
             "QoraiSearchOmniboxDDGBanner",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kOmniboxPromotionButton,
             "QoraiSearchPromotionOmniboxButton",
             base::FEATURE_DISABLED_BY_DEFAULT);

// Qorai search promotion at NTP.
BASE_FEATURE(kNTP, "QoraiSearchNTP", base::FEATURE_DISABLED_BY_DEFAULT);

}  // namespace qorai_search_conversion::features
