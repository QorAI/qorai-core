// Copyright (c) 2023 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/permissions/contexts/qorai_localhost_permission_context.h"

#include <utility>

#include "components/content_settings/browser/page_specific_content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/permissions/permission_request_id.h"

namespace permissions {

QorAILocalhostPermissionContext::QorAILocalhostPermissionContext(
    content::BrowserContext* browser_context)
    : ContentSettingPermissionContextBase(
          browser_context,
          ContentSettingsType::QORAI_LOCALHOST_ACCESS,
          network::mojom::PermissionsPolicyFeature::kNotFound) {}

QorAILocalhostPermissionContext::~QorAILocalhostPermissionContext() = default;

bool QorAILocalhostPermissionContext::IsRestrictedToSecureOrigins() const {
  return false;
}
}  // namespace permissions
