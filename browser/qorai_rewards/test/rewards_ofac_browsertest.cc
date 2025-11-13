/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/app/qorai_command_ids.h"
#include "qorai/browser/qorai_ads/ads_service_factory.h"
#include "qorai/browser/qorai_rewards/rewards_service_factory.h"
#include "qorai/browser/qorai_rewards/rewards_util.h"
#include "qorai/components/qorai_rewards/content/rewards_service.h"
#include "qorai/components/qorai_rewards/core/rewards_util.h"
#include "qorai/components/l10n/common/test/scoped_default_locale.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_command_controller.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/prefs/pref_service.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/web_contents.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "url/gurl.h"

namespace qorai_rewards {

class QoraiRewardsOFACTest : public InProcessBrowserTest {
 public:
  QoraiRewardsOFACTest() = default;
  ~QoraiRewardsOFACTest() override = default;

  content::WebContents* web_contents() const {
    return browser()->tab_strip_model()->GetActiveWebContents();
  }

  content::BrowserContext* browser_context() {
    return web_contents()->GetBrowserContext();
  }

  Profile* profile() { return browser()->profile(); }

  PrefService* prefs() { return user_prefs::UserPrefs::Get(browser_context()); }
};

// Verify that qorai_rewards::IsSupported works correctly based on the locale.
IN_PROC_BROWSER_TEST_F(QoraiRewardsOFACTest, IsQoraiRewardsDisabled) {
  {
    const qorai_l10n::test::ScopedDefaultLocale locale("en_CA");  // "Canada"
    EXPECT_FALSE(IsUnsupportedRegion());
    EXPECT_TRUE(qorai_rewards::IsSupported(prefs()));
    EXPECT_TRUE(qorai_rewards::IsSupported(
        prefs(), qorai_rewards::IsSupportedOptions::kSkipRegionCheck));
    EXPECT_TRUE(qorai_rewards::IsSupportedForProfile(profile()));
    EXPECT_TRUE(qorai_rewards::IsSupportedForProfile(
        profile(), qorai_rewards::IsSupportedOptions::kSkipRegionCheck));
  }
  {
    const qorai_l10n::test::ScopedDefaultLocale locale("es_CU");  // "Cuba"
    EXPECT_TRUE(IsUnsupportedRegion());
    EXPECT_FALSE(qorai_rewards::IsSupported(prefs()));
    EXPECT_TRUE(qorai_rewards::IsSupported(
        prefs(), qorai_rewards::IsSupportedOptions::kSkipRegionCheck));
    EXPECT_FALSE(qorai_rewards::IsSupportedForProfile(profile()));
    EXPECT_TRUE(qorai_rewards::IsSupportedForProfile(
        profile(), qorai_rewards::IsSupportedOptions::kSkipRegionCheck));
  }
}

// Verify that Rewards and Ads services don't get created when in an OFAC
// sanctioned region.
IN_PROC_BROWSER_TEST_F(QoraiRewardsOFACTest, GetRewardsAndAdsServices) {
  {
    const qorai_l10n::test::ScopedDefaultLocale locale("en_CA");  // "Canada"
    EXPECT_NE(qorai_rewards::RewardsServiceFactory::GetForProfile(profile()),
              nullptr);
    EXPECT_NE(qorai_ads::AdsServiceFactory::GetForProfile(profile()), nullptr);
  }

  {
    const qorai_l10n::test::ScopedDefaultLocale locale("es_CU");  // "Cuba"
    EXPECT_EQ(qorai_rewards::RewardsServiceFactory::GetForProfile(profile()),
              nullptr);
    EXPECT_EQ(qorai_ads::AdsServiceFactory::GetForProfile(profile()), nullptr);
  }
}

// Verify that Rewards menu item is enabled in the app menu even when in an OFAC
// sanctioned region.
IN_PROC_BROWSER_TEST_F(QoraiRewardsOFACTest, AppMenuItemEnabled) {
  auto* command_controller = browser()->command_controller();
  {
    const qorai_l10n::test::ScopedDefaultLocale locale("en_CA");  // "Canada"
    EXPECT_TRUE(command_controller->IsCommandEnabled(IDC_SHOW_QORAI_REWARDS));
  }
  {
    const qorai_l10n::test::ScopedDefaultLocale locale("es_CU");  // "Cuba"
    EXPECT_TRUE(command_controller->IsCommandEnabled(IDC_SHOW_QORAI_REWARDS));
  }
}

// Verify that qorai://rewards page is reachable even when  in an OFAC
// sanctioned region.
IN_PROC_BROWSER_TEST_F(QoraiRewardsOFACTest, RewardsPagesAccess) {
  const GURL url("chrome://rewards");
  {
    const qorai_l10n::test::ScopedDefaultLocale locale("es_CU");  // "Cuba"
    auto* rfh = ui_test_utils::NavigateToURL(browser(), url);
    EXPECT_TRUE(rfh);
    EXPECT_FALSE(rfh->IsErrorDocument());
  }
}

}  // namespace qorai_rewards
