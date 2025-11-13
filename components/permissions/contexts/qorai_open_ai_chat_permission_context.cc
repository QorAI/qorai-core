// Copyright (c) 2024 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/permissions/contexts/qorai_open_ai_chat_permission_context.h"

#include <utility>

#include "qorai/qorai_domains/service_domains.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/permissions/permission_request_data.h"
#include "services/network/public/mojom/permissions_policy/permissions_policy_feature.mojom-shared.h"
#include "url/gurl.h"
#include "url/url_constants.h"

namespace permissions {

QorAIOpenAIChatPermissionContext::QorAIOpenAIChatPermissionContext(
    content::BrowserContext* browser_context)
    : ContentSettingPermissionContextBase(
          browser_context,
          ContentSettingsType::QORAI_OPEN_AI_CHAT,
          network::mojom::PermissionsPolicyFeature::kNotFound) {}

QorAIOpenAIChatPermissionContext::~QorAIOpenAIChatPermissionContext() = default;

ContentSetting
QorAIOpenAIChatPermissionContext::GetContentSettingStatusInternal(
    content::RenderFrameHost* render_frame_host,
    const GURL& requesting_origin,
    const GURL& embedding_origin) const {
  // Check if origin is https://search.qorai.com.
  if (!requesting_origin.SchemeIs(url::kHttpsScheme) ||
      requesting_origin.host_piece() !=
          qorai_domains::GetServicesDomain("search")) {
    return ContentSetting::CONTENT_SETTING_BLOCK;
  }

  return ContentSettingPermissionContextBase::GetContentSettingStatusInternal(
      render_frame_host, requesting_origin, embedding_origin);
}

bool QorAIOpenAIChatPermissionContext::IsRestrictedToSecureOrigins() const {
  return true;
}

}  // namespace permissions
