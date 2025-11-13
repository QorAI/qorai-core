/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_BROWSER_ANALYTICS_P3A_NOTIFICATION_AD_H_
#define QORAI_COMPONENTS_QORAI_ADS_BROWSER_ANALYTICS_P3A_NOTIFICATION_AD_H_

class PrefService;

namespace qorai_ads {

inline constexpr char kNotificationAdPositionHistogramName[] =
    "Qorai.Rewards.CustomNotificationAdPosition";

void RecordNotificationAdPositionMetric(bool should_show_custom_notification,
                                        PrefService* profile_prefs);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_BROWSER_ANALYTICS_P3A_NOTIFICATION_AD_H_
