/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UTIL_TIME_UTIL_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UTIL_TIME_UTIL_H_

#include "base/time/time.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"

namespace qorai_rewards::internal {
namespace util {

mojom::ActivityMonth GetCurrentMonth();

mojom::ActivityMonth GetMonth(const base::Time& time);

uint32_t GetCurrentYear();

uint32_t GetYear(const base::Time& time);

uint64_t GetCurrentTimeStamp();

base::TimeDelta GetRandomizedDelay(base::TimeDelta delay);

base::TimeDelta GetRandomizedDelayWithBackoff(base::TimeDelta delay,
                                              base::TimeDelta max_delay,
                                              int backoff_count);

}  // namespace util
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UTIL_TIME_UTIL_H_
