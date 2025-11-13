/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/inline_content_ads/inline_content_ad_event_viewed.h"

#include <utility>

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_events.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/inline_content_ad/inline_content_ad_info.h"

namespace qorai_ads {

void InlineContentAdEventViewed::FireEvent(const InlineContentAdInfo& ad,
                                           ResultCallback callback) {
  RecordAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                std::move(callback));
}

}  // namespace qorai_ads
