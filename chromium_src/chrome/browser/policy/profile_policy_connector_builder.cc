/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/files/file_path.h"
#include "chrome/browser/policy/profile_policy_connector.h"

#define CreateProfilePolicyConnectorForBrowserContext \
  CreateProfilePolicyConnectorForBrowserContext_ChromiumImpl

#include <chrome/browser/policy/profile_policy_connector_builder.cc>  // IWYU pragma: export

#undef CreateProfilePolicyConnectorForBrowserContext

namespace qorai_policy {
class QoraiProfilePolicyProvider;
void SetQoraiProfilePolicyProviderProfileID(
    policy::ConfigurationPolicyProvider* provider,
    const base::FilePath& profile_path);
}  // namespace qorai_policy

namespace policy {

std::unique_ptr<ProfilePolicyConnector>
CreateProfilePolicyConnectorForBrowserContext(
    SchemaRegistry* schema_registry,
    CloudPolicyManager* cloud_policy_manager,
    ConfigurationPolicyProvider* policy_provider,
    policy::ChromeBrowserPolicyConnector* browser_policy_connector,
    bool force_immediate_load,
    content::BrowserContext* context) {
  auto connector = CreateProfilePolicyConnectorForBrowserContext_ChromiumImpl(
      schema_registry, cloud_policy_manager, policy_provider,
      browser_policy_connector, force_immediate_load, context);
  // Some upstream browser tests don't do the normal flow so have no provider
  if (connector->GetQoraiProfilePolicyProvider()) {
    qorai_policy::SetQoraiProfilePolicyProviderProfileID(
        connector->GetQoraiProfilePolicyProvider().get(), context->GetPath());
  }

  return connector;
}

}  // namespace policy
