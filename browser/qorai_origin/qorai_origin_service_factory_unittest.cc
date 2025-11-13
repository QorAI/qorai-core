/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_origin/qorai_origin_service_factory.h"

#include "base/containers/contains.h"
#include "base/containers/map_util.h"
#include "qorai/browser/policy/qorai_simple_policy_map.h"
#include "qorai/components/qorai_origin/qorai_origin_policy_info.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/p3a/pref_names.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile_manager.h"
#include "components/policy/policy_constants.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gtest/include/gtest/gtest.h"

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/components/tor/pref_names.h"
#endif

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
#include "qorai/components/qorai_rewards/core/pref_names.h"  // nogncheck
#endif

namespace qorai_origin {

TEST(QorAIOriginServiceFactoryTest,
     GetBrowserPolicyDefinitions_ContainsExpectedBrowserPolicies) {
  auto browser_policy_definitions =
      QorAIOriginServiceFactory::GetBrowserPolicyDefinitions();

  // Test that P3A policy is correctly built (browser-level)
  const auto* p3a_info = base::FindOrNull(browser_policy_definitions,
                                          policy::key::kQorAIP3AEnabled);
  ASSERT_NE(p3a_info, nullptr);
  EXPECT_EQ(p3a_info->pref_name, p3a::kP3AEnabled);
  EXPECT_EQ(p3a_info->default_value, false);
  EXPECT_EQ(p3a_info->user_settable, true);
  EXPECT_EQ(p3a_info->qorai_origin_pref_key, p3a::kP3AEnabled);

  // Test that Stats reporting policy is correctly built (browser-level)
  const auto* stats_info = base::FindOrNull(
      browser_policy_definitions, policy::key::kQorAIStatsPingEnabled);
  ASSERT_NE(stats_info, nullptr);
  EXPECT_EQ(stats_info->pref_name, kStatsReportingEnabled);
  EXPECT_EQ(stats_info->default_value, false);
  EXPECT_EQ(stats_info->user_settable, true);
  EXPECT_EQ(stats_info->qorai_origin_pref_key, kStatsReportingEnabled);

#if BUILDFLAG(ENABLE_TOR)
  // Test that Tor disabled policy is correctly built (browser-level)
  const auto* tor_info =
      base::FindOrNull(browser_policy_definitions, policy::key::kTorDisabled);
  ASSERT_NE(tor_info, nullptr);
  EXPECT_EQ(tor_info->pref_name, tor::prefs::kTorDisabled);
  EXPECT_EQ(tor_info->default_value,
            true);  // This is a "disabled" pref, so default is true
  EXPECT_EQ(tor_info->user_settable, false);
  EXPECT_EQ(tor_info->qorai_origin_pref_key, tor::prefs::kTorDisabled);
#endif

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
  // Test that profile-level policies are NOT in browser definitions
  EXPECT_FALSE(base::Contains(browser_policy_definitions,
                              policy::key::kQorAIRewardsDisabled))
      << "Profile-level policy should not be in browser definitions";
#endif
}

TEST(QorAIOriginServiceFactoryTest,
     GetProfilePolicyDefinitions_ContainsExpectedProfilePolicies) {
  auto profile_policy_definitions =
      QorAIOriginServiceFactory::GetProfilePolicyDefinitions();

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
  // Test that QorAI Rewards disabled policy is correctly built (profile-level)
  const auto* rewards_info = base::FindOrNull(
      profile_policy_definitions, policy::key::kQorAIRewardsDisabled);
  ASSERT_NE(rewards_info, nullptr);
  EXPECT_EQ(rewards_info->pref_name, qorai_rewards::prefs::kDisabledByPolicy);
  EXPECT_EQ(rewards_info->default_value,
            true);  // This is a "disabled" pref, so default is true
  EXPECT_EQ(rewards_info->user_settable, false);
  EXPECT_EQ(rewards_info->qorai_origin_pref_key,
            qorai_rewards::prefs::kDisabledByPolicy);
#endif

  // Test that browser-level policies are NOT in profile definitions
  EXPECT_FALSE(
      base::Contains(profile_policy_definitions, policy::key::kQorAIP3AEnabled))
      << "Browser-level policy should not be in profile definitions";
  EXPECT_FALSE(base::Contains(profile_policy_definitions,
                              policy::key::kQorAIStatsPingEnabled))
      << "Browser-level policy should not be in profile definitions";
}

TEST(QorAIOriginServiceFactoryTest,
     GetBrowserPolicyDefinitions_ExcludesPoliciesNotInMetadata) {
  auto policy_definitions =
      QorAIOriginServiceFactory::GetBrowserPolicyDefinitions();

  // Test that policies in kQorAISimplePolicyMap but NOT in kQorAIOriginMetadata
  // are excluded kQorAIShieldsDisabledForUrls is in kQorAISimplePolicyMap but
  // not in kQorAIOriginMetadata
#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
  EXPECT_FALSE(base::Contains(policy_definitions,
                              policy::key::kQorAIShieldsDisabledForUrls))
      << "kManagedQorAIShieldsDisabledForUrls should not be in policy "
         "definitions";

  // kQorAIShieldsEnabledForUrls is also in kQorAISimplePolicyMap but not in
  // kQorAIOriginMetadata
  EXPECT_FALSE(base::Contains(policy_definitions,
                              policy::key::kQorAIShieldsEnabledForUrls))
      << "kManagedQorAIShieldsEnabledForUrls should not be in policy "
         "definitions";
#endif
}

TEST(QorAIOriginServiceFactoryTest,
     GetPolicyDefinitions_OnlyContainsMetadataPolicies) {
  auto browser_policy_definitions =
      QorAIOriginServiceFactory::GetBrowserPolicyDefinitions();
  auto profile_policy_definitions =
      QorAIOriginServiceFactory::GetProfilePolicyDefinitions();

  // Test browser policy definitions
  for (const auto& [policy_key, policy_info] : browser_policy_definitions) {
    EXPECT_FALSE(policy_key.empty())
        << "Browser policy key should not be empty";
    EXPECT_FALSE(policy_info.pref_name.empty())
        << "Browser policy info pref name should not be empty";
    EXPECT_FALSE(policy_info.qorai_origin_pref_key.empty())
        << "Browser QorAIOrigin pref key should not be empty";
    EXPECT_EQ(policy_info.qorai_origin_pref_key, policy_info.pref_name);
  }

  // Test profile policy definitions
  for (const auto& [policy_key, policy_info] : profile_policy_definitions) {
    EXPECT_FALSE(policy_key.empty())
        << "Profile policy key should not be empty";
    EXPECT_FALSE(policy_info.pref_name.empty())
        << "Profile policy info pref name should not be empty";
    EXPECT_FALSE(policy_info.qorai_origin_pref_key.empty())
        << "Profile QorAIOrigin pref key should not be empty";
    EXPECT_EQ(policy_info.qorai_origin_pref_key, policy_info.pref_name);
  }

  // Verify that we have browser-level policies (P3A, Stats are always
  // available)
  EXPECT_GE(browser_policy_definitions.size(), 2u)
      << "Should have at least P3A and Stats browser policies";

  // Verify that we have profile-level policies
  EXPECT_GT(profile_policy_definitions.size(), 0u)
      << "Should have at least some profile policies";
}

// Test fixture for profile-related tests
class QorAIOriginServiceFactoryProfileTest : public ::testing::Test {
 protected:
  void SetUp() override { ASSERT_TRUE(profile_manager_.SetUp()); }

  content::BrowserTaskEnvironment task_environment_;
  TestingProfileManager profile_manager_{TestingBrowserProcess::GetGlobal()};
};

TEST_F(QorAIOriginServiceFactoryProfileTest, NoServiceForGuestProfile) {
  // Create a guest profile
  auto* guest_profile = profile_manager_.CreateGuestProfile();
  ASSERT_NE(guest_profile, nullptr);

  // Verify that QorAIOriginService is not created for guest profiles
  auto* service = QorAIOriginServiceFactory::GetForProfile(guest_profile);
  EXPECT_EQ(service, nullptr);
}

}  // namespace qorai_origin
