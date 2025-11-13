/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_PUBLIC_COMMON_PERMISSIONS_PERMISSION_UTILS_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_PUBLIC_COMMON_PERMISSIONS_PERMISSION_UTILS_H_

// clang-format off
#define NUM                         \
  QORAI_ADS,                        \
  QORAI_TRACKERS,                   \
  QORAI_HTTP_UPGRADABLE_RESOURCES,  \
  QORAI_FINGERPRINTING_V2,          \
  QORAI_SHIELDS,                    \
  QORAI_REFERRERS,                  \
  QORAI_COOKIES,                    \
  QORAI_SPEEDREADER,                \
  QORAI_ETHEREUM,                   \
  QORAI_SOLANA,                     \
  QORAI_GOOGLE_SIGN_IN,             \
  QORAI_LOCALHOST_ACCESS,           \
  QORAI_OPEN_AI_CHAT,               \
  QORAI_CARDANO,                    \
  NUM
// clang-format on

#include <third_party/blink/public/common/permissions/permission_utils.h>  // IWYU pragma: export
#undef NUM

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_PUBLIC_COMMON_PERMISSIONS_PERMISSION_UTILS_H_
