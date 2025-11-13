// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/constants/pref_names.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "testing/gtest/include/gtest/gtest.h"

class QoraiTalkPolicyTest : public testing::Test {
 public:
  QoraiTalkPolicyTest() {
    // Register the Qorai Talk policy preference
    pref_service_.registry()->RegisterBooleanPref(kQoraiTalkDisabledByPolicy,
                                                  false);
  }

 protected:
  void SetQoraiTalkDisabledByPolicy(bool value) {
    pref_service_.SetManagedPref(kQoraiTalkDisabledByPolicy,
                                 base::Value(value));
  }

  sync_preferences::TestingPrefServiceSyncable pref_service_;
};

TEST_F(QoraiTalkPolicyTest, PolicyDisablesQoraiTalk) {
  // Initially, policy should not be disabled
  EXPECT_FALSE(pref_service_.GetBoolean(kQoraiTalkDisabledByPolicy));
  EXPECT_FALSE(pref_service_.IsManagedPreference(kQoraiTalkDisabledByPolicy));

  // Set policy to disable Qorai Talk
  SetQoraiTalkDisabledByPolicy(true);

  // Test that the policy preference is set correctly
  EXPECT_TRUE(pref_service_.FindPreference(kQoraiTalkDisabledByPolicy));
  EXPECT_TRUE(pref_service_.IsManagedPreference(kQoraiTalkDisabledByPolicy));
  EXPECT_TRUE(pref_service_.GetBoolean(kQoraiTalkDisabledByPolicy));
}

TEST_F(QoraiTalkPolicyTest, PolicyEnablesQoraiTalk) {
  // Set policy to explicitly enable Qorai Talk
  SetQoraiTalkDisabledByPolicy(false);

  // Test that the policy preference is set correctly
  EXPECT_TRUE(pref_service_.FindPreference(kQoraiTalkDisabledByPolicy));
  EXPECT_TRUE(pref_service_.IsManagedPreference(kQoraiTalkDisabledByPolicy));
  EXPECT_FALSE(pref_service_.GetBoolean(kQoraiTalkDisabledByPolicy));
}

TEST_F(QoraiTalkPolicyTest, PolicyChangesAreReflected) {
  // Start with policy disabled
  SetQoraiTalkDisabledByPolicy(false);
  EXPECT_FALSE(pref_service_.GetBoolean(kQoraiTalkDisabledByPolicy));
  EXPECT_TRUE(pref_service_.IsManagedPreference(kQoraiTalkDisabledByPolicy));

  // Change policy to enabled
  SetQoraiTalkDisabledByPolicy(true);
  EXPECT_TRUE(pref_service_.GetBoolean(kQoraiTalkDisabledByPolicy));
  EXPECT_TRUE(pref_service_.IsManagedPreference(kQoraiTalkDisabledByPolicy));
}

TEST_F(QoraiTalkPolicyTest, DefaultValueWhenNotManaged) {
  // When not managed by policy, should be false by default
  EXPECT_FALSE(pref_service_.GetBoolean(kQoraiTalkDisabledByPolicy));
  EXPECT_FALSE(pref_service_.IsManagedPreference(kQoraiTalkDisabledByPolicy));
}
