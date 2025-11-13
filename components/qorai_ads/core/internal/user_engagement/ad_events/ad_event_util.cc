/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_util.h"

#include "base/time/time.h"

namespace qorai_ads {

std::vector<base::Time> ToHistory(const AdEventList& ad_events) {
  std::vector<base::Time> history;
  history.reserve(ad_events.size());

  for (const auto& ad_event : ad_events) {
    if (ad_event.IsValid()) {
      history.push_back(*ad_event.created_at);
    }
  }

  return history;
}

}  // namespace qorai_ads
