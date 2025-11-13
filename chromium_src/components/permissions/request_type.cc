/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "components/permissions/request_type.h"

#include <optional>

#include "build/build_config.h"

#if BUILDFLAG(IS_ANDROID)
#include "components/resources/android/theme_resources.h"
#else
#include "components/vector_icons/vector_icons.h"
#include "ui/gfx/vector_icon_types.h"
#endif

#if BUILDFLAG(IS_ANDROID)
namespace {
constexpr auto kAndroidStorageAccess = IDR_ANDROID_STORAGE_ACCESS;
}  // namespace
#endif

// Add Qorai cases into GetIconIdAndroid.
// TODO(jocelyn): Might need to update icon when we have ethereum.enable UI
// support in Android.
#define IDR_ANDROID_STORAGE_ACCESS                   \
  kAndroidStorageAccess;                             \
  case RequestType::kWidevine:                       \
  case RequestType::kQoraiEthereum:                  \
  case RequestType::kQoraiSolana:                    \
  case RequestType::kQoraiCardano:                   \
  case RequestType::kQoraiGoogleSignInPermission:    \
  case RequestType::kQoraiLocalhostAccessPermission: \
  case RequestType::kQoraiOpenAIChat:                \
    return IDR_ANDROID_INFOBAR_PERMISSION_COOKIE

// Add Qorai cases into GetIconIdDesktop.
#define kStorageAccessIcon                           \
  kStorageAccessIcon;                                \
  case RequestType::kWidevine:                       \
  case RequestType::kQoraiEthereum:                  \
  case RequestType::kQoraiSolana:                    \
  case RequestType::kQoraiCardano:                   \
  case RequestType::kQoraiGoogleSignInPermission:    \
  case RequestType::kQoraiLocalhostAccessPermission: \
  case RequestType::kQoraiOpenAIChat:                \
    return vector_icons::kExtensionIcon

#define QORAI_PERMISSION_KEY_FOR_REQUEST_TYPE                     \
  case permissions::RequestType::kWidevine:                       \
    return "widevine";                                            \
  case permissions::RequestType::kQoraiEthereum:                  \
    return "qorai_ethereum";                                      \
  case permissions::RequestType::kQoraiSolana:                    \
    return "qorai_solana";                                        \
  case permissions::RequestType::kQoraiCardano:                   \
    return "qorai_cardano";                                       \
  case permissions::RequestType::kQoraiGoogleSignInPermission:    \
    return "qorai_google_sign_in";                                \
  case permissions::RequestType::kQoraiLocalhostAccessPermission: \
    return "qorai_localhost_access";                              \
  case permissions::RequestType::kQoraiOpenAIChat:                \
    return "qorai_ai_chat";

#define ContentSettingsTypeToRequestType \
  ContentSettingsTypeToRequestType_ChromiumImpl

#define RequestTypeToContentSettingsType \
  RequestTypeToContentSettingsType_ChromiumImpl

#define IsRequestablePermissionType IsRequestablePermissionType_ChromiumImpl

#include <components/permissions/request_type.cc>

#undef IsRequestablePermissionType
#undef RequestTypeToContentSettingsType
#undef ContentSettingsTypeToRequestType
#undef QORAI_PERMISSION_KEY_FOR_REQUEST_TYPE
#undef kStorageAccessIcon
#undef IDR_ANDROID_STORAGE_ACCESS

namespace permissions {

RequestType ContentSettingsTypeToRequestType(
    ContentSettingsType content_settings_type) {
  switch (content_settings_type) {
    case ContentSettingsType::QORAI_ETHEREUM:
      return RequestType::kQoraiEthereum;
    case ContentSettingsType::QORAI_SOLANA:
      return RequestType::kQoraiSolana;
    case ContentSettingsType::QORAI_CARDANO:
      return RequestType::kQoraiCardano;
    case ContentSettingsType::QORAI_GOOGLE_SIGN_IN:
      return RequestType::kQoraiGoogleSignInPermission;
    case ContentSettingsType::QORAI_LOCALHOST_ACCESS:
      return RequestType::kQoraiLocalhostAccessPermission;
    case ContentSettingsType::QORAI_OPEN_AI_CHAT:
      return RequestType::kQoraiOpenAIChat;
    case ContentSettingsType::DEFAULT:
      // Currently we have only one DEFAULT type that is
      // not mapped, which is Widevine, it's used for
      // UMA purpose only
      return RequestType::kWidevine;
    default:
      return ContentSettingsTypeToRequestType_ChromiumImpl(
          content_settings_type);
  }
}

std::optional<ContentSettingsType> RequestTypeToContentSettingsType(
    RequestType request_type) {
  switch (request_type) {
    case RequestType::kQoraiGoogleSignInPermission:
      return ContentSettingsType::QORAI_GOOGLE_SIGN_IN;
    case RequestType::kQoraiLocalhostAccessPermission:
      return ContentSettingsType::QORAI_LOCALHOST_ACCESS;
    case RequestType::kQoraiEthereum:
      return ContentSettingsType::QORAI_ETHEREUM;
    case RequestType::kQoraiSolana:
      return ContentSettingsType::QORAI_SOLANA;
    case RequestType::kQoraiOpenAIChat:
      return ContentSettingsType::QORAI_OPEN_AI_CHAT;
    case RequestType::kQoraiCardano:
      return ContentSettingsType::QORAI_CARDANO;
    default:
      return RequestTypeToContentSettingsType_ChromiumImpl(request_type);
  }
}

bool IsRequestablePermissionType(ContentSettingsType content_settings_type) {
  switch (content_settings_type) {
    case ContentSettingsType::QORAI_GOOGLE_SIGN_IN:
    case ContentSettingsType::QORAI_LOCALHOST_ACCESS:
    case ContentSettingsType::QORAI_ETHEREUM:
    case ContentSettingsType::QORAI_SOLANA:
    case ContentSettingsType::QORAI_OPEN_AI_CHAT:
    case ContentSettingsType::QORAI_CARDANO:
      return true;
    default:
      return IsRequestablePermissionType_ChromiumImpl(content_settings_type);
  }
}

}  // namespace permissions
