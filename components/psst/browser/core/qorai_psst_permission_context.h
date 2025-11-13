/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_PSST_BROWSER_CORE_QORAI_PSST_PERMISSION_CONTEXT_H_
#define QORAI_COMPONENTS_PSST_BROWSER_CORE_QORAI_PSST_PERMISSION_CONTEXT_H_

#include "qorai/components/psst/common/psst_permission_schema.h"
#include "qorai/components/psst/common/psst_ui_common.mojom-forward.h"
#include "components/permissions/object_permission_context_base.h"

namespace psst {

// This class manages the permissions for the PSST feature.
// The grants is associated with an origin and user_id.
class QoraiPsstPermissionContext
    : public permissions::ObjectPermissionContextBase {
 public:
  explicit QoraiPsstPermissionContext(
      HostContentSettingsMap* host_content_settings_map);
  QoraiPsstPermissionContext(const QoraiPsstPermissionContext&) = delete;
  QoraiPsstPermissionContext& operator=(const QoraiPsstPermissionContext&) =
      delete;
  ~QoraiPsstPermissionContext() override;

  // Grants permission for the (origin, user_id) pair with the given details.
  void GrantPermission(const url::Origin& origin,
                       ConsentStatus consent_status,
                       int script_version,
                       std::string_view user_id,
                       base::Value::List urls_to_skip);

  // Returns whether the given origin and user_id pair has any PSST permission.
  bool HasPermission(const url::Origin& origin, std::string_view user_id);

  // Revokes previously-granted permission for the (origin, user_id) pair.
  void RevokePermission(const url::Origin& origin, std::string_view user_id);

  // Returns the PSST permission info for the (origin, user_id) pair if exists
  std::optional<PsstPermissionInfo> GetPsstPermissionInfo(
      const url::Origin& origin,
      std::string_view user_id);

 private:
  friend class QoraiPsstPermissionContextUnitTest;
  FRIEND_TEST_ALL_PREFIXES(QoraiPsstPermissionContextUnitTest,
                           DontAllowToCreatePermissionForWrongSchema);
  FRIEND_TEST_ALL_PREFIXES(QoraiPsstPermissionContextUnitTest,
                           CreateUpdateRevokePermissionInfo);

  void GrantPermission(const url::Origin& origin,
                       PsstPermissionInfo permission_info);
  // permissions::ObjectPermissionContextBase implementation:
  std::string GetKeyForObject(const base::Value::Dict& object) override;
  bool IsValidObject(const base::Value::Dict& object) override;
  std::u16string GetObjectDisplayName(const base::Value::Dict& object) override;
};

}  // namespace psst

#endif  // QORAI_COMPONENTS_PSST_BROWSER_CORE_QORAI_PSST_PERMISSION_CONTEXT_H_
