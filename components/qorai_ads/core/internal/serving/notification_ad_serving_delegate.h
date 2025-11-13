/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_NOTIFICATION_AD_SERVING_DELEGATE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_NOTIFICATION_AD_SERVING_DELEGATE_H_

#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"

namespace qorai_ads {

struct NotificationAdInfo;

class NotificationAdServingDelegate {
 public:
  // Invoked when an opportunity arises to serve a notification ad.
  virtual void OnOpportunityAroseToServeNotificationAd(
      const SegmentList& segments) {}

  // Invoked when a notification ad is served.
  virtual void OnDidServeNotificationAd(const NotificationAdInfo& ad) {}

  // Invoked when a notification ad fails to serve.
  virtual void OnFailedToServeNotificationAd() {}

 protected:
  virtual ~NotificationAdServingDelegate() = default;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_NOTIFICATION_AD_SERVING_DELEGATE_H_
