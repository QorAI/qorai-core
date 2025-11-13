/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_events.h"

#include <utility>

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_events_database_table.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/ad_info.h"

namespace qorai_ads {

void RecordAdEvent(const AdInfo& ad,
                   mojom::ConfirmationType mojom_confirmation_type,
                   AdEventCallback callback) {
  RecordAdEvent(BuildAdEvent(ad, mojom_confirmation_type,
                             /*created_at=*/base::Time::Now()),
                std::move(callback));
}

void RecordAdEvent(const AdEventInfo& ad_event, AdEventCallback callback) {
  database::table::AdEvents database_table;
  database_table.RecordEvent(ad_event, std::move(callback));
}

void PurgeOrphanedAdEvents(mojom::AdType mojom_ad_type,
                           AdEventCallback callback) {
  const database::table::AdEvents database_table;
  database_table.PurgeOrphaned(mojom_ad_type, std::move(callback));
}

void PurgeOrphanedAdEvents(const std::vector<std::string>& placement_ids,
                           AdEventCallback callback) {
  const database::table::AdEvents database_table;
  database_table.PurgeOrphaned(placement_ids, std::move(callback));
}

}  // namespace qorai_ads
