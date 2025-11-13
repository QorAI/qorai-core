/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_BUILDER_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_BUILDER_TEST_UTIL_H_

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace base {
class Time;
}  // namespace base

namespace qorai_ads {

struct AdEventInfo;
struct CreativeAdInfo;

namespace test {

AdEventInfo BuildAdEvent(const CreativeAdInfo& creative_ad,
                         mojom::AdType mojom_ad_type,
                         mojom::ConfirmationType mojom_confirmation_type,
                         base::Time created_at,
                         bool should_generate_random_uuids);

}  // namespace test

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_BUILDER_TEST_UTIL_H_
