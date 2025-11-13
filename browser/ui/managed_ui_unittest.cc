/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/values.h"
#include "components/policy/core/common/policy_map.h"
#include "components/policy/core/common/policy_types.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace qorai_policy {
// Forward declare the function from chromium_src
bool ShouldHideManagedUI(const policy::PolicyMap& policies);
}  // namespace qorai_policy

TEST(ManagedUiTest, ShouldHideManagedUI_EmptyPolicies) {
  policy::PolicyMap empty_policies;
  EXPECT_FALSE(qorai_policy::ShouldHideManagedUI(empty_policies));
}

TEST(ManagedUiTest, ShouldHideManagedUI_OnlyQoraiPolicies) {
  policy::PolicyMap policies;
  policies.Set("QoraiPolicy1", policy::POLICY_LEVEL_MANDATORY,
               policy::POLICY_SCOPE_USER, policy::POLICY_SOURCE_QORAI,
               base::Value("value1"), nullptr);
  policies.Set("QoraiPolicy2", policy::POLICY_LEVEL_RECOMMENDED,
               policy::POLICY_SCOPE_MACHINE, policy::POLICY_SOURCE_QORAI,
               base::Value("value2"), nullptr);

  EXPECT_TRUE(qorai_policy::ShouldHideManagedUI(policies));
}

TEST(ManagedUiTest, ShouldHideManagedUI_MixedPolicies) {
  policy::PolicyMap policies;
  policies.Set("QoraiPolicy", policy::POLICY_LEVEL_MANDATORY,
               policy::POLICY_SCOPE_USER, policy::POLICY_SOURCE_QORAI,
               base::Value("qorai_value"), nullptr);
  policies.Set("EnterprisePolicy", policy::POLICY_LEVEL_MANDATORY,
               policy::POLICY_SCOPE_MACHINE,
               policy::POLICY_SOURCE_ENTERPRISE_DEFAULT,
               base::Value("enterprise_value"), nullptr);

  EXPECT_FALSE(qorai_policy::ShouldHideManagedUI(policies));
}

TEST(ManagedUiTest, ShouldHideManagedUI_OnlyNonQoraiPolicies) {
  policy::PolicyMap policies;
  policies.Set("CloudPolicy", policy::POLICY_LEVEL_MANDATORY,
               policy::POLICY_SCOPE_USER, policy::POLICY_SOURCE_CLOUD,
               base::Value("cloud_value"), nullptr);
  policies.Set("PlatformPolicy", policy::POLICY_LEVEL_RECOMMENDED,
               policy::POLICY_SCOPE_MACHINE, policy::POLICY_SOURCE_PLATFORM,
               base::Value("platform_value"), nullptr);

  EXPECT_FALSE(qorai_policy::ShouldHideManagedUI(policies));
}
