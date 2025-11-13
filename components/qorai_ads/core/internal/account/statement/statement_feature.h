/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_FEATURE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace qorai_ads {

BASE_DECLARE_FEATURE(kAccountStatementFeature);

inline constexpr base::FeatureParam<int> kNextPaymentDay{
    &kAccountStatementFeature, "next_payment_day", 7};

inline constexpr base::FeatureParam<double> kMinEstimatedEarningsMultiplier{
    &kAccountStatementFeature, "minimum_estimated_earnings_multiplier", 0.8};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_FEATURE_H_
