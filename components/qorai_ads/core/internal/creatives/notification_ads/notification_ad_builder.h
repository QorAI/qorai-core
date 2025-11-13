/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_NOTIFICATION_AD_BUILDER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_NOTIFICATION_AD_BUILDER_H_

#include <string>

namespace qorai_ads {

struct CreativeNotificationAdInfo;
struct NotificationAdInfo;

NotificationAdInfo BuildNotificationAd(
    const CreativeNotificationAdInfo& creative_ad);

NotificationAdInfo BuildNotificationAd(
    const CreativeNotificationAdInfo& creative_ad,
    const std::string& placement_id);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_NOTIFICATION_AD_BUILDER_H_
