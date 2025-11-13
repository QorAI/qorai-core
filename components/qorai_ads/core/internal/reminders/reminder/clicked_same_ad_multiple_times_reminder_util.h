/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_REMINDERS_REMINDER_CLICKED_SAME_AD_MULTIPLE_TIMES_REMINDER_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_REMINDERS_REMINDER_CLICKED_SAME_AD_MULTIPLE_TIMES_REMINDER_UTIL_H_

#include <string>

#include "qorai/components/qorai_ads/core/public/history/ad_history_item_info.h"

namespace qorai_ads {

bool ShouldRemindUser();

bool DidUserClickTheSameAdMultipleTimes(const std::string& creative_instance_id,
                                        const AdHistoryList& ad_history);

void RemindUserTheyDoNotNeedToClickToEarnRewards();

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_REMINDERS_REMINDER_CLICKED_SAME_AD_MULTIPLE_TIMES_REMINDER_UTIL_H_
