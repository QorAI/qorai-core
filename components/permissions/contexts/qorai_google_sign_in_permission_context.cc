// Copyright (c) 2022 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/permissions/contexts/qorai_google_sign_in_permission_context.h"

#include <utility>

#include "components/content_settings/browser/page_specific_content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/permissions/permission_request_id.h"

namespace permissions {

QorAIGoogleSignInPermissionContext::QorAIGoogleSignInPermissionContext(
    content::BrowserContext* browser_context)
    : ContentSettingPermissionContextBase(
          browser_context,
          ContentSettingsType::QORAI_GOOGLE_SIGN_IN,
          network::mojom::PermissionsPolicyFeature::kNotFound) {}

QorAIGoogleSignInPermissionContext::~QorAIGoogleSignInPermissionContext() =
    default;

bool QorAIGoogleSignInPermissionContext::IsRestrictedToSecureOrigins() const {
  return false;
}
}  // namespace permissions
