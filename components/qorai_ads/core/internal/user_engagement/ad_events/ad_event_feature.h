/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_FEATURE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace qorai_ads {

BASE_DECLARE_FEATURE(kAdEventFeature);

// Set to 0 to always deduplicate viewed ad events.
inline constexpr base::FeatureParam<base::TimeDelta>
    kDeduplicateViewedAdEventFor{
        &kAdEventFeature, "deduplicate_viewed_ad_event_for", base::Seconds(0)};

// Set to 0 to always deduplicate clicked ad events.
inline constexpr base::FeatureParam<base::TimeDelta>
    kDeduplicateClickedAdEventFor{
        &kAdEventFeature, "deduplicate_clicked_ad_event_for", base::Seconds(1)};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_FEATURE_H_
