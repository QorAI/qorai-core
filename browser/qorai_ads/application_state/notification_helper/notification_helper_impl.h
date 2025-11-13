/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_H_
#define QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_H_

#include "base/functional/callback_forward.h"

namespace qorai_ads {

class NotificationHelperImpl {
 public:
  NotificationHelperImpl(const NotificationHelperImpl&) = delete;
  NotificationHelperImpl& operator=(const NotificationHelperImpl&) = delete;

  virtual ~NotificationHelperImpl();

  virtual void InitSystemNotifications(base::OnceClosure callback);

  virtual bool CanShowNotifications();
  virtual bool CanShowSystemNotificationsWhileBrowserIsBackgrounded() const;

  virtual bool ShowOnboardingNotification();

 protected:
  friend class NotificationHelper;

  NotificationHelperImpl();
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_NOTIFICATION_HELPER_NOTIFICATION_HELPER_IMPL_H_
