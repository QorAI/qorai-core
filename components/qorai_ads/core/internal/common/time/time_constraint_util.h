/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TIME_TIME_CONSTRAINT_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TIME_TIME_CONSTRAINT_UTIL_H_

#include <cstddef>
#include <vector>

namespace base {
class Time;
class TimeDelta;
}  // namespace base

namespace qorai_ads {

// Check if the `history` of time points respects a certain `time_constraint`
// and a `cap` on the number of elements. Assumes that `history` is in
// chronological order.
bool DoesHistoryRespectRollingTimeConstraint(
    const std::vector<base::Time>& history,
    base::TimeDelta time_constraint,
    size_t cap);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TIME_TIME_CONSTRAINT_UTIL_H_
