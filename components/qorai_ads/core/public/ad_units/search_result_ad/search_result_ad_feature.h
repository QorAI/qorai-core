/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_FEATURE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace qorai_ads {

BASE_DECLARE_FEATURE(kSearchResultAdFeature);

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kMaximumSearchResultAdsPerHour{
    &kSearchResultAdFeature, "maximum_ads_per_hour", 0};

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kMaximumSearchResultAdsPerDay{
    &kSearchResultAdFeature, "maximum_ads_per_day", 0};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_FEATURE_H_
