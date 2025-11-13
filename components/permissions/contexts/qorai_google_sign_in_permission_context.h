// Copyright (c) 2022 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_PERMISSIONS_CONTEXTS_QORAI_GOOGLE_SIGN_IN_PERMISSION_CONTEXT_H_
#define QORAI_COMPONENTS_PERMISSIONS_CONTEXTS_QORAI_GOOGLE_SIGN_IN_PERMISSION_CONTEXT_H_

#include "components/permissions/content_setting_permission_context_base.h"
#include "content/public/browser/browser_context.h"

namespace permissions {

class QorAIGoogleSignInPermissionContext
    : public ContentSettingPermissionContextBase {
 public:
  // using ContentSettingPermissionContextBase::RequestPermission;
  explicit QorAIGoogleSignInPermissionContext(
      content::BrowserContext* browser_context);
  ~QorAIGoogleSignInPermissionContext() override;

  QorAIGoogleSignInPermissionContext(
      const QorAIGoogleSignInPermissionContext&) = delete;
  QorAIGoogleSignInPermissionContext& operator=(
      const QorAIGoogleSignInPermissionContext&) = delete;

 private:
  bool IsRestrictedToSecureOrigins() const override;
};

}  // namespace permissions

#endif  // QORAI_COMPONENTS_PERMISSIONS_CONTEXTS_QORAI_GOOGLE_SIGN_IN_PERMISSION_CONTEXT_H_
