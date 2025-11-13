/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_PERMISSIONS_REQUEST_TYPE_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_PERMISSIONS_REQUEST_TYPE_H_

#define kStorageAccess                                                       \
  kStorageAccess, kWidevine, kQoraiEthereum, kQoraiSolana, kQoraiOpenAIChat, \
      kQoraiGoogleSignInPermission, kQoraiLocalhostAccessPermission,         \
      kQoraiCardano, kQoraiMinValue = kWidevine,                             \
                     kQoraiMaxValue = kQoraiCardano

#define ContentSettingsTypeToRequestType \
  ContentSettingsTypeToRequestType_ChromiumImpl

#define RequestTypeToContentSettingsType \
  RequestTypeToContentSettingsType_ChromiumImpl

#define IsRequestablePermissionType IsRequestablePermissionType_ChromiumImpl

#include <components/permissions/request_type.h>  // IWYU pragma: export

#include <optional>

#undef kStorageAccess
#undef ContentSettingsTypeToRequestType
#undef RequestTypeToContentSettingsType
#undef IsRequestablePermissionType

namespace permissions {

RequestType ContentSettingsTypeToRequestType(
    ContentSettingsType content_settings_type);

std::optional<ContentSettingsType> RequestTypeToContentSettingsType(
    RequestType request_type);

bool IsRequestablePermissionType(ContentSettingsType content_settings_type);

}  // namespace permissions

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_PERMISSIONS_REQUEST_TYPE_H_
