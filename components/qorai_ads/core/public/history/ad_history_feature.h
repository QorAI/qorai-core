/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_FEATURE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "base/time/time.h"

namespace qorai_ads {

BASE_DECLARE_FEATURE(kAdHistoryFeature);

inline constexpr base::FeatureParam<base::TimeDelta> kAdHistoryRetentionPeriod{
    &kAdHistoryFeature, "retention_period", base::Days(30)};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_FEATURE_H_
