/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_SCORING_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_SCORING_H_

#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_event_info.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_trigger_info.h"

namespace qorai_ads {

double GetUserActivityScore(const UserActivityTriggerList& triggers,
                            const UserActivityEventList& events);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_SCORING_H_
