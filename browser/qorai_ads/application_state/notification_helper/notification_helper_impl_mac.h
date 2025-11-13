/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_MAC_H_
#define QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_MAC_H_

#include "qorai/browser/qorai_ads/application_state/notification_helper/notification_helper_impl.h"

namespace qorai_ads {

class NotificationHelperImplMac final : public NotificationHelperImpl {
 public:
  NotificationHelperImplMac(const NotificationHelperImplMac&) = delete;
  NotificationHelperImplMac& operator=(const NotificationHelperImplMac&) =
      delete;

  ~NotificationHelperImplMac() override;

 protected:
  friend class NotificationHelper;

  NotificationHelperImplMac();

 private:
  // NotificationHelperImpl:
  bool CanShowNotifications() override;
  bool CanShowSystemNotificationsWhileBrowserIsBackgrounded() const override;

  bool ShowOnboardingNotification() override;
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_MAC_H_
