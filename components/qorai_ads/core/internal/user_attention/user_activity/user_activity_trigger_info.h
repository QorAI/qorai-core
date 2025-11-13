/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_TRIGGER_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_TRIGGER_INFO_H_

#include <string>
#include <vector>

namespace qorai_ads {

struct UserActivityTriggerInfo final {
  bool operator==(const UserActivityTriggerInfo&) const = default;

  std::string event_sequence;
  double score = 0.0;
};

using UserActivityTriggerList = std::vector<UserActivityTriggerInfo>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_TRIGGER_INFO_H_
