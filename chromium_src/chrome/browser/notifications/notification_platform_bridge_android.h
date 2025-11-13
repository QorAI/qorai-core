/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_NOTIFICATIONS_NOTIFICATION_PLATFORM_BRIDGE_ANDROID_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_NOTIFICATIONS_NOTIFICATION_PLATFORM_BRIDGE_ANDROID_H_

#define OnNotificationProcessed                              \
  Unused() {}                                                \
  friend class QoraiNotificationPlatformBridgeHelperAndroid; \
  void OnNotificationProcessed

#include <chrome/browser/notifications/notification_platform_bridge_android.h>  // IWYU pragma: export

#undef OnNotificationProcessed

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_NOTIFICATIONS_NOTIFICATION_PLATFORM_BRIDGE_ANDROID_H_
