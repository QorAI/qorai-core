/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_BUILDER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_BUILDER_H_

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace base {
class Time;
}  // namespace base

namespace qorai_ads {

struct AdEventInfo;
struct AdInfo;

// Builds a new `AdEventInfo` for the given `ad`, `mojom_confirmation_type`, and
// `created_at` time.
AdEventInfo BuildAdEvent(const AdInfo& ad,
                         mojom::ConfirmationType mojom_confirmation_type,
                         base::Time created_at);

// Rebuilds an existing `AdEventInfo` with a new `mojom_confirmation_type` and
// `created_at` time.
AdEventInfo RebuildAdEvent(const AdEventInfo& ad_event,
                           mojom::ConfirmationType mojom_confirmation_type,
                           base::Time created_at);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_BUILDER_H_
