/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ELIGIBLE_ADS_FEATURE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ELIGIBLE_ADS_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace qorai_ads {

BASE_DECLARE_FEATURE(kEligibleAdFeature);

inline constexpr base::FeatureParam<int> kSiteHistoryMaxCount{
    &kEligibleAdFeature, "site_history_max_count", 5'000};

inline constexpr base::FeatureParam<int> kSiteHistoryRecentDayRange{
    &kEligibleAdFeature, "site_history_recent_day_range", 180};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ELIGIBLE_ADS_FEATURE_H_
