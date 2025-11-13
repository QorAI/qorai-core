/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_FEATURE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace qorai_ads {

BASE_DECLARE_FEATURE(kConfirmationsFeature);

inline constexpr base::FeatureParam<base::TimeDelta>
    kRetryProcessingConfirmationAfter{
        &kConfirmationsFeature, "retry_processing_after", base::Seconds(15)};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_FEATURE_H_
