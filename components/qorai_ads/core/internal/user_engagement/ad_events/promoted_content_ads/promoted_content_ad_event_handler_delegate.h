/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_PROMOTED_CONTENT_ADS_PROMOTED_CONTENT_AD_EVENT_HANDLER_DELEGATE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_PROMOTED_CONTENT_ADS_PROMOTED_CONTENT_AD_EVENT_HANDLER_DELEGATE_H_

#include <string>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

struct PromotedContentAdInfo;

class PromotedContentAdEventHandlerDelegate {
 public:
  // Invoked when the promoted content `ad` is served.
  virtual void OnDidFirePromotedContentAdServedEvent(
      const PromotedContentAdInfo& ad) {}

  // Invoked when the promoted content `ad` is viewed.
  virtual void OnDidFirePromotedContentAdViewedEvent(
      const PromotedContentAdInfo& ad) {}

  // Invoked when the promoted content `ad` is clicked.
  virtual void OnDidFirePromotedContentAdClickedEvent(
      const PromotedContentAdInfo& ad) {}

  // Invoked when the promoted content ad event fails for `placement_id`,
  // `creative_instance_id` and `mojom_ad_event_type`.
  virtual void OnFailedToFirePromotedContentAdEvent(
      const std::string& placement_id,
      const std::string& creative_instance_id,
      mojom::PromotedContentAdEventType mojom_ad_event_type) {}

 protected:
  virtual ~PromotedContentAdEventHandlerDelegate() = default;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_PROMOTED_CONTENT_ADS_PROMOTED_CONTENT_AD_EVENT_HANDLER_DELEGATE_H_
