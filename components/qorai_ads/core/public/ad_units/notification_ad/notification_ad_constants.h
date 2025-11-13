/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_CONSTANTS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_CONSTANTS_H_

#include <cstdint>

#include "base/time/time.h"
#include "build/build_config.h"

namespace qorai_ads {

inline constexpr char kNotificationAdTypeKey[] = "type";
inline constexpr char kNotificationAdPlacementIdKey[] = "uuid";
inline constexpr char kNotificationAdCreativeInstanceIdKey[] =
    "creative_instance_id";
inline constexpr char kNotificationAdCreativeSetIdKey[] = "creative_set_id";
inline constexpr char kNotificationAdCampaignIdKey[] = "campaign_id";
inline constexpr char kNotificationAdAdvertiserIdKey[] = "advertiser_id";
inline constexpr char kNotificationAdSegmentKey[] = "segment";
inline constexpr char kNotificationAdTitleKey[] = "title";
inline constexpr char kNotificationAdBodyKey[] = "body";
inline constexpr char kNotificationAdTargetUrlKey[] = "target_url";

// Qorai Ads per hour are user configurable within the qorai://rewards ads UI.
#if !BUILDFLAG(IS_IOS)
inline constexpr int64_t kDefaultQoraiRewardsNotificationAdsPerHour = 10;
#else
inline constexpr int64_t kDefaultQoraiRewardsNotificationAdsPerHour = 2;
#endif  // !BUILDFLAG(IS_IOS)

// Default ad notification timeout in seconds.
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
inline constexpr base::TimeDelta kDefaultNotificationAdTimeout =
    base::Minutes(2);
#else
inline constexpr base::TimeDelta kDefaultNotificationAdTimeout =
    base::Seconds(30);
#endif  // !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)

// Do not fallback to custom notification ad by default
inline constexpr bool kDefaultCanFallbackToCustomNotificationAds = false;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_CONSTANTS_H_
