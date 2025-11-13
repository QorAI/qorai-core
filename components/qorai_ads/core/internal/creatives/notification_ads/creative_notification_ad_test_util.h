/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_CREATIVE_NOTIFICATION_AD_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_CREATIVE_NOTIFICATION_AD_TEST_UTIL_H_

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"

namespace qorai_ads::test {

CreativeNotificationAdList BuildCreativeNotificationAds(size_t count);
CreativeNotificationAdInfo BuildCreativeNotificationAd(
    bool should_generate_random_uuids);

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_CREATIVE_NOTIFICATION_AD_TEST_UTIL_H_
