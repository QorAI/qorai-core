// Copyright (c) 2023 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_PERMISSIONS_CONTEXTS_QORAI_LOCALHOST_PERMISSION_CONTEXT_H_
#define QORAI_COMPONENTS_PERMISSIONS_CONTEXTS_QORAI_LOCALHOST_PERMISSION_CONTEXT_H_

#include "components/permissions/content_setting_permission_context_base.h"
#include "content/public/browser/browser_context.h"

namespace permissions {

class QorAILocalhostPermissionContext
    : public ContentSettingPermissionContextBase {
 public:
  // using ContentSettingPermissionContextBase::RequestPermission;
  explicit QorAILocalhostPermissionContext(
      content::BrowserContext* browser_context);
  ~QorAILocalhostPermissionContext() override;

  QorAILocalhostPermissionContext(const QorAILocalhostPermissionContext&) =
      delete;
  QorAILocalhostPermissionContext& operator=(
      const QorAILocalhostPermissionContext&) = delete;

 private:
  bool IsRestrictedToSecureOrigins() const override;
};

}  // namespace permissions

#endif  // QORAI_COMPONENTS_PERMISSIONS_CONTEXTS_QORAI_LOCALHOST_PERMISSION_CONTEXT_H_
