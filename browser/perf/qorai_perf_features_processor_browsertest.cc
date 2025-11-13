/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/scoped_observation.h"
#include "qorai/browser/qorai_rewards/rewards_service_factory.h"
#include "qorai/browser/perf/qorai_perf_switches.h"
#include "qorai/components/ai_chat/core/browser/utils.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/content/rewards_service.h"
#include "qorai/components/qorai_rewards/content/rewards_service_observer.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "components/prefs/pref_service.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/browser/speedreader/speedreader_service_factory.h"
#include "qorai/components/speedreader/speedreader_service.h"
#endif

namespace {
class TestRewardsServiceObserver
    : public qorai_rewards::RewardsServiceObserver {
 public:
  void WaitForServiceInitialized(qorai_rewards::RewardsService* service) {
    if (service->IsInitialized()) {
      return;
    }

    observer_.Observe(service);
    run_loop_.Run();
  }

 private:
  void OnRewardsInitialized(qorai_rewards::RewardsService*) override {
    run_loop_.Quit();
  }

  base::RunLoop run_loop_;
  base::ScopedObservation<qorai_rewards::RewardsService,
                          qorai_rewards::RewardsServiceObserver>
      observer_{this};
};
}  // namespace

class QoraiSpeedFeatureProcessorBrowserTest : public InProcessBrowserTest {
 protected:
  void SetUpCommandLine(base::CommandLine* command_line) override {
    InProcessBrowserTest::SetUpCommandLine(command_line);
    command_line->AppendSwitch(
        perf::switches::kEnableQoraiFeaturesForPerfTesting);
  }

#if BUILDFLAG(ENABLE_SPEEDREADER)
  bool SpeedreaderIsEnabled() {
    auto* speedreader_service =
        speedreader::SpeedreaderServiceFactory::GetForBrowserContext(
            browser()->profile());
    return speedreader_service->IsAllowedForAllReadableSites();
  }
#endif  // BUILDFLAG(ENABLE_SPEEDREADER)

  bool QoraiNewsAreEnabled() {
    return qorai_news::IsEnabled(browser()->profile()->GetPrefs());
  }

  bool HasOptedInToNotificationAds() {
    return browser()->profile()->GetPrefs()->GetBoolean(
        qorai_ads::prefs::kOptedInToNotificationAds);
  }

  void WaitForRewardsServiceInitialized() {
    auto* rewards_service = qorai_rewards::RewardsServiceFactory::GetForProfile(
        browser()->profile());
    TestRewardsServiceObserver observer;
    observer.WaitForServiceInitialized(rewards_service);
  }
};

IN_PROC_BROWSER_TEST_F(QoraiSpeedFeatureProcessorBrowserTest, PRE_Default) {
  WaitForRewardsServiceInitialized();
}

IN_PROC_BROWSER_TEST_F(QoraiSpeedFeatureProcessorBrowserTest, Default) {
#if BUILDFLAG(ENABLE_SPEEDREADER)
  EXPECT_TRUE(SpeedreaderIsEnabled());
#endif
  EXPECT_TRUE(HasOptedInToNotificationAds());
  EXPECT_TRUE(QoraiNewsAreEnabled());
  WaitForRewardsServiceInitialized();

  auto* prefs = browser()->profile()->GetPrefs();
  EXPECT_TRUE(ai_chat::IsAIChatEnabled(prefs));
  EXPECT_TRUE(ai_chat::HasUserOptedIn(prefs));
}
