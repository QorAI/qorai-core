/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_FACTORY_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_FACTORY_H_

#include <memory>

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_interface.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

struct NotificationAdInfo;

class NotificationAdEventFactory final {
 public:
  static std::unique_ptr<AdEventInterface<NotificationAdInfo>> Build(
      mojom::NotificationAdEventType mojom_ad_event_type);
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_FACTORY_H_
