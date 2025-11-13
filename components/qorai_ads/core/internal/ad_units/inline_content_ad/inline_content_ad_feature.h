/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_INLINE_CONTENT_AD_INLINE_CONTENT_AD_FEATURE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_INLINE_CONTENT_AD_INLINE_CONTENT_AD_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace qorai_ads {

BASE_DECLARE_FEATURE(kInlineContentAdFeature);

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kMaximumInlineContentAdsPerHour{
    &kInlineContentAdFeature, "maximum_ads_per_hour", 6};

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kMaximumInlineContentAdsPerDay{
    &kInlineContentAdFeature, "maximum_ads_per_day", 20};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_INLINE_CONTENT_AD_INLINE_CONTENT_AD_FEATURE_H_
