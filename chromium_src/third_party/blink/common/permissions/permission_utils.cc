/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <optional>

#include "services/network/public/mojom/permissions_policy/permissions_policy_feature.mojom.h"

#define PERMISSION_UTIL_GET_PERMISSION_STRING           \
  case PermissionType::QORAI_ADS:                       \
    return "QoraiAds";                                  \
  case PermissionType::QORAI_TRACKERS:                  \
    return "QoraiTrackers";                             \
  case PermissionType::QORAI_HTTP_UPGRADABLE_RESOURCES: \
    return "QoraiHttpUpgradableResource";               \
  case PermissionType::QORAI_FINGERPRINTING_V2:         \
    return "QoraiFingerprintingV2";                     \
  case PermissionType::QORAI_SHIELDS:                   \
    return "QoraiShields";                              \
  case PermissionType::QORAI_REFERRERS:                 \
    return "QoraiReferrers";                            \
  case PermissionType::QORAI_COOKIES:                   \
    return "QoraiCookies";                              \
  case PermissionType::QORAI_SPEEDREADER:               \
    return "QoraiSpeedreaders";                         \
  case PermissionType::QORAI_GOOGLE_SIGN_IN:            \
    return "QoraiGoogleSignInPermission";               \
  case PermissionType::QORAI_LOCALHOST_ACCESS:          \
    return "QoraiLocalhostAccessPermission";            \
  case PermissionType::QORAI_OPEN_AI_CHAT:              \
    return "QoraiOpenAIChatPermission";                 \
  case PermissionType::QORAI_ETHEREUM:                  \
    return "QoraiEthereum";                             \
  case PermissionType::QORAI_SOLANA:                    \
    return "QoraiSolana";                               \
  case PermissionType::QORAI_CARDANO:                   \
    return "QoraiCardano";

#define kDisplayCapture                                         \
  kDisplayCapture;                                              \
  case PermissionType::QORAI_ETHEREUM:                          \
    return network::mojom::PermissionsPolicyFeature::kEthereum; \
  case PermissionType::QORAI_SOLANA:                            \
    return network::mojom::PermissionsPolicyFeature::kSolana;   \
  case PermissionType::QORAI_ADS:                               \
  case PermissionType::QORAI_TRACKERS:                          \
  case PermissionType::QORAI_HTTP_UPGRADABLE_RESOURCES:         \
  case PermissionType::QORAI_FINGERPRINTING_V2:                 \
  case PermissionType::QORAI_SHIELDS:                           \
  case PermissionType::QORAI_REFERRERS:                         \
  case PermissionType::QORAI_COOKIES:                           \
  case PermissionType::QORAI_SPEEDREADER:                       \
  case PermissionType::QORAI_GOOGLE_SIGN_IN:                    \
  case PermissionType::QORAI_LOCALHOST_ACCESS:                  \
  case PermissionType::QORAI_OPEN_AI_CHAT:                      \
    return std::nullopt;                                        \
  case PermissionType::QORAI_CARDANO:                           \
    return network::mojom::PermissionsPolicyFeature::kCardano

#define QORAI_PERMISSION_UTIL_PERMISSION_DESCRIPTOR_INFO_TO_PERMISSION_TYPE \
  case PermissionName::QORAI_ETHEREUM:                                      \
    return PermissionType::QORAI_ETHEREUM;                                  \
  case PermissionName::QORAI_SOLANA:                                        \
    return PermissionType::QORAI_SOLANA;                                    \
  case PermissionName::QORAI_ADS:                                           \
    return PermissionType::QORAI_ADS;                                       \
  case PermissionName::QORAI_TRACKERS:                                      \
    return PermissionType::QORAI_TRACKERS;                                  \
  case PermissionName::QORAI_HTTP_UPGRADABLE_RESOURCES:                     \
    return PermissionType::QORAI_HTTP_UPGRADABLE_RESOURCES;                 \
  case PermissionName::QORAI_FINGERPRINTING_V2:                             \
    return PermissionType::QORAI_FINGERPRINTING_V2;                         \
  case PermissionName::QORAI_SHIELDS:                                       \
    return PermissionType::QORAI_SHIELDS;                                   \
  case PermissionName::QORAI_REFERRERS:                                     \
    return PermissionType::QORAI_SHIELDS;                                   \
  case PermissionName::QORAI_COOKIES:                                       \
    return PermissionType::QORAI_COOKIES;                                   \
  case PermissionName::QORAI_SPEEDREADER:                                   \
    return PermissionType::QORAI_SPEEDREADER;                               \
  case PermissionName::QORAI_GOOGLE_SIGN_IN:                                \
    return PermissionType::QORAI_GOOGLE_SIGN_IN;                            \
  case PermissionName::QORAI_LOCALHOST_ACCESS:                              \
    return PermissionType::QORAI_LOCALHOST_ACCESS;                          \
  case PermissionName::QORAI_OPEN_AI_CHAT:                                  \
    return PermissionType::QORAI_OPEN_AI_CHAT;                              \
  case PermissionName::QORAI_CARDANO:                                       \
    return PermissionType::QORAI_CARDANO;

#include <third_party/blink/common/permissions/permission_utils.cc>
#undef QORAI_PERMISSION_UTIL_PERMISSION_DESCRIPTOR_INFO_TO_PERMISSION_TYPE
#undef kDisplayCapture
#undef PERMISSION_UTIL_GET_PERMISSION_STRING
