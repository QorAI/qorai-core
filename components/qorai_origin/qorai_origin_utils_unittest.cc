/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_origin/qorai_origin_utils.h"

#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_origin/qorai_origin_policy_info.h"
#include "qorai/components/qorai_origin/features.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace qorai_origin {

// Test constants
constexpr char kTestGlobalPolicy[] = "TestGlobalPolicy";
constexpr char kTestProfilePolicy[] = "TestProfilePolicy";

class QoraiOriginUtilsTest : public testing::Test {
 public:
  QoraiOriginUtilsTest() = default;
  ~QoraiOriginUtilsTest() override = default;

 protected:
  base::test::ScopedFeatureList scoped_feature_list_;
};

TEST_F(QoraiOriginUtilsTest, IsQoraiOriginEnabled_FeatureDisabled) {
  scoped_feature_list_.InitAndDisableFeature(features::kQoraiOrigin);

  EXPECT_FALSE(IsQoraiOriginEnabled());
}

TEST_F(QoraiOriginUtilsTest, IsQoraiOriginEnabled_FeatureEnabled) {
  scoped_feature_list_.InitAndEnableFeature(features::kQoraiOrigin);

  EXPECT_TRUE(IsQoraiOriginEnabled());
}

TEST_F(QoraiOriginUtilsTest, GetQoraiOriginPrefKey_BrowserPolicy) {
  std::string result = GetQoraiOriginPrefKey(kTestGlobalPolicy, std::nullopt);

  EXPECT_EQ(kTestGlobalPolicy, result);
}

TEST_F(QoraiOriginUtilsTest, GetQoraiOriginPrefKey_ProfilePolicy) {
  std::string result = GetQoraiOriginPrefKey(kTestProfilePolicy, "profile123");

  EXPECT_EQ("profile123.TestProfilePolicy", result);
}

TEST_F(QoraiOriginUtilsTest, GetQoraiOriginPrefKey_SpecialCharacters) {
  std::string result =
      GetQoraiOriginPrefKey("Test-Policy_Key", "Profile-1_test");

  EXPECT_EQ("Profile-1_test.Test-Policy_Key", result);
}

}  // namespace qorai_origin
