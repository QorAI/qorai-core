/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_EVENT_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_EVENT_INFO_H_

#include "base/containers/circular_deque.h"
#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_event_types.h"

namespace qorai_ads {

struct UserActivityEventInfo final {
  bool operator==(const UserActivityEventInfo&) const = default;

  UserActivityEventType type;
  base::Time created_at;
};

using UserActivityEventList = base::circular_deque<UserActivityEventInfo>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_EVENT_INFO_H_
