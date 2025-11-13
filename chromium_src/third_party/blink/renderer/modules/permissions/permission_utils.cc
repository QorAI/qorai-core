/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "third_party/blink/renderer/modules/permissions/permission_utils.h"

#include "third_party/blink/renderer/core/workers/worker_global_scope.h"

#define WEB_PRINTING                                    \
  QORAI_ADS:                                            \
  return "qorai_ads";                                   \
  case PermissionName::QORAI_TRACKERS:                  \
    return "qorai_trackers";                            \
  case PermissionName::QORAI_HTTP_UPGRADABLE_RESOURCES: \
    return "qorai_http_upgradable_resources";           \
  case PermissionName::QORAI_FINGERPRINTING_V2:         \
    return "qorai_fingerprinting_v2";                   \
  case PermissionName::QORAI_SHIELDS:                   \
    return "qorai_shields";                             \
  case PermissionName::QORAI_REFERRERS:                 \
    return "qorai_referrers";                           \
  case PermissionName::QORAI_COOKIES:                   \
    return "qorai_cookies";                             \
  case PermissionName::QORAI_SPEEDREADER:               \
    return "qorai_speedreader";                         \
  case PermissionName::QORAI_ETHEREUM:                  \
    return "qorai_ethereum";                            \
  case PermissionName::QORAI_SOLANA:                    \
    return "qorai_solana";                              \
  case PermissionName::QORAI_GOOGLE_SIGN_IN:            \
    return "qorai_google_sign_in";                      \
  case PermissionName::QORAI_LOCALHOST_ACCESS:          \
    return "qorai_localhost_access";                    \
  case PermissionName::QORAI_OPEN_AI_CHAT:              \
    return "qorai_open_ai_chat";                        \
  case PermissionName::QORAI_CARDANO:                   \
    return "qorai_cardano";                             \
  case PermissionName::WEB_PRINTING

#include <third_party/blink/renderer/modules/permissions/permission_utils.cc>

#undef WEB_PRINTING
