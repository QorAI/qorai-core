// Copyright (c) 2025 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/qorai_shields/qorai_shields_tab_helper.h"

#include <memory>

#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/qorai_shields/core/common/pref_names.h"
#include "chrome/test/base/chrome_render_view_host_test_harness.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile.h"
#include "components/favicon/content/content_favicon_driver.h"
#include "components/favicon/core/test/mock_favicon_service.h"
#include "components/prefs/testing_pref_service.h"
#include "content/public/browser/navigation_entry.h"
#include "content/public/test/navigation_simulator.h"
#include "content/public/test/test_renderer_host.h"
#include "content/public/test/web_contents_tester.h"
#include "content/test/test_web_contents.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace qorai_shields {

namespace {

class MockQorAIShieldsTabHelperObserver
    : public QorAIShieldsTabHelper::Observer {
 public:
  MOCK_METHOD(void, OnResourcesChanged, (), (override));
  MOCK_METHOD(void, OnFaviconUpdated, (), (override));
  MOCK_METHOD(void, OnShieldsEnabledChanged, (), (override));
  MOCK_METHOD(void, OnShieldsAdBlockOnlyModeEnabledChanged, (), (override));
  MOCK_METHOD(void, OnRepeatedReloadsDetected, (), (override));
};

}  // namespace

class QorAIShieldsTabHelperUnitTest
    : public content::RenderViewHostTestHarness {
 public:
  QorAIShieldsTabHelperUnitTest()
      : content::RenderViewHostTestHarness(
            base::test::TaskEnvironment::TimeSource::MOCK_TIME) {}

  ~QorAIShieldsTabHelperUnitTest() override = default;

  void SetUp() override {
    content::RenderViewHostTestHarness::SetUp();

    favicon::ContentFaviconDriver::CreateForWebContents(web_contents(),
                                                        &favicon_service_);
    QorAIShieldsTabHelper::CreateForWebContents(web_contents());
    qorai_shields_tab_helper_ =
        QorAIShieldsTabHelper::FromWebContents(web_contents());
    observer_ = std::make_unique<
        testing::NiceMock<MockQorAIShieldsTabHelperObserver>>();
    qorai_shields_tab_helper_->AddObserver(observer_.get());

    TestingBrowserProcess::GetGlobal()->SetApplicationLocale("en-US");
  }

  void TearDown() override {
    qorai_shields_tab_helper_->RemoveObserver(observer_.get());
    qorai_shields_tab_helper_ = nullptr;
    content::RenderViewHostTestHarness::TearDown();
  }

  std::unique_ptr<content::BrowserContext> CreateBrowserContext() override {
    return std::make_unique<TestingProfile>();
  }

  void NavigateTo(GURL url) {
    content::NavigationSimulator::NavigateAndCommitFromBrowser(web_contents(),
                                                               url);
    EXPECT_EQ(web_contents()->GetLastCommittedURL(), url);
  }

  void Reload() { content::NavigationSimulator::Reload(web_contents()); }

  PrefService* profile_prefs() {
    return Profile::FromBrowserContext(web_contents()->GetBrowserContext())
        ->GetPrefs();
  }

  void SetApplicationLocale(const std::string& locale) {
    TestingBrowserProcess::GetGlobal()->SetApplicationLocale(locale);
  }

  PrefService* local_state() {
    return TestingBrowserProcess::GetGlobal()->GetTestingLocalState();
  }

 protected:
  testing::NiceMock<favicon::MockFaviconService> favicon_service_;
  std::unique_ptr<testing::NiceMock<MockQorAIShieldsTabHelperObserver>>
      observer_;
  raw_ptr<QorAIShieldsTabHelper> qorai_shields_tab_helper_;
  base::test::ScopedFeatureList feature_list_;
};

TEST_F(QorAIShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedWhenFeatureDisabled) {
  feature_list_.InitAndDisableFeature(features::kAdblockOnlyMode);

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  NavigateTo(GURL("https://example.com"));
  Reload();
  Reload();
  Reload();
}

TEST_F(QorAIShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedWhenLocaleNotSupported) {
  SetApplicationLocale("fr-FR");

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  NavigateTo(GURL("https://example.com"));
  Reload();
  Reload();
  Reload();
}

TEST_F(QorAIShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedWhenAdBlockOnlyModeAlreadyEnabled) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterPageReloadsMin.name, "1"},
          {features::kAdblockOnlyModePromptAfterPageReloadsMax.name, "2"},
          {features::kAdblockOnlyModePromptAfterPageReloadsInterval.name, "1s"},
      });
  local_state()->SetBoolean(qorai_shields::prefs::kAdBlockOnlyModeEnabled,
                            true);

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  NavigateTo(GURL("https://example.com"));
  Reload();
  Reload();
  Reload();
}

TEST_F(QorAIShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedOnNotReloadNavigation) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterPageReloadsMin.name, "1"},
          {features::kAdblockOnlyModePromptAfterPageReloadsMax.name, "2"},
          {features::kAdblockOnlyModePromptAfterPageReloadsInterval.name, "1s"},
      });

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  NavigateTo(GURL("https://example.com"));
  NavigateTo(GURL("https://example.com"));
  NavigateTo(GURL("https://example.com"));
  NavigateTo(GURL("https://example.com"));
  NavigateTo(GURL("https://example.com"));
}

TEST_F(QorAIShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedWhenReloadsByShieldsChanges) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterPageReloadsMin.name, "1"},
          {features::kAdblockOnlyModePromptAfterPageReloadsMax.name, "2"},
          {features::kAdblockOnlyModePromptAfterPageReloadsInterval.name, "1s"},
      });

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(true);
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(true);
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
}

TEST_F(QorAIShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedByZeroCountFeatureParameters) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterPageReloadsMin.name, "0"},
          {features::kAdblockOnlyModePromptAfterPageReloadsMax.name, "0"},
          {features::kAdblockOnlyModePromptAfterPageReloadsInterval.name, "1s"},
      });

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  NavigateTo(GURL("https://example.com"));
  Reload();
  Reload();
  Reload();
  Reload();
  Reload();
}

TEST_F(QorAIShieldsTabHelperUnitTest, TriggerOnRepeatedReloadsDetected) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterPageReloadsMin.name, "1"},
          {features::kAdblockOnlyModePromptAfterPageReloadsMax.name, "2"},
          {features::kAdblockOnlyModePromptAfterPageReloadsInterval.name, "1s"},
      });

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(2);

  NavigateTo(GURL("https://example.com"));
  Reload();
  Reload();
  Reload();
  Reload();
  Reload();
  testing::Mock::VerifyAndClearExpectations(observer_.get());

  // Counter is reset after more than
  // `kAdblockOnlyModePromptAfterPageReloadsInterval` time interval. Fast
  // forward by 2 times to ensure the counter is reset.
  task_environment()->FastForwardBy(
      2 * features::kAdblockOnlyModePromptAfterPageReloadsInterval.Get());

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(2);
  Reload();
  Reload();
  Reload();
  Reload();
  Reload();
  testing::Mock::VerifyAndClearExpectations(observer_.get());
}

TEST_F(QorAIShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedWhenPromptDismissed) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterPageReloadsMin.name, "1"},
          {features::kAdblockOnlyModePromptAfterPageReloadsMax.name, "2"},
          {features::kAdblockOnlyModePromptAfterPageReloadsInterval.name, "1s"},
      });
  qorai_shields_tab_helper_->SetQorAIShieldsAdBlockOnlyModePromptDismissed();

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  NavigateTo(GURL("https://example.com"));
  Reload();
  Reload();
  Reload();
  Reload();
  Reload();
}

TEST_F(QorAIShieldsTabHelperUnitTest,
       DontShowShieldsDisabledAdBlockOnlyModePromptWhenFeatureDisabled) {
  feature_list_.InitAndDisableFeature(features::kAdblockOnlyMode);

  // Default value of
  // `features::kAdblockOnlyModePromptAfterShieldsDisabledCount` is 5.
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);

  EXPECT_EQ(
      profile_prefs()->GetInteger(qorai_shields::prefs::kShieldsDisabledCount),
      0);

  EXPECT_FALSE(qorai_shields_tab_helper_
                   ->ShouldShowShieldsDisabledAdBlockOnlyModePrompt());
}

TEST_F(QorAIShieldsTabHelperUnitTest,
       DontShowShieldsDisabledAdBlockOnlyModePromptWhenLocaleNotSupported) {
  SetApplicationLocale("fr-FR");

  // Default value of
  // `features::kAdblockOnlyModePromptAfterShieldsDisabledCount` is 5.
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);

  EXPECT_EQ(
      profile_prefs()->GetInteger(qorai_shields::prefs::kShieldsDisabledCount),
      0);

  EXPECT_FALSE(qorai_shields_tab_helper_
                   ->ShouldShowShieldsDisabledAdBlockOnlyModePrompt());
}

TEST_F(QorAIShieldsTabHelperUnitTest,
       DontShowShieldsDisabledAdBlockOnlyModePromptWhenPromptDismissed) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterShieldsDisabledCount.name, "2"},
      });
  qorai_shields_tab_helper_->SetQorAIShieldsAdBlockOnlyModePromptDismissed();

  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  EXPECT_FALSE(qorai_shields_tab_helper_
                   ->ShouldShowShieldsDisabledAdBlockOnlyModePrompt());
}

TEST_F(QorAIShieldsTabHelperUnitTest,
       ShowShieldsDisabledAdBlockOnlyModePrompt) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterShieldsDisabledCount.name, "2"},
      });

  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  EXPECT_FALSE(qorai_shields_tab_helper_
                   ->ShouldShowShieldsDisabledAdBlockOnlyModePrompt());

  qorai_shields_tab_helper_->SetQorAIShieldsEnabled(false);
  EXPECT_TRUE(qorai_shields_tab_helper_
                  ->ShouldShowShieldsDisabledAdBlockOnlyModePrompt());
}

}  // namespace qorai_shields
