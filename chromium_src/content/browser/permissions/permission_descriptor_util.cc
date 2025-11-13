/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "content/public/browser/permission_descriptor_util.h"

#define NUM                                                                   \
  QORAI_ADS:                                                                  \
  return CreatePermissionDescriptor(blink::mojom::PermissionName::QORAI_ADS); \
  case blink::PermissionType::QORAI_TRACKERS:                                 \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_TRACKERS);                        \
  case blink::PermissionType::QORAI_HTTP_UPGRADABLE_RESOURCES:                \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_HTTP_UPGRADABLE_RESOURCES);       \
  case blink::PermissionType::QORAI_FINGERPRINTING_V2:                        \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_FINGERPRINTING_V2);               \
  case blink::PermissionType::QORAI_SHIELDS:                                  \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_SHIELDS);                         \
  case blink::PermissionType::QORAI_REFERRERS:                                \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_REFERRERS);                       \
  case blink::PermissionType::QORAI_COOKIES:                                  \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_COOKIES);                         \
  case blink::PermissionType::QORAI_SPEEDREADER:                              \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_SPEEDREADER);                     \
  case blink::PermissionType::QORAI_ETHEREUM:                                 \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_ETHEREUM);                        \
  case blink::PermissionType::QORAI_SOLANA:                                   \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_SOLANA);                          \
  case blink::PermissionType::QORAI_GOOGLE_SIGN_IN:                           \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_GOOGLE_SIGN_IN);                  \
  case blink::PermissionType::QORAI_LOCALHOST_ACCESS:                         \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_LOCALHOST_ACCESS);                \
  case blink::PermissionType::QORAI_OPEN_AI_CHAT:                             \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_OPEN_AI_CHAT);                    \
  case blink::PermissionType::QORAI_CARDANO:                                  \
    return CreatePermissionDescriptor(                                        \
        blink::mojom::PermissionName::QORAI_CARDANO);                         \
  case blink::PermissionType::NUM

#include <content/browser/permissions/permission_descriptor_util.cc>

#undef NUM
