/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_MINIMUM_WAIT_TIME_PERMISSION_RULE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_MINIMUM_WAIT_TIME_PERMISSION_RULE_H_

#include <cstddef>
#include <vector>

namespace base {
class Time;
class TimeDelta;
}  // namespace base

namespace qorai_ads {

bool HasMinimumWaitTimePermission(const std::vector<base::Time>& history,
                                  base::TimeDelta time_constraint);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_MINIMUM_WAIT_TIME_PERMISSION_RULE_H_
