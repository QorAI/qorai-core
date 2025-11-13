/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/app/qorai_command_ids.h"
#include "qorai/browser/qorai_ads/ads_service_factory.h"
#include "qorai/browser/qorai_rewards/rewards_service_factory.h"
#include "qorai/browser/qorai_rewards/rewards_util.h"
#include "qorai/browser/ui/views/qorai_actions/qorai_actions_container.h"
#include "qorai/browser/ui/views/qorai_actions/qorai_rewards_action_view.h"
#include "qorai/browser/ui/views/location_bar/qorai_location_bar_view.h"
#include "qorai/components/qorai_rewards/content/rewards_service.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/qorai_rewards/core/rewards_util.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_command_controller.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/policy/core/browser/browser_policy_connector.h"
#include "components/policy/core/common/mock_configuration_policy_provider.h"
#include "components/policy/core/common/policy_map.h"
#include "components/policy/policy_constants.h"
#include "components/prefs/pref_service.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/web_contents.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "content/public/test/navigation_handle_observer.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"
#include "url/gurl.h"

namespace policy {

class QoraiRewardsPolicyTest : public InProcessBrowserTest,
                               public ::testing::WithParamInterface<bool> {
 public:
  QoraiRewardsPolicyTest() = default;
  ~QoraiRewardsPolicyTest() override = default;

  void SetUpInProcessBrowserTestFixture() override {
    EXPECT_CALL(provider_, IsInitializationComplete(testing::_))
        .WillRepeatedly(testing::Return(true));
    BrowserPolicyConnector::SetPolicyProviderForTesting(&provider_);
    PolicyMap policies;
    policies.Set(key::kQoraiRewardsDisabled, POLICY_LEVEL_MANDATORY,
                 POLICY_SCOPE_USER, POLICY_SOURCE_PLATFORM,
                 base::Value(IsQoraiRewardsDisabledTest()), nullptr);
    provider_.UpdateChromePolicy(policies);
  }

  bool IsQoraiRewardsDisabledTest() { return GetParam(); }

  content::WebContents* web_contents() const {
    return browser()->tab_strip_model()->GetActiveWebContents();
  }

  content::BrowserContext* browser_context() {
    return web_contents()->GetBrowserContext();
  }

  Profile* profile() { return browser()->profile(); }

  PrefService* prefs() { return user_prefs::UserPrefs::Get(browser_context()); }

 private:
  MockConfigurationPolicyProvider provider_;
};

// Verify that qorai_rewards::IsDisabledByPolicy works correctly based on the
// preference set by the policy.
IN_PROC_BROWSER_TEST_P(QoraiRewardsPolicyTest, IsQoraiRewardsDisabled) {
  EXPECT_TRUE(prefs()->FindPreference(qorai_rewards::prefs::kDisabledByPolicy));
  if (IsQoraiRewardsDisabledTest()) {
    EXPECT_TRUE(prefs()->GetBoolean(qorai_rewards::prefs::kDisabledByPolicy));
    EXPECT_FALSE(qorai_rewards::IsSupported(prefs()));
    EXPECT_FALSE(qorai_rewards::IsSupportedForProfile(profile()));
  } else {
    EXPECT_FALSE(prefs()->GetBoolean(qorai_rewards::prefs::kDisabledByPolicy));
    EXPECT_TRUE(qorai_rewards::IsSupported(prefs()));
    EXPECT_TRUE(qorai_rewards::IsSupportedForProfile(profile()));
  }
}

// Verify that Rewards and Ads services don't get created when Qorai Rewards are
// disabled by policy.
IN_PROC_BROWSER_TEST_P(QoraiRewardsPolicyTest, GetRewardsAndAdsServices) {
  if (IsQoraiRewardsDisabledTest()) {
    EXPECT_EQ(qorai_rewards::RewardsServiceFactory::GetForProfile(profile()),
              nullptr);
    EXPECT_EQ(qorai_ads::AdsServiceFactory::GetForProfile(profile()), nullptr);
  } else {
    EXPECT_NE(qorai_rewards::RewardsServiceFactory::GetForProfile(profile()),
              nullptr);
    EXPECT_NE(qorai_ads::AdsServiceFactory::GetForProfile(profile()), nullptr);
  }
}

// Verify that Rewards menu item isn't enabled in the app menu when Qorai
// Rewards are disabled by policy.
IN_PROC_BROWSER_TEST_P(QoraiRewardsPolicyTest, AppMenuItemDisabled) {
  auto* command_controller = browser()->command_controller();
  if (IsQoraiRewardsDisabledTest()) {
    EXPECT_FALSE(command_controller->IsCommandEnabled(IDC_SHOW_QORAI_REWARDS));
  } else {
    EXPECT_TRUE(command_controller->IsCommandEnabled(IDC_SHOW_QORAI_REWARDS));
  }
}

// Verify that qorai://rewards and qorai://rewards-internals pages aren't
// reachable when Qorai Rewards are disabled by policy.
IN_PROC_BROWSER_TEST_P(QoraiRewardsPolicyTest, RewardsPagesAccess) {
  for (const auto& url :
       {GURL("chrome://rewards"), GURL("chrome://rewards-internals")}) {
    SCOPED_TRACE(testing::Message() << "url=" << url);
    auto* rfh = ui_test_utils::NavigateToURL(browser(), url);
    EXPECT_TRUE(rfh);
    EXPECT_EQ(IsQoraiRewardsDisabledTest(), rfh->IsErrorDocument());
  }
}

// Verify that Qorai Rewards icon is not shown in the location bar when Qorai
// Rewards are disabled by policy.
IN_PROC_BROWSER_TEST_P(QoraiRewardsPolicyTest, RewardsIconIsHidden) {
  const auto* browser_view = BrowserView::GetBrowserViewForBrowser(browser());
  ASSERT_NE(browser_view, nullptr);
  const auto* qorai_location_bar_view =
      static_cast<QoraiLocationBarView*>(browser_view->GetLocationBarView());
  ASSERT_NE(qorai_location_bar_view, nullptr);
  const auto* qorai_actions = qorai_location_bar_view->qorai_actions_.get();
  ASSERT_NE(qorai_actions, nullptr);
  EXPECT_TRUE(
      prefs()->GetBoolean(qorai_rewards::prefs::kShowLocationBarButton));
  if (IsQoraiRewardsDisabledTest()) {
    EXPECT_FALSE(qorai_actions->rewards_action_btn_->GetVisible());
  } else {
    EXPECT_TRUE(qorai_actions->rewards_action_btn_->GetVisible());
  }
}

INSTANTIATE_TEST_SUITE_P(
    QoraiRewardsPolicyTest,
    QoraiRewardsPolicyTest,
    ::testing::Bool(),
    [](const testing::TestParamInfo<QoraiRewardsPolicyTest::ParamType>& info) {
      return absl::StrFormat("QoraiRewards_%sByPolicy",
                             info.param ? "Disabled" : "NotDisabled");
    });

}  // namespace policy
