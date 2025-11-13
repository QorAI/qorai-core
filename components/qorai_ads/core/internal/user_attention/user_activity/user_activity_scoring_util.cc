/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_scoring_util.h"

#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_event_info.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_feature.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_manager.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_scoring.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_trigger_info.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_util.h"

namespace qorai_ads {

bool WasUserActive() {
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers(kUserActivityTriggers.Get());

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          kUserActivityTimeWindow.Get());

  return GetUserActivityScore(triggers, events) >= kUserActivityThreshold.Get();
}

}  // namespace qorai_ads
