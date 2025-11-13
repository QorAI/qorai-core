/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_FEATURES_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_FEATURES_H_

#include <string>

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace qorai_search_conversion {
namespace features {

inline constexpr char kBannerTypeParamName[] = "banner_type";

BASE_DECLARE_FEATURE(kOmniboxBanner);
extern const base::FeatureParam<std::string> kBannerType;

BASE_DECLARE_FEATURE(kOmniboxDDGBanner);
BASE_DECLARE_FEATURE(kOmniboxPromotionButton);

BASE_DECLARE_FEATURE(kNTP);

}  // namespace features
}  // namespace qorai_search_conversion

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_FEATURES_H_
