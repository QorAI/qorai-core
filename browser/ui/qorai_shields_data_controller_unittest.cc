/*  Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>

#include "base/memory/raw_ptr.h"
#include "qorai/browser/qorai_shields/qorai_shields_tab_helper.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "qorai/components/qorai_shields/core/common/qorai_shield_constants.h"
#include "build/build_config.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile.h"
#include "chrome/test/base/testing_profile_manager.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/favicon/content/content_favicon_driver.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/web_contents.h"
#include "content/public/test/browser_task_environment.h"
#include "content/public/test/test_renderer_host.h"
#include "content/public/test/web_contents_tester.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

using qorai_shields::QoraiShieldsTabHelper;
using qorai_shields::ControlType;
using qorai_shields::mojom::AdBlockMode;

namespace {
constexpr char kTestProfileName[] = "TestProfile";

class MockObserver : public QoraiShieldsTabHelper::Observer {
 public:
  MOCK_METHOD(void, OnResourcesChanged, (), (override));
  MOCK_METHOD(void, OnShieldsEnabledChanged, (), (override));
};
}  // namespace

class QoraiShieldsDataControllerTest : public testing::Test {
 public:
  QoraiShieldsDataControllerTest() = default;
  ~QoraiShieldsDataControllerTest() override = default;

  QoraiShieldsDataControllerTest(const QoraiShieldsDataControllerTest&) =
      delete;
  QoraiShieldsDataControllerTest& operator=(
      const QoraiShieldsDataControllerTest&) = delete;

  void SetUp() override {
    TestingBrowserProcess* browser_process = TestingBrowserProcess::GetGlobal();
    profile_manager_ = std::make_unique<TestingProfileManager>(browser_process);
    ASSERT_TRUE(profile_manager_->SetUp());
    profile_ = profile_manager_->CreateTestingProfile(kTestProfileName);

    test_web_contents_ =
        content::WebContentsTester::CreateTestWebContents(profile_, nullptr);
    favicon::ContentFaviconDriver::CreateForWebContents(
        test_web_contents_.get(), nullptr);
    QoraiShieldsTabHelper::CreateForWebContents(test_web_contents_.get());
  }

  void TearDown() override {
    test_web_contents_.reset();
    profile_ = nullptr;
    profile_manager_->DeleteTestingProfile(kTestProfileName);
  }

  Profile* profile() { return profile_; }
  content::WebContents* web_contents() { return test_web_contents_.get(); }

  void SetLastCommittedUrl(const GURL& url) {
    content::WebContentsTester::For(web_contents())->SetLastCommittedURL(url);
  }

  QoraiShieldsTabHelper* GetShieldsDataController() {
    return QoraiShieldsTabHelper::FromWebContents(web_contents());
  }

  ContentSetting GetContentSettingFor(Profile* profile,
                                      ContentSettingsType type,
                                      GURL secondary_url = GURL()) {
    auto* map = HostContentSettingsMapFactory::GetForProfile(profile);
    auto* controller = GetShieldsDataController();

    return map->GetContentSetting(controller->GetCurrentSiteURL(),
                                  secondary_url, type);
  }

  ControlType GetSettingForCosmeticFiltering(
      const GURL& secondary_url = GURL::EmptyGURL()) {
    auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
    auto* controller = GetShieldsDataController();

    return qorai_shields::CosmeticFilteringSetting::FromValue(
        map->GetWebsiteSetting(
            controller->GetCurrentSiteURL(), secondary_url,
            qorai_shields::CosmeticFilteringSetting::kContentSettingsType));
  }

  void SetContentSettingFor(ContentSettingsType type,
                            ContentSetting setting,
                            GURL secondary_url = GURL()) {
    auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
    auto* controller = GetShieldsDataController();

    map->SetContentSettingCustomScope(
        qorai_shields::GetPatternFromURL(controller->GetCurrentSiteURL()),
        qorai_shields::GetPatternFromURL(secondary_url), type, setting);
  }

  void SetSettingForCosmeticFiltering(
      ControlType setting,
      const GURL& secondary_url = GURL::EmptyGURL()) {
    auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
    auto* controller = GetShieldsDataController();

    map->SetWebsiteSettingCustomScope(
        qorai_shields::GetPatternFromURL(controller->GetCurrentSiteURL()),
        qorai_shields::GetPatternFromURL(secondary_url),
        qorai_shields::CosmeticFilteringSetting::kContentSettingsType,
        qorai_shields::CosmeticFilteringSetting::ToValue(setting));
  }

 private:
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<content::WebContents> test_web_contents_;
  content::RenderViewHostTestEnabler render_view_host_test_enabler_;
  raw_ptr<Profile> profile_;
  std::unique_ptr<TestingProfileManager> profile_manager_;
};

TEST_F(QoraiShieldsDataControllerTest, RegularVsIncognitoContentSettings) {
  const GURL url("http://qorai.com");
  SetLastCommittedUrl(url);

  Profile* otr_profile =
      profile()->GetPrimaryOTRProfile(/*create_if_needed=*/true);
  auto otr_web_contents =
      content::WebContentsTester::CreateTestWebContents(otr_profile, nullptr);
  favicon::ContentFaviconDriver::CreateForWebContents(otr_web_contents.get(),
                                                      nullptr);
  auto* incognito_controller =
      QoraiShieldsTabHelper::GetOrCreateForWebContents(otr_web_contents.get());
  content::WebContentsTester::For(otr_web_contents.get())
      ->SetLastCommittedURL(GURL("http://qorai.com"));

  incognito_controller->SetAdBlockMode(AdBlockMode::ALLOW);

  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetContentSettingFor(otr_profile, ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_ALLOW);
}

TEST_F(QoraiShieldsDataControllerTest, SetAdBlockMode_ForOrigin_1) {
  auto* controller = GetShieldsDataController();
  SetLastCommittedUrl(GURL("http://qorai.com"));

  /* DEFAULT */
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK_THIRD_PARTY);

  /* ALLOW */
  controller->SetAdBlockMode(AdBlockMode::ALLOW);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_ALLOW);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::ALLOW);

  /* STANDARD */
  controller->SetAdBlockMode(AdBlockMode::STANDARD);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK_THIRD_PARTY);

  /* ALLOW */
  controller->SetAdBlockMode(AdBlockMode::ALLOW);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_ALLOW);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::ALLOW);

  /* AGGRESSIVE */
  controller->SetAdBlockMode(AdBlockMode::AGGRESSIVE);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK);

  /* ALLOW */
  controller->SetAdBlockMode(AdBlockMode::ALLOW);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_ALLOW);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::ALLOW);
}

TEST_F(QoraiShieldsDataControllerTest, SetAdBlockMode_ForOrigin_2) {
  auto* controller = GetShieldsDataController();
  SetLastCommittedUrl(GURL("http://qorai.com"));

  /* DEFAULT */
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK_THIRD_PARTY);

  /* STANDARD */
  controller->SetAdBlockMode(AdBlockMode::STANDARD);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK_THIRD_PARTY);

  /* ALLOW */
  controller->SetAdBlockMode(AdBlockMode::ALLOW);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_ALLOW);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::ALLOW);

  /* STANDARD */
  controller->SetAdBlockMode(AdBlockMode::STANDARD);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK_THIRD_PARTY);

  /* AGGRESSIVE */
  controller->SetAdBlockMode(AdBlockMode::AGGRESSIVE);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK);

  /* STANDARD */
  controller->SetAdBlockMode(AdBlockMode::STANDARD);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK_THIRD_PARTY);
}

TEST_F(QoraiShieldsDataControllerTest, SetAdBlockMode_ForOrigin_3) {
  auto* controller = GetShieldsDataController();
  SetLastCommittedUrl(GURL("http://qorai.com"));

  /* DEFAULT */
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK_THIRD_PARTY);

  /* AGGRESSIVE */
  controller->SetAdBlockMode(AdBlockMode::AGGRESSIVE);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK);

  /* ALLOW */
  controller->SetAdBlockMode(AdBlockMode::ALLOW);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_ALLOW);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::ALLOW);

  /* AGGRESSIVE */
  controller->SetAdBlockMode(AdBlockMode::AGGRESSIVE);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK);

  /* STANDARD */
  controller->SetAdBlockMode(AdBlockMode::STANDARD);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK_THIRD_PARTY);

  /* AGGRESSIVE */
  controller->SetAdBlockMode(AdBlockMode::AGGRESSIVE);
  EXPECT_EQ(GetContentSettingFor(profile(), ContentSettingsType::QORAI_ADS),
            CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetSettingForCosmeticFiltering(), ControlType::BLOCK);
}

TEST_F(QoraiShieldsDataControllerTest, GetAdBlockMode_ForOrigin) {
  auto* controller = GetShieldsDataController();
  SetLastCommittedUrl(GURL("http://qorai.com"));

  /* DEFAULT */
  EXPECT_EQ(controller->GetAdBlockMode(), AdBlockMode::STANDARD);

  /* ALLOW */
  SetContentSettingFor(ContentSettingsType::QORAI_ADS, CONTENT_SETTING_ALLOW);
  EXPECT_EQ(controller->GetAdBlockMode(), AdBlockMode::ALLOW);

  /* STANDARD */
  SetContentSettingFor(ContentSettingsType::QORAI_ADS, CONTENT_SETTING_BLOCK);
  SetSettingForCosmeticFiltering(ControlType::BLOCK_THIRD_PARTY);
  EXPECT_EQ(controller->GetAdBlockMode(), AdBlockMode::STANDARD);

  /* AGGRESSIVE */
  SetContentSettingFor(ContentSettingsType::QORAI_ADS, CONTENT_SETTING_BLOCK);
  SetSettingForCosmeticFiltering(ControlType::BLOCK);
  EXPECT_EQ(controller->GetAdBlockMode(), AdBlockMode::AGGRESSIVE);
}

TEST_F(QoraiShieldsDataControllerTest, Observer_OnShieldsEnabledChangedTest) {
  // Set url for default web contents.
  SetLastCommittedUrl(GURL("http://qorai.com"));

  // Create another web contents for testing whether its
  // OnShieldsEnabledChanged() callback is called when shields enabled is
  // changed by another web contents when both loaded same url.
  MockObserver observer_2;
  EXPECT_CALL(observer_2, OnShieldsEnabledChanged).Times(1);
  auto web_contents_2 =
      content::WebContentsTester::CreateTestWebContents(profile(), nullptr);
  favicon::ContentFaviconDriver::CreateForWebContents(web_contents_2.get(),
                                                      nullptr);
  QoraiShieldsTabHelper::CreateForWebContents(web_contents_2.get());
  auto* ctrl_2 = QoraiShieldsTabHelper::FromWebContents(web_contents_2.get());
  ctrl_2->AddObserver(&observer_2);
  content::WebContentsTester::For(web_contents_2.get())
      ->SetLastCommittedURL(GURL("http://qorai.com"));

  // Create another web contents for testing whether its
  // OnShieldsEnabledChanged() callback is *not* called when shields enabled is
  // changed by another web contents when both loaded *different* url.
  MockObserver observer_3;
  EXPECT_CALL(observer_3, OnShieldsEnabledChanged).Times(0);
  auto web_contents_3 =
      content::WebContentsTester::CreateTestWebContents(profile(), nullptr);
  favicon::ContentFaviconDriver::CreateForWebContents(web_contents_3.get(),
                                                      nullptr);
  QoraiShieldsTabHelper::CreateForWebContents(web_contents_3.get());
  auto* ctrl_3 = QoraiShieldsTabHelper::FromWebContents(web_contents_3.get());
  ctrl_3->AddObserver(&observer_3);
  content::WebContentsTester::For(web_contents_3.get())
      ->SetLastCommittedURL(GURL("http://github.com"));

  // Change default web contents' shields enabled setting.
  // And this changes will affect |web_contents_2| as both loaded same url.
  GetShieldsDataController()->SetQoraiShieldsEnabled(false);

  ctrl_2->RemoveObserver(&observer_2);
  ctrl_3->RemoveObserver(&observer_3);
}

TEST_F(QoraiShieldsDataControllerTest, SetQoraiShieldsEnabledAsDefaultValue) {
  // Set url for default web contents.
  SetLastCommittedUrl(GURL("http://qorai.com"));
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  EXPECT_EQ(map->GetDefaultContentSetting(ContentSettingsType::QORAI_SHIELDS,
                                          nullptr),
            CONTENT_SETTING_ALLOW);

  EXPECT_TRUE(GetShieldsDataController()->GetQoraiShieldsEnabled());
  GetShieldsDataController()->SetQoraiShieldsEnabled(false);
  EXPECT_FALSE(GetShieldsDataController()->GetQoraiShieldsEnabled());
  EXPECT_FALSE(profile()
                   ->GetPrefs()
                   ->GetDict("profile.content_settings.exceptions.qoraiShields")
                   .empty());

  GetShieldsDataController()->SetQoraiShieldsEnabled(true);
  EXPECT_TRUE(GetShieldsDataController()->GetQoraiShieldsEnabled());
  EXPECT_TRUE(profile()
                  ->GetPrefs()
                  ->GetDict("profile.content_settings.exceptions.qoraiShields")
                  .empty());
}

TEST_F(QoraiShieldsDataControllerTest, AllowedOnceScripts) {
  EXPECT_EQ(GetShieldsDataController()->GetAllowedJsList().size(), 0u);
  GetShieldsDataController()->HandleItemAllowedOnce(
      qorai_shields::kJavaScript, "https://url1.com/script.js");
  EXPECT_EQ(GetShieldsDataController()->GetAllowedJsList().size(), 1u);
  GetShieldsDataController()->HandleItemAllowedOnce(
      qorai_shields::kJavaScript, "https://url2.com/script.js");
  EXPECT_EQ(GetShieldsDataController()->GetAllowedJsList().size(), 2u);
  GetShieldsDataController()->HandleItemAllowedOnce(
      qorai_shields::kJavaScript, "https://url3.com/script.js");
  EXPECT_EQ(GetShieldsDataController()->GetAllowedJsList().size(), 3u);

  // Making sure we exclude duplicates
  GetShieldsDataController()->HandleItemAllowedOnce(
      qorai_shields::kJavaScript, "https://url2.com/script.js");
  GetShieldsDataController()->HandleItemAllowedOnce(
      qorai_shields::kJavaScript, "https://url3.com/script.js");
  EXPECT_EQ(GetShieldsDataController()->GetAllowedJsList().size(), 3u);

  GetShieldsDataController()->ClearAllResourcesList();
  EXPECT_EQ(GetShieldsDataController()->GetAllowedJsList().size(), 0u);
}
