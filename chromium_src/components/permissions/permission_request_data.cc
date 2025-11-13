/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "components/permissions/permission_request_data.h"

#include <optional>

#include "components/permissions/content_setting_permission_context_base.h"

namespace permissions {

std::optional<RequestType> ContentSettingsTypeToRequestTypeIfExists_QoraiImpl(
    ContentSettingsType content_settings_type) {
  switch (content_settings_type) {
    case ContentSettingsType::QORAI_ETHEREUM:
      return RequestType::kQoraiEthereum;
    case ContentSettingsType::QORAI_SOLANA:
      return RequestType::kQoraiSolana;
    case ContentSettingsType::QORAI_GOOGLE_SIGN_IN:
      return RequestType::kQoraiGoogleSignInPermission;
    case ContentSettingsType::QORAI_LOCALHOST_ACCESS:
      return RequestType::kQoraiLocalhostAccessPermission;
    case ContentSettingsType::QORAI_OPEN_AI_CHAT:
      return RequestType::kQoraiOpenAIChat;
    case ContentSettingsType::QORAI_CARDANO:
      return RequestType::kQoraiCardano;
    default:
      return ContentSettingsTypeToRequestTypeIfExists(content_settings_type);
  }
}

}  // namespace permissions

#define PermissionContextBase PermissionContextBase_ChromiumImpl

#define ContentSettingsTypeToRequestTypeIfExists \
  ContentSettingsTypeToRequestTypeIfExists_QoraiImpl

#include <components/permissions/permission_request_data.cc>

#undef ContentSettingsTypeToRequestTypeIfExists
#undef PermissionContextBase
