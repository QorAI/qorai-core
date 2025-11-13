/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/calendar/calendar_util.h"

#include "base/time/time.h"

namespace qorai_ads {

int DayOfWeek(base::Time time, bool is_local) {
  base::Time::Exploded exploded;

  if (is_local) {
    time.LocalExplode(&exploded);
  } else {
    time.UTCExplode(&exploded);
  }

  return exploded.day_of_week;
}

}  // namespace qorai_ads
