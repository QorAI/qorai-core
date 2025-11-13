/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "components/permissions/permission_util.h"

#include "components/permissions/permission_uma_util.h"
#include "third_party/blink/public/common/permissions/permission_utils.h"

#define PermissionUtil PermissionUtil_ChromiumImpl

// Since we don't do UMA just reuse an existing UMA type instead of adding one.
#define QORAI_GET_UMA_VALUE_FOR_REQUEST_TYPE         \
  case RequestType::kWidevine:                       \
  case RequestType::kQoraiEthereum:                  \
  case RequestType::kQoraiSolana:                    \
  case RequestType::kQoraiCardano:                   \
  case RequestType::kQoraiGoogleSignInPermission:    \
  case RequestType::kQoraiLocalhostAccessPermission: \
  case RequestType::kQoraiOpenAIChat:                \
    return RequestTypeForUma::PERMISSION_VR;

// These requests may be batched together, so we must handle them explicitly as
// GetUmaValueForRequests expects only a few specific request types to be
// batched
#define QORAI_GET_UMA_VALUE_FOR_REQUESTS             \
  if (request_type >= RequestType::kQoraiMinValue && \
      request_type <= RequestType::kQoraiMaxValue) { \
    return GetUmaValueForRequestType(request_type);  \
  }

#define PERMISSION_UTIL_PERMISSION_TYPE_TO_CONTENT_SETTINGS_TYPE \
  case PermissionType::QORAI_ADS:                                \
    return ContentSettingsType::QORAI_ADS;                       \
  case PermissionType::QORAI_TRACKERS:                           \
    return ContentSettingsType::QORAI_TRACKERS;                  \
  case PermissionType::QORAI_HTTP_UPGRADABLE_RESOURCES:          \
    return ContentSettingsType::QORAI_HTTP_UPGRADABLE_RESOURCES; \
  case PermissionType::QORAI_FINGERPRINTING_V2:                  \
    return ContentSettingsType::QORAI_FINGERPRINTING_V2;         \
  case PermissionType::QORAI_SHIELDS:                            \
    return ContentSettingsType::QORAI_SHIELDS;                   \
  case PermissionType::QORAI_REFERRERS:                          \
    return ContentSettingsType::QORAI_REFERRERS;                 \
  case PermissionType::QORAI_COOKIES:                            \
    return ContentSettingsType::QORAI_COOKIES;                   \
  case PermissionType::QORAI_SPEEDREADER:                        \
    return ContentSettingsType::QORAI_SPEEDREADER;               \
  case PermissionType::QORAI_ETHEREUM:                           \
    return ContentSettingsType::QORAI_ETHEREUM;                  \
  case PermissionType::QORAI_SOLANA:                             \
    return ContentSettingsType::QORAI_SOLANA;                    \
  case PermissionType::QORAI_GOOGLE_SIGN_IN:                     \
    return ContentSettingsType::QORAI_GOOGLE_SIGN_IN;            \
  case PermissionType::QORAI_LOCALHOST_ACCESS:                   \
    return ContentSettingsType::QORAI_LOCALHOST_ACCESS;          \
  case PermissionType::QORAI_OPEN_AI_CHAT:                       \
    return ContentSettingsType::QORAI_OPEN_AI_CHAT;              \
  case PermissionType::QORAI_CARDANO:                            \
    return ContentSettingsType::QORAI_CARDANO;

#include <components/permissions/permission_util.cc>
#undef PermissionUtil
#undef QORAI_GET_UMA_VALUE_FOR_REQUEST_TYPE
#undef QORAI_GET_UMA_VALUE_FOR_REQUESTS
#undef PERMISSION_UTIL_PERMISSION_TYPE_TO_CONTENT_SETTINGS_TYPE

namespace permissions {

// static
std::string PermissionUtil::GetPermissionString(
    ContentSettingsType content_type) {
  switch (content_type) {
    case ContentSettingsType::QORAI_ETHEREUM:
      return "QoraiEthereum";
    case ContentSettingsType::QORAI_SOLANA:
      return "QoraiSolana";
    case ContentSettingsType::QORAI_GOOGLE_SIGN_IN:
      return "QoraiGoogleSignInPermission";
    case ContentSettingsType::QORAI_LOCALHOST_ACCESS:
      return "QoraiLocalhostAccessPermission";
    case ContentSettingsType::QORAI_OPEN_AI_CHAT:
      return "QoraiOpenAIChatPermission";
    case ContentSettingsType::QORAI_CARDANO:
      return "QoraiCardano";
    default:
      return PermissionUtil_ChromiumImpl::GetPermissionString(content_type);
  }
}

// static
bool PermissionUtil::GetPermissionType(ContentSettingsType type,
                                       blink::PermissionType* out) {
  if (type == ContentSettingsType::QORAI_ETHEREUM ||
      type == ContentSettingsType::QORAI_SOLANA ||
      type == ContentSettingsType::QORAI_CARDANO) {
    *out = PermissionType::WINDOW_MANAGEMENT;
    return true;
  }
  if (type == ContentSettingsType::QORAI_GOOGLE_SIGN_IN) {
    *out = PermissionType::QORAI_GOOGLE_SIGN_IN;
    return true;
  }
  if (type == ContentSettingsType::QORAI_LOCALHOST_ACCESS) {
    *out = PermissionType::QORAI_LOCALHOST_ACCESS;
    return true;
  }
  if (type == ContentSettingsType::QORAI_OPEN_AI_CHAT) {
    *out = PermissionType::QORAI_OPEN_AI_CHAT;
    return true;
  }

  return PermissionUtil_ChromiumImpl::GetPermissionType(type, out);
}

// static
bool PermissionUtil::IsPermission(ContentSettingsType type) {
  switch (type) {
    case ContentSettingsType::QORAI_ETHEREUM:
    case ContentSettingsType::QORAI_SOLANA:
    case ContentSettingsType::QORAI_CARDANO:
    case ContentSettingsType::QORAI_GOOGLE_SIGN_IN:
    case ContentSettingsType::QORAI_LOCALHOST_ACCESS:
    case ContentSettingsType::QORAI_OPEN_AI_CHAT:
      return true;
    default:
      return PermissionUtil_ChromiumImpl::IsPermission(type);
  }
}

PermissionType PermissionUtil::ContentSettingsTypeToPermissionType(
    ContentSettingsType permission) {
  switch (permission) {
    case ContentSettingsType::QORAI_ADS:
      return PermissionType::QORAI_ADS;
    case ContentSettingsType::QORAI_TRACKERS:
      return PermissionType::QORAI_TRACKERS;
    case ContentSettingsType::QORAI_HTTP_UPGRADABLE_RESOURCES:
      return PermissionType::QORAI_HTTP_UPGRADABLE_RESOURCES;
    case ContentSettingsType::QORAI_FINGERPRINTING_V2:
      return PermissionType::QORAI_FINGERPRINTING_V2;
    case ContentSettingsType::QORAI_SHIELDS:
      return PermissionType::QORAI_SHIELDS;
    case ContentSettingsType::QORAI_REFERRERS:
      return PermissionType::QORAI_REFERRERS;
    case ContentSettingsType::QORAI_COOKIES:
      return PermissionType::QORAI_COOKIES;
    case ContentSettingsType::QORAI_SPEEDREADER:
      return PermissionType::QORAI_SPEEDREADER;
    case ContentSettingsType::QORAI_ETHEREUM:
      return PermissionType::QORAI_ETHEREUM;
    case ContentSettingsType::QORAI_SOLANA:
      return PermissionType::QORAI_SOLANA;
    case ContentSettingsType::QORAI_GOOGLE_SIGN_IN:
      return PermissionType::QORAI_GOOGLE_SIGN_IN;
    case ContentSettingsType::QORAI_LOCALHOST_ACCESS:
      return PermissionType::QORAI_LOCALHOST_ACCESS;
    case ContentSettingsType::QORAI_OPEN_AI_CHAT:
      return PermissionType::QORAI_OPEN_AI_CHAT;
    case ContentSettingsType::QORAI_CARDANO:
      return PermissionType::QORAI_CARDANO;
    default:
      return PermissionUtil_ChromiumImpl::ContentSettingsTypeToPermissionType(
          permission);
  }
}

GURL PermissionUtil::GetCanonicalOrigin(ContentSettingsType permission,
                                        const GURL& requesting_origin,
                                        const GURL& embedding_origin) {
  // Use requesting_origin which will have ethereum or solana address info.
  if (permission == ContentSettingsType::QORAI_ETHEREUM ||
      permission == ContentSettingsType::QORAI_SOLANA ||
      permission == ContentSettingsType::QORAI_CARDANO) {
    return requesting_origin;
  }

  return PermissionUtil_ChromiumImpl::GetCanonicalOrigin(
      permission, requesting_origin, embedding_origin);
}

}  // namespace permissions
