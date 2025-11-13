// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_news/common/pref_names.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace qorai_news {

class QoraiNewsPolicyTest : public testing::Test {
 public:
  QoraiNewsPolicyTest() {
    prefs::RegisterProfilePrefs(pref_service_.registry());
  }

 protected:
  void BlockQoraiNewsByPolicy(bool value) {
    pref_service_.SetManagedPref(prefs::kQoraiNewsDisabledByPolicy,
                                 base::Value(value));
  }

  sync_preferences::TestingPrefServiceSyncable pref_service_;
};

TEST_F(QoraiNewsPolicyTest, PolicyDisablesQoraiNews) {
  // Initially, policy should not be disabled
  EXPECT_FALSE(pref_service_.GetBoolean(prefs::kQoraiNewsDisabledByPolicy));
  EXPECT_FALSE(
      pref_service_.IsManagedPreference(prefs::kQoraiNewsDisabledByPolicy));

  // Set policy to disable Qorai News
  BlockQoraiNewsByPolicy(true);

  // Test that the policy preference is set correctly
  EXPECT_TRUE(pref_service_.FindPreference(prefs::kQoraiNewsDisabledByPolicy));
  EXPECT_TRUE(
      pref_service_.IsManagedPreference(prefs::kQoraiNewsDisabledByPolicy));
  EXPECT_TRUE(pref_service_.GetBoolean(prefs::kQoraiNewsDisabledByPolicy));

  // Test that IsEnabled returns false when policy disables it
  EXPECT_FALSE(IsEnabled(&pref_service_));
}

TEST_F(QoraiNewsPolicyTest, PolicyEnablesQoraiNews) {
  // Set policy to enable Qorai News (policy value false = not disabled)
  BlockQoraiNewsByPolicy(false);

  // Test that the policy preference is set correctly
  EXPECT_TRUE(pref_service_.FindPreference(prefs::kQoraiNewsDisabledByPolicy));
  EXPECT_TRUE(
      pref_service_.IsManagedPreference(prefs::kQoraiNewsDisabledByPolicy));
  EXPECT_FALSE(pref_service_.GetBoolean(prefs::kQoraiNewsDisabledByPolicy));

  // Set user preferences needed for IsEnabled to return true
  pref_service_.SetBoolean(prefs::kNewTabPageShowToday, true);
  pref_service_.SetBoolean(prefs::kQoraiNewsOptedIn, true);

  // Test that IsEnabled returns true when policy allows it and user opts in
  EXPECT_TRUE(IsEnabled(&pref_service_));
}

TEST_F(QoraiNewsPolicyTest, NoPolicyDefaultBehavior) {
  // Test that the policy preference exists but is not managed by default
  EXPECT_TRUE(pref_service_.FindPreference(prefs::kQoraiNewsDisabledByPolicy));
  EXPECT_FALSE(
      pref_service_.IsManagedPreference(prefs::kQoraiNewsDisabledByPolicy));
  EXPECT_FALSE(pref_service_.GetBoolean(prefs::kQoraiNewsDisabledByPolicy));

  // Set user preferences needed for IsEnabled to return true
  pref_service_.SetBoolean(prefs::kNewTabPageShowToday, true);
  pref_service_.SetBoolean(prefs::kQoraiNewsOptedIn, true);

  // Test that IsEnabled returns true when no policy is set and user opts in
  EXPECT_TRUE(IsEnabled(&pref_service_));
}

TEST_F(QoraiNewsPolicyTest, PolicyOverridesUserPreferences) {
  // Set user preferences to enable Qorai News
  pref_service_.SetBoolean(prefs::kNewTabPageShowToday, true);
  pref_service_.SetBoolean(prefs::kQoraiNewsOptedIn, true);

  // Without policy, should be enabled
  EXPECT_TRUE(IsEnabled(&pref_service_));

  // Set policy to disable Qorai News
  BlockQoraiNewsByPolicy(true);

  // Test that policy overrides user preferences
  EXPECT_TRUE(pref_service_.GetBoolean(prefs::kQoraiNewsDisabledByPolicy));
  EXPECT_FALSE(IsEnabled(&pref_service_));
}

}  // namespace qorai_news
