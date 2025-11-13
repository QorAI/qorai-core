/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_FEATURE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/public/ad_units/notification_ad/notification_ad_constants.h"

namespace qorai_ads {

BASE_DECLARE_FEATURE(kNotificationAdFeature);
BASE_DECLARE_FEATURE(kAllowedToFallbackToCustomNotificationAdFeature);

// Ad notification timeout in seconds. Set to 0 to never time out
inline constexpr base::FeatureParam<base::TimeDelta> kNotificationAdTimeout{
    &kNotificationAdFeature, "notification_ad_timeout",
    kDefaultNotificationAdTimeout};

inline constexpr base::FeatureParam<int> kDefaultNotificationAdsPerHour{
    &kNotificationAdFeature, "default_ads_per_hour",
    kDefaultQoraiRewardsNotificationAdsPerHour};

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kMaximumNotificationAdsPerDay{
    &kNotificationAdFeature, "maximum_ads_per_day", 100};

// Set to true to fallback to custom notification ads if native notifications
// are disabled or false to never fallback
inline constexpr base::FeatureParam<bool> kCanFallbackToCustomNotificationAds{
    &kNotificationAdFeature, "can_fallback_to_custom_notifications",
    kDefaultCanFallbackToCustomNotificationAds};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_FEATURE_H_
