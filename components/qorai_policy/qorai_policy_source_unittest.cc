// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include <optional>
#include <string>

#include "base/values.h"
#include "components/policy/core/common/policy_map.h"
#include "components/policy/core/common/policy_types.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace policy {

class QoraiPolicySourceTest : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test that POLICY_SOURCE_QORAI enum value exists and is unique
TEST_F(QoraiPolicySourceTest, QoraiEnumExists) {
  // Verify the enum value exists and is different from other sources
  EXPECT_NE(POLICY_SOURCE_QORAI, POLICY_SOURCE_ENTERPRISE_DEFAULT);
  EXPECT_NE(POLICY_SOURCE_QORAI, POLICY_SOURCE_CLOUD);
  EXPECT_NE(POLICY_SOURCE_QORAI, POLICY_SOURCE_ACTIVE_DIRECTORY);
  EXPECT_NE(POLICY_SOURCE_QORAI, POLICY_SOURCE_PLATFORM);

  // Verify it's included in the count
  EXPECT_LT(POLICY_SOURCE_QORAI, POLICY_SOURCE_COUNT);
}

// Test that POLICY_SOURCE_QORAI has lower priority than
// POLICY_SOURCE_ENTERPRISE_DEFAULT
TEST_F(QoraiPolicySourceTest, QoraiHasLowerPriority) {
  // Create entries with same level and scope but different sources
  PolicyMap::Entry qorai_entry(POLICY_LEVEL_MANDATORY, POLICY_SCOPE_USER,
                               POLICY_SOURCE_QORAI, base::Value("qorai_value"),
                               nullptr);

  PolicyMap::Entry enterprise_entry(POLICY_LEVEL_MANDATORY, POLICY_SCOPE_USER,
                                    POLICY_SOURCE_ENTERPRISE_DEFAULT,
                                    base::Value("enterprise_value"), nullptr);

  PolicyMap policy_map;

  // Enterprise entry should have higher priority than Qorai entry
  EXPECT_TRUE(policy_map.EntryHasHigherPriority(enterprise_entry, qorai_entry));
  EXPECT_FALSE(
      policy_map.EntryHasHigherPriority(qorai_entry, enterprise_entry));
}

}  // namespace policy
