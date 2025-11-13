/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/promoted_content_ads/promoted_content_ad_event_factory.h"

#include "qorai/components/qorai_ads/core/internal/ad_units/promoted_content_ad/promoted_content_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/promoted_content_ads/promoted_content_ad_event_clicked.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/promoted_content_ads/promoted_content_ad_event_served.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/promoted_content_ads/promoted_content_ad_event_viewed.h"

namespace qorai_ads {

std::unique_ptr<AdEventInterface<PromotedContentAdInfo>>
PromotedContentAdEventFactory::Build(
    mojom::PromotedContentAdEventType mojom_ad_event_type) {
  switch (mojom_ad_event_type) {
    case mojom::PromotedContentAdEventType::kServedImpression: {
      return std::make_unique<PromotedContentAdEventServed>();
    }

    case mojom::PromotedContentAdEventType::kViewedImpression: {
      return std::make_unique<PromotedContentAdEventViewed>();
    }

    case mojom::PromotedContentAdEventType::kClicked: {
      return std::make_unique<PromotedContentAdEventClicked>();
    }
  }
}

}  // namespace qorai_ads
