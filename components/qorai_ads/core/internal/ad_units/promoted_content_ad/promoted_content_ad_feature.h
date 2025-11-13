/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_PROMOTED_CONTENT_AD_PROMOTED_CONTENT_AD_FEATURE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_PROMOTED_CONTENT_AD_PROMOTED_CONTENT_AD_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace qorai_ads {

BASE_DECLARE_FEATURE(kPromotedContentAdFeature);

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kMaximumPromotedContentAdsPerHour{
    &kPromotedContentAdFeature, "maximum_ads_per_hour", 4};

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kMaximumPromotedContentAdsPerDay{
    &kPromotedContentAdFeature, "maximum_ads_per_day", 20};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_PROMOTED_CONTENT_AD_PROMOTED_CONTENT_AD_FEATURE_H_
