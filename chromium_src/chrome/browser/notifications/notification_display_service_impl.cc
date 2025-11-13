/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/notifications/ads_notification_handler.h"

#define QORAI_ADD_QORAI_ADS_NOTIFICATION_HANDLER \
  AddNotificationHandler(                        \
      NotificationHandler::Type::QORAI_ADS,      \
      std::make_unique<qorai_ads::AdsNotificationHandler>(*profile));
#include <chrome/browser/notifications/notification_display_service_impl.cc>
#undef QORAI_ADD_QORAI_ADS_NOTIFICATION_HANDLER
