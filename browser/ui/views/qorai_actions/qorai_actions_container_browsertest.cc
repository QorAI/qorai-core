/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/qorai_actions/qorai_actions_container.h"

#include "base/functional/callback_helpers.h"
#include "base/memory/raw_ptr.h"
#include "qorai/browser/ui/qorai_rewards/rewards_panel_coordinator.h"
#include "qorai/browser/ui/views/qorai_actions/qorai_rewards_action_view.h"
#include "qorai/browser/ui/views/location_bar/qorai_location_bar_view.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/constants/pref_names.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/profiles/profile_window.h"
#include "chrome/browser/search_engines/template_url_service_factory.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/ui/browser_window/public/browser_window_features.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/search_test_utils.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/prefs/pref_service.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/test_utils.h"

class QoraiActionsContainerTest : public InProcessBrowserTest {
 public:
  QoraiActionsContainerTest() = default;
  QoraiActionsContainerTest(const QoraiActionsContainerTest&) = delete;
  QoraiActionsContainerTest& operator=(const QoraiActionsContainerTest&) =
      delete;
  ~QoraiActionsContainerTest() override = default;

  void SetUpOnMainThread() override { Init(browser()); }

  void Init(Browser* browser) {
    BrowserView* browser_view = BrowserView::GetBrowserViewForBrowser(browser);
    ASSERT_NE(browser_view, nullptr);
    QoraiLocationBarView* qorai_location_bar_view =
        static_cast<QoraiLocationBarView*>(browser_view->GetLocationBarView());
    ASSERT_NE(qorai_location_bar_view, nullptr);
    qorai_actions_ = qorai_location_bar_view->qorai_actions_;
    ASSERT_NE(qorai_actions_, nullptr);
    prefs_ = browser->profile()->GetPrefs();
  }

  void CheckQoraiRewardsActionShown(bool expected_shown) {
    const bool shown = qorai_actions_->rewards_action_btn_->GetVisible();
    ASSERT_EQ(shown, expected_shown);
  }

  void CloseRewardsPanel() {
    qorai_actions_->rewards_action_btn_->ClosePanelForTesting();
  }

 protected:
  raw_ptr<QoraiActionsContainer, DanglingUntriaged> qorai_actions_ = nullptr;
  raw_ptr<PrefService, DanglingUntriaged> prefs_ = nullptr;
};

IN_PROC_BROWSER_TEST_F(QoraiActionsContainerTest, HideQoraiRewardsAction) {
  // By default the action should be shown.
  EXPECT_TRUE(prefs_->GetBoolean(qorai_rewards::prefs::kShowLocationBarButton));
  CheckQoraiRewardsActionShown(true);

  // Set to hide.
  prefs_->SetBoolean(qorai_rewards::prefs::kShowLocationBarButton, false);
  CheckQoraiRewardsActionShown(false);

  // Set to show.
  prefs_->SetBoolean(qorai_rewards::prefs::kShowLocationBarButton, true);
  CheckQoraiRewardsActionShown(true);
}

IN_PROC_BROWSER_TEST_F(QoraiActionsContainerTest,
                       QoraiRewardsActionHiddenInGuestSession) {
  // By default the action should be shown.
  EXPECT_TRUE(prefs_->GetBoolean(qorai_rewards::prefs::kShowLocationBarButton));
  CheckQoraiRewardsActionShown(true);

  // Open a Guest window.
  EXPECT_EQ(1U, BrowserList::GetInstance()->size());
  ui_test_utils::BrowserCreatedObserver browser_creation_observer;
  profiles::SwitchToGuestProfile(base::DoNothing());
  base::RunLoop().RunUntilIdle();
  browser_creation_observer.Wait();
  EXPECT_EQ(2U, BrowserList::GetInstance()->size());

  // Retrieve the new Guest profile.
  Profile* guest = g_browser_process->profile_manager()->GetProfileByPath(
      ProfileManager::GetGuestProfilePath());
  // The BrowsingDataRemover needs a loaded TemplateUrlService or else it hangs
  // on to a CallbackList::Subscription forever.
  search_test_utils::WaitForTemplateURLServiceToLoad(
      TemplateURLServiceFactory::GetForProfile(guest));

  // Access the browser with the Guest profile and re-init test for it.
  Browser* browser = chrome::FindAnyBrowser(guest, true);
  EXPECT_TRUE(browser);
  Init(browser);
  CheckQoraiRewardsActionShown(false);
}

IN_PROC_BROWSER_TEST_F(QoraiActionsContainerTest, ShowRewardsIconForPanel) {
  prefs_->SetBoolean(qorai_rewards::prefs::kShowLocationBarButton, false);
  CheckQoraiRewardsActionShown(false);

  // Send a request to open the Rewards panel.
  auto* coordinator = browser()->GetFeatures().rewards_panel_coordinator();
  ASSERT_TRUE(coordinator);
  coordinator->OpenRewardsPanel();
  base::RunLoop().RunUntilIdle();

  CheckQoraiRewardsActionShown(false);
}
