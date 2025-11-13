/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_attention/user_idle_detection/user_idle_detection_util.h"

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/public/user_attention/user_idle_detection/user_idle_detection_feature.h"

namespace qorai_ads {

bool MaybeScreenWasLocked(bool screen_was_locked) {
  return kShouldDetectScreenWasLocked.Get() && screen_was_locked;
}

bool HasExceededMaximumIdleTime(base::TimeDelta idle_time) {
  const base::TimeDelta maximum_idle_time = kMaximumUserIdleDetectionTime.Get();
  return maximum_idle_time.is_positive() && idle_time > maximum_idle_time;
}

}  // namespace qorai_ads
