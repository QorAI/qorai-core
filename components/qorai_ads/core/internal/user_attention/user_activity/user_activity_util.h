/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_UTIL_H_

#include <cstddef>
#include <string>

#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_event_info.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_event_types.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_trigger_info.h"

namespace qorai_ads {

size_t GetNumberOfUserActivityEvents(const UserActivityEventList& events,
                                     UserActivityEventType event_type);
base::TimeDelta GetTimeSinceLastUserActivityEvent(
    const UserActivityEventList& events,
    UserActivityEventType event_type);

UserActivityTriggerList ToUserActivityTriggers(const std::string& param_value);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_UTIL_H_
