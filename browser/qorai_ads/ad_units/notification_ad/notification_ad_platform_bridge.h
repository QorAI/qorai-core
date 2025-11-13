/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_PLATFORM_BRIDGE_H_
#define QORAI_BROWSER_QORAI_ADS_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_PLATFORM_BRIDGE_H_

#include <string>

#include "base/memory/raw_ref.h"
#include "qorai/browser/ui/qorai_ads/notification_ad.h"
#include "chrome/browser/profiles/profile.h"

namespace qorai_ads {

class NotificationAdPlatformBridge {
 public:
  explicit NotificationAdPlatformBridge(Profile& profile);

  NotificationAdPlatformBridge(const NotificationAdPlatformBridge&) = delete;
  NotificationAdPlatformBridge& operator=(const NotificationAdPlatformBridge&) =
      delete;

  ~NotificationAdPlatformBridge() = default;

  void ShowNotificationAd(NotificationAd notification_ad);
  void CloseNotificationAd(const std::string& notification_id);

 private:
  const raw_ref<Profile> profile_;
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_PLATFORM_BRIDGE_H_
