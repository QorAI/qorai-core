/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_EXTENSIONS_BROWSER_EXTENSION_EVENT_HISTOGRAM_VALUE_H_
#define QORAI_CHROMIUM_SRC_EXTENSIONS_BROWSER_EXTENSION_EVENT_HISTOGRAM_VALUE_H_

// clang-format off
#define ENUM_BOUNDARY                         \
  QORAI_START = 600,                          \
  QORAI_AD_BLOCKED,                           \
  QORAI_WALLET_CREATED,                       \
  QORAI_ON_WALLET_PROPERTIES,                 \
  QORAI_ON_PUBLISHER_DATA,                    \
  QORAI_ON_CURRENT_REPORT,                    \
  QORAI_ON_QORAI_THEME_TYPE_CHANGED,          \
  QORAI_REWARDS_NOTIFICATION_ADDED,           \
  QORAI_REWARDS_NOTIFICATION_DELETED,         \
  QORAI_REWARDS_ALL_NOTIFICATIONS_DELETED,    \
  QORAI_REWARDS_GET_NOTIFICATION,             \
  QORAI_REWARDS_GET_ALL_NOTIFICATIONS,        \
  QORAI_WALLET_FAILED,                        \
  ENUM_BOUNDARY
// clang-format on

#include <extensions/browser/extension_event_histogram_value.h>  // IWYU pragma: export

#undef ENUM_BOUNDARY

#endif  // QORAI_CHROMIUM_SRC_EXTENSIONS_BROWSER_EXTENSION_EVENT_HISTOGRAM_VALUE_H_
