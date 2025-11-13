/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "components/permissions/permission_util.h"
#include "third_party/blink/public/common/permissions/permission_utils.h"

#define NUM                                             \
  QORAI_ADS:                                            \
  case PermissionType::QORAI_TRACKERS:                  \
  case PermissionType::QORAI_HTTP_UPGRADABLE_RESOURCES: \
  case PermissionType::QORAI_FINGERPRINTING_V2:         \
  case PermissionType::QORAI_SHIELDS:                   \
  case PermissionType::QORAI_REFERRERS:                 \
  case PermissionType::QORAI_COOKIES:                   \
  case PermissionType::QORAI_SPEEDREADER:               \
  case PermissionType::QORAI_ETHEREUM:                  \
  case PermissionType::QORAI_SOLANA:                    \
  case PermissionType::QORAI_GOOGLE_SIGN_IN:            \
  case PermissionType::QORAI_LOCALHOST_ACCESS:          \
  case PermissionType::QORAI_OPEN_AI_CHAT:              \
  case PermissionType::QORAI_CARDANO:                   \
  case PermissionType::NUM

#include <content/shell/browser/shell_permission_manager.cc>
#undef NUM
