/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"

namespace qorai_ads {

CreativeNotificationAdInfo::CreativeNotificationAdInfo() = default;

CreativeNotificationAdInfo::CreativeNotificationAdInfo(
    const CreativeAdInfo& creative_ad)
    : CreativeAdInfo(creative_ad) {}

}  // namespace qorai_ads
