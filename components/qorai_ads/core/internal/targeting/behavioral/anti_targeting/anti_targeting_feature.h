/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_ANTI_TARGETING_FEATURE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_ANTI_TARGETING_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace qorai_ads {

BASE_DECLARE_FEATURE(kAntiTargetingFeature);

inline constexpr base::FeatureParam<int> kAntiTargetingResourceVersion{
    &kAntiTargetingFeature, "resource_version", 1};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_ANTI_TARGETING_FEATURE_H_
