/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_IDLE_DETECTION_USER_IDLE_DETECTION_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_IDLE_DETECTION_USER_IDLE_DETECTION_UTIL_H_

namespace base {
class TimeDelta;
}  // namespace base

namespace qorai_ads {

bool MaybeScreenWasLocked(bool screen_was_locked);

bool HasExceededMaximumIdleTime(base::TimeDelta idle_time);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ATTENTION_USER_IDLE_DETECTION_USER_IDLE_DETECTION_UTIL_H_
