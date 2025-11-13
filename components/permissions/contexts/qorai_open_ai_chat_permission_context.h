// Copyright (c) 2024 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_PERMISSIONS_CONTEXTS_QORAI_OPEN_AI_CHAT_PERMISSION_CONTEXT_H_
#define QORAI_COMPONENTS_PERMISSIONS_CONTEXTS_QORAI_OPEN_AI_CHAT_PERMISSION_CONTEXT_H_

#include "components/permissions/content_setting_permission_context_base.h"
#include "content/public/browser/browser_context.h"

namespace permissions {

class QorAIOpenAIChatPermissionContext
    : public ContentSettingPermissionContextBase {
 public:
  explicit QorAIOpenAIChatPermissionContext(
      content::BrowserContext* browser_context);
  ~QorAIOpenAIChatPermissionContext() override;

  QorAIOpenAIChatPermissionContext(const QorAIOpenAIChatPermissionContext&) =
      delete;
  QorAIOpenAIChatPermissionContext& operator=(
      const QorAIOpenAIChatPermissionContext&) = delete;

 private:
  // ContentSettingPermissionContextBase:
  ContentSetting GetContentSettingStatusInternal(
      content::RenderFrameHost* render_frame_host,
      const GURL& requesting_origin,
      const GURL& embedding_origin) const override;
  bool IsRestrictedToSecureOrigins() const override;
};

}  // namespace permissions

#endif  // QORAI_COMPONENTS_PERMISSIONS_CONTEXTS_QORAI_OPEN_AI_CHAT_PERMISSION_CONTEXT_H_
