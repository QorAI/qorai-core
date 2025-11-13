/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "components/policy/core/common/configuration_policy_provider.h"

namespace qorai_policy {
std::unique_ptr<policy::ConfigurationPolicyProvider>
CreateQoraiProfilePolicyProvider();
}  // namespace qorai_policy

// Create and Init the Qorai Profile Policy Provider which is used
// for Qorai Origin and other Qorai specific policies.
// We do not need to define a patch for Shutdown since anything in
// wrapped_policy_providers_ will automatically call Shutdown.
#define QORAI_PROFILE_POLICY_CONNECTOR_INIT                         \
  auto provider = qorai_policy::CreateQoraiProfilePolicyProvider(); \
  qorai_profile_policy_provider_ = provider.get();                  \
  policy_providers_.push_back(provider.get());                      \
  provider->Init(schema_registry);                                  \
  wrapped_policy_providers_.push_back(std::move(provider));

#include <chrome/browser/policy/profile_policy_connector.cc>  // IWYU pragma: export

namespace policy {
raw_ptr<policy::ConfigurationPolicyProvider>
ProfilePolicyConnector::GetQoraiProfilePolicyProvider() {
  return qorai_profile_policy_provider_;
}
}  // namespace policy

#undef QORAI_PROFILE_POLICY_CONNECTOR_INIT
