// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"

#include <memory>
#include <utility>

#include "base/files/scoped_temp_dir.h"
#include "base/test/scoped_feature_list.h"
#include "qorai/browser/profiles/qorai_profile_manager.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_p3a.h"
#include "qorai/components/qorai_shields/core/common/qorai_shield_utils.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/constants/pref_names.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/cookie_settings_factory.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile.h"
#include "components/content_settings/core/browser/cookie_settings.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/content_settings/core/common/pref_names.h"
#include "components/prefs/pref_service.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "content/public/test/browser_task_environment.h"
#include "content/public/test/test_utils.h"
#include "net/base/features.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

using qorai_shields::ControlType;
using qorai_shields::ControlTypeFromString;
using qorai_shields::ControlTypeToString;
using qorai_shields::DomainBlockingType;
using qorai_shields::GetPatternFromURL;
using qorai_shields::features::kQoraiDomainBlock;

class QoraiShieldsUtilTest : public testing::Test {
 public:
  QoraiShieldsUtilTest() = default;
  QoraiShieldsUtilTest(const QoraiShieldsUtilTest&) = delete;
  QoraiShieldsUtilTest& operator=(const QoraiShieldsUtilTest&) = delete;
  ~QoraiShieldsUtilTest() override = default;

  void SetUp() override {
    ASSERT_TRUE(temp_dir_.CreateUniqueTempDir());
    TestingBrowserProcess::GetGlobal()->SetProfileManager(
        CreateProfileManagerForTest());
    TestingProfile::Builder builder;
    builder.SetPath(temp_dir_.GetPath());
    profile_ = builder.Build();
    g_browser_process->profile_manager()->InitProfileUserPrefs(profile_.get());
  }

  void TearDown() override {
    profile_.reset();
    TestingBrowserProcess::GetGlobal()->SetProfileManager(nullptr);
    content::RunAllTasksUntilIdle();
  }

  TestingProfile* profile() { return profile_.get(); }

  void ExpectDomainBlockingType(const GURL& url,
                                DomainBlockingType domain_blocking_type) {
    auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
    auto setting = qorai_shields::GetDomainBlockingType(map, url);
    EXPECT_EQ(domain_blocking_type, setting);
  }

 private:
  std::unique_ptr<QoraiProfileManager> CreateProfileManagerForTest() {
    return std::make_unique<QoraiProfileManagerWithoutInit>(
        temp_dir_.GetPath());
  }

  base::ScopedTempDir temp_dir_;
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<TestingProfile> profile_;
};

class QoraiShieldsUtilDomainBlockFeatureTest : public QoraiShieldsUtilTest {
 public:
  QoraiShieldsUtilDomainBlockFeatureTest() {
    feature_list_.InitAndDisableFeature(kQoraiDomainBlock);
  }

 private:
  base::test::ScopedFeatureList feature_list_;
};

TEST_F(QoraiShieldsUtilTest, GetPatternFromURL) {
  // wildcard
  auto pattern = GetPatternFromURL(GURL());
  EXPECT_EQ(ContentSettingsPattern::Wildcard(), pattern);

  // scheme is a wildcard, should match any scheme
  pattern = GetPatternFromURL(GURL("http://qorai.com"));
  EXPECT_TRUE(pattern.Matches(GURL("http://qorai.com")));
  EXPECT_TRUE(pattern.Matches(GURL("http://qorai.com/path1")));
  EXPECT_TRUE(pattern.Matches(GURL("http://qorai.com/path2")));
  EXPECT_TRUE(pattern.Matches(GURL("https://qorai.com")));
  EXPECT_TRUE(pattern.Matches(GURL("ftp://qorai.com")));
  EXPECT_FALSE(pattern.Matches(GURL("http://subdomain.qorai.com")));
  EXPECT_FALSE(pattern.Matches(GURL("http://qorai2.com")));

  // path is a wildcard
  pattern = GetPatternFromURL(GURL("http://qorai.com/path1"));
  EXPECT_TRUE(pattern.Matches(GURL("http://qorai.com")));
  EXPECT_TRUE(pattern.Matches(GURL("http://qorai.com/path1")));
  EXPECT_TRUE(pattern.Matches(GURL("http://qorai.com/path2")));
  EXPECT_FALSE(pattern.Matches(GURL("http://subdomain.qorai.com")));
  EXPECT_FALSE(pattern.Matches(GURL("http://qorai2.com")));

  // port is a wildcard
  pattern = GetPatternFromURL(GURL("http://qorai.com:8080"));
  EXPECT_TRUE(pattern.Matches(GURL("http://qorai.com")));
  EXPECT_TRUE(pattern.Matches(GURL("http://qorai.com:8080")));
  EXPECT_TRUE(pattern.Matches(GURL("http://qorai.com:8080/path1")));
  EXPECT_TRUE(pattern.Matches(GURL("http://qorai.com:8080/path2")));
  EXPECT_TRUE(pattern.Matches(GURL("http://qorai.com:5555")));
  EXPECT_TRUE(pattern.Matches(GURL("https://qorai.com")));
  EXPECT_TRUE(pattern.Matches(GURL("https://qorai.com:8080")));
  EXPECT_FALSE(pattern.Matches(GURL("http://subdomain.qorai.com")));
  EXPECT_FALSE(pattern.Matches(GURL("http://qorai2.com")));

  // with implied port
  pattern = GetPatternFromURL(GURL("https://brianbondy.com"));
  EXPECT_EQ(pattern.ToString(), "brianbondy.com");
  pattern = GetPatternFromURL(GURL("http://brianbondy.com"));
  EXPECT_EQ(pattern.ToString(), "brianbondy.com");
  // with specified port
  pattern = GetPatternFromURL(GURL("http://brianbondy.com:8080"));
  EXPECT_EQ(pattern.ToString(), "brianbondy.com");
}

TEST_F(QoraiShieldsUtilTest, ControlTypeToString) {
  EXPECT_EQ("block", ControlTypeToString(ControlType::BLOCK));
  EXPECT_EQ("allow", ControlTypeToString(ControlType::ALLOW));
  EXPECT_EQ("block_third_party",
            ControlTypeToString(ControlType::BLOCK_THIRD_PARTY));
}

TEST_F(QoraiShieldsUtilTest, ControlTypeFromString) {
  EXPECT_EQ(ControlType::BLOCK, ControlTypeFromString("block"));
  EXPECT_EQ(ControlType::ALLOW, ControlTypeFromString("allow"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY,
            ControlTypeFromString("block_third_party"));
}

/* QORAI_SHIELDS CONTROL */
TEST_F(QoraiShieldsUtilTest, SetQoraiShieldsEnabled_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  qorai_shields::SetQoraiShieldsEnabled(map, false, GURL("http://qorai.com"));
  // setting should apply to origin
  auto setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                        ContentSettingsType::QORAI_SHIELDS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // setting should apply to different scheme
  setting = map->GetContentSetting(GURL("https://qorai.com"), GURL(),
                                   ContentSettingsType::QORAI_SHIELDS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // setting should not apply to default
  setting = map->GetContentSetting(GURL(), GURL(),
                                   ContentSettingsType::QORAI_SHIELDS);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  GURL host2("http://host2.com");
  GURL host1("http://host1.com");
  // Set shields as disabled for initial value.
  qorai_shields::SetQoraiShieldsEnabled(map, false, host1);
  // host2.com is enabled by default
  setting =
      map->GetContentSetting(host2, GURL(), ContentSettingsType::QORAI_SHIELDS);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // Set policy to disable shields for specific domain.
  base::Value::List disabled_list;
  disabled_list.Append("[*.]host2.com");
  disabled_list.Append("*.*");
  profile()->GetTestingPrefService()->SetManagedPref(
      kManagedQoraiShieldsDisabledForUrls, std::move(disabled_list));

  base::Value::List enabled_list;
  enabled_list.Append("[*.]host1.com");
  profile()->GetTestingPrefService()->SetManagedPref(
      kManagedQoraiShieldsEnabledForUrls, std::move(enabled_list));

  // setting should apply block to origin.
  setting =
      map->GetContentSetting(host2, GURL(), ContentSettingsType::QORAI_SHIELDS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  qorai_shields::SetQoraiShieldsEnabled(map, true, host2);

  // setting should not be changed.
  EXPECT_FALSE(qorai_shields::GetQoraiShieldsEnabled(map, host2));

  // setting should apply enabled to origin.
  EXPECT_TRUE(qorai_shields::GetQoraiShieldsEnabled(map, host1));
  qorai_shields::SetQoraiShieldsEnabled(map, false, host1);
  // setting should not be changed.
  EXPECT_TRUE(qorai_shields::GetQoraiShieldsEnabled(map, host1));

  // setting should not apply to default
  EXPECT_TRUE(qorai_shields::GetQoraiShieldsEnabled(map, GURL()));
}

TEST_F(QoraiShieldsUtilTest, IsQoraiShieldsManaged) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  GURL host2("http://host2.com");
  GURL host1("http://host1.com");
  EXPECT_FALSE(qorai_shields::IsQoraiShieldsManaged(
      profile()->GetTestingPrefService(), map, host2));

  base::Value::List disabled_list;
  disabled_list.Append("[*.]host2.com");
  profile()->GetTestingPrefService()->SetManagedPref(
      kManagedQoraiShieldsDisabledForUrls, std::move(disabled_list));
  // only disabled pref set
  EXPECT_TRUE(qorai_shields::IsQoraiShieldsManaged(
      profile()->GetTestingPrefService(), map, host2));

  EXPECT_FALSE(qorai_shields::IsQoraiShieldsManaged(
      profile()->GetTestingPrefService(), map, GURL("http://host1.com")));

  base::Value::List enabled_list;
  enabled_list.Append("[*.]host1.com");
  profile()->GetTestingPrefService()->SetManagedPref(
      kManagedQoraiShieldsEnabledForUrls, std::move(enabled_list));

  // both disabled/enabled prefs set
  EXPECT_TRUE(qorai_shields::IsQoraiShieldsManaged(
      profile()->GetTestingPrefService(), map, host2));

  EXPECT_TRUE(qorai_shields::IsQoraiShieldsManaged(
      profile()->GetTestingPrefService(), map, host1));

  profile()->GetTestingPrefService()->RemoveManagedPref(
      kManagedQoraiShieldsDisabledForUrls);

  // only enabled prefs set
  EXPECT_FALSE(qorai_shields::IsQoraiShieldsManaged(
      profile()->GetTestingPrefService(), map, host2));

  EXPECT_TRUE(qorai_shields::IsQoraiShieldsManaged(
      profile()->GetTestingPrefService(), map, host1));
}

TEST_F(QoraiShieldsUtilTest, SetQoraiShieldsEnabled_IsNotHttpHttps) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto setting =
      qorai_shields::GetQoraiShieldsEnabled(map, GURL("chrome://preferences"));
  EXPECT_EQ(false, setting);
  qorai_shields::SetQoraiShieldsEnabled(map, ControlType::ALLOW,
                                        GURL("chrome://preferences"));
  setting =
      qorai_shields::GetQoraiShieldsEnabled(map, GURL("chrome://preferences"));
  EXPECT_EQ(false, setting);

  setting = qorai_shields::GetQoraiShieldsEnabled(map, GURL("about:blank"));
  EXPECT_EQ(false, setting);
  qorai_shields::SetQoraiShieldsEnabled(map, ControlType::ALLOW,
                                        GURL("about:blank"));
  setting = qorai_shields::GetQoraiShieldsEnabled(map, GURL("about:blank"));
  EXPECT_EQ(false, setting);
}

TEST_F(QoraiShieldsUtilTest, GetQoraiShieldsEnabled_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = qorai_shields::GetQoraiShieldsEnabled(map, GURL());
  EXPECT_EQ(true, setting);
  setting =
      qorai_shields::GetQoraiShieldsEnabled(map, GURL("http://qorai.com"));
  EXPECT_EQ(true, setting);
  setting =
      qorai_shields::GetQoraiShieldsEnabled(map, GURL("https://qorai.com"));
  EXPECT_EQ(true, setting);

  /* BLOCK */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://qorai.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::QORAI_SHIELDS,
      CONTENT_SETTING_BLOCK);
  setting =
      qorai_shields::GetQoraiShieldsEnabled(map, GURL("http://qorai.com/*"));
  EXPECT_EQ(false, setting);
  // https in unchanged
  setting =
      qorai_shields::GetQoraiShieldsEnabled(map, GURL("https://qorai.com"));
  EXPECT_EQ(true, setting);
  // default is unchanged
  setting = qorai_shields::GetQoraiShieldsEnabled(map, GURL());
  EXPECT_EQ(true, setting);
}

TEST_F(QoraiShieldsUtilTest, GetQoraiShieldsEnabled_IsNotHttpHttps) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto setting =
      qorai_shields::GetQoraiShieldsEnabled(map, GURL("chrome://preferences"));
  EXPECT_EQ(false, setting);

  setting = qorai_shields::GetQoraiShieldsEnabled(map, GURL("about:blank"));
  EXPECT_EQ(false, setting);
}

/* AD CONTROL */
TEST_F(QoraiShieldsUtilTest, SetAdControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  // settings should be default
  auto setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::QORAI_ADS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                   ContentSettingsType::QORAI_ADS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  /* ALLOW */
  qorai_shields::SetAdControlType(map, ControlType::ALLOW, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::QORAI_ADS);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                   ContentSettingsType::QORAI_ADS);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  /* BLOCK */
  qorai_shields::SetAdControlType(map, ControlType::BLOCK, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::QORAI_ADS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                   ContentSettingsType::QORAI_ADS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
}

TEST_F(QoraiShieldsUtilTest, SetAdControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  qorai_shields::SetAdControlType(map, ControlType::ALLOW,
                                  GURL("http://qorai.com"));
  // setting should apply to origin
  auto setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                        ContentSettingsType::QORAI_ADS);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should also apply to different scheme
  setting = map->GetContentSetting(GURL("https://qorai.com"), GURL(),
                                   ContentSettingsType::QORAI_ADS);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should not apply to default
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::QORAI_ADS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
}

TEST_F(QoraiShieldsUtilTest, GetAdControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = qorai_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::QORAI_ADS, CONTENT_SETTING_ALLOW);
  setting = qorai_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* BLOCK */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::QORAI_ADS, CONTENT_SETTING_BLOCK);
  setting = qorai_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);
}

TEST_F(QoraiShieldsUtilTest, GetAdControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = qorai_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = qorai_shields::GetAdControlType(map, GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = qorai_shields::GetAdControlType(map, GURL("https://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://qorai.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::QORAI_ADS,
      CONTENT_SETTING_ALLOW);
  setting = qorai_shields::GetAdControlType(map, GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  // https in unchanged
  setting = qorai_shields::GetAdControlType(map, GURL("https://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  // default is unchanged
  setting = qorai_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* BLOCK */
  // change default to allow
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::QORAI_ADS, CONTENT_SETTING_ALLOW);
  setting = qorai_shields::GetAdControlType(map, GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = qorai_shields::GetAdControlType(map, GURL("https://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = qorai_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  // set override to block
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://qorai.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::QORAI_ADS,
      CONTENT_SETTING_BLOCK);
  setting = qorai_shields::GetAdControlType(map, GURL("http://qorai.com/*"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  // https in unchanged
  setting = qorai_shields::GetAdControlType(map, GURL("https://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  // default is unchanged
  setting = qorai_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);
}

/* COOKIE CONTROL */
TEST_F(QoraiShieldsUtilTest, SetCookieControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());
  /* ALLOW */
  qorai_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::ALLOW, GURL());
  auto setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  // setting should apply to all urls
  setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  EXPECT_FALSE(cookies->ShouldBlockThirdPartyCookies());
  setting =
      map->GetContentSetting(GURL("http://qorai.com"), GURL("http://qorai.com"),
                             ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  /* BLOCK */
  qorai_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  setting = map->GetContentSetting(GURL(), GURL("https://firstParty"),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  EXPECT_TRUE(cookies->ShouldBlockThirdPartyCookies());
  // setting should apply to all urls
  setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  setting = map->GetContentSetting(GURL("http://qorai.com"),
                                   GURL("https://firstParty"),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // Ensure BLOCK with kCookieControlsMode == kOff still blocks all cookies.
  profile()->GetPrefs()->SetInteger(
      ::prefs::kCookieControlsMode,
      static_cast<int>(content_settings::CookieControlsMode::kOff));
  EXPECT_FALSE(cookies->ShouldBlockThirdPartyCookies());
  // setting should apply to all urls
  setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  setting = map->GetContentSetting(GURL("http://qorai.com"),
                                   GURL("https://firstParty"),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  /* BLOCK_THIRD_PARTY */
  qorai_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK_THIRD_PARTY, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  EXPECT_TRUE(cookies->ShouldBlockThirdPartyCookies());
  setting = map->GetContentSetting(GURL(), GURL("https://firstParty"),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should apply to all urls
  setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  EXPECT_TRUE(cookies->ShouldBlockThirdPartyCookies());
  setting =
      map->GetContentSetting(GURL("http://qorai.com"), GURL("http://qorai.com"),
                             ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  EXPECT_TRUE(cookies->ShouldBlockThirdPartyCookies());
}

TEST_F(QoraiShieldsUtilTest, SetCookieControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());

  qorai_shields::SetCookieControlType(
      map, profile()->GetPrefs(), ControlType::ALLOW, GURL("http://qorai.com"));
  // override should apply to origin
  auto setting = qorai_shields::GetCookieControlType(map, cookies.get(),
                                                     GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  // override should also apply to different scheme
  setting = qorai_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
}

TEST_F(QoraiShieldsUtilTest, GetCookieControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());

  EXPECT_EQ(CONTENT_SETTING_ALLOW,
            map->GetContentSetting(GURL::EmptyGURL(), GURL::EmptyGURL(),
                                   ContentSettingsType::QORAI_COOKIES));
  auto setting =
      qorai_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
  setting = qorai_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  /* ALLOW */
  qorai_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::ALLOW, GURL());
  setting = qorai_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = qorai_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* BLOCK */
  qorai_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK, GURL());
  setting = qorai_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = qorai_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* BLOCK_THIRD_PARTY */
  qorai_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK_THIRD_PARTY, GURL());
  setting = qorai_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
  setting = qorai_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  // Setting CONTENT_SETTING_DEFAULT doesn't produce any CHECKS or crashes.
  map->SetDefaultContentSetting(ContentSettingsType::QORAI_COOKIES,
                                CONTENT_SETTING_DEFAULT);
}

TEST_F(QoraiShieldsUtilTest, GetCookieControlType_WithUserSettings) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());

  struct CookieState {
    bool block_first_party = false;
    bool block_third_party = false;
  };

  auto get_effective_cookie_state =
      [](content_settings::CookieSettings* cookie_settings,
         const GURL& url) -> CookieState {
    const auto first_party_blocked =
        cookie_settings->GetCookieSetting(
            url, net::SiteForCookies::FromUrl(url), url,
            net::CookieSettingOverrides(), nullptr) == CONTENT_SETTING_BLOCK;

    const auto third_party_blocked =
        cookie_settings->GetCookieSetting(
            GURL::EmptyGURL(), net::SiteForCookies(), url,
            net::CookieSettingOverrides(), nullptr) == CONTENT_SETTING_BLOCK;

    return {first_party_blocked, third_party_blocked};
  };

  auto cookies_settings =
      get_effective_cookie_state(cookies.get(), GURL("http://qorai.com"));
  EXPECT_FALSE(cookies_settings.block_first_party);
  EXPECT_TRUE(cookies_settings.block_third_party);

  // block all
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(),
      ContentSettingsPattern::FromURL(GURL("http://qorai.com")),
      ContentSettingsType::COOKIES, CONTENT_SETTING_BLOCK);

  auto setting = qorai_shields::GetCookieControlType(map, cookies.get(),
                                                     GURL("http://qorai.com"));
  // User settings doesn't affect QORAI_COOKIES
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  cookies_settings =
      get_effective_cookie_state(cookies.get(), GURL("http://qorai.com"));
  EXPECT_TRUE(cookies_settings.block_first_party);
  EXPECT_TRUE(cookies_settings.block_third_party);

  qorai_shields::SetCookieControlType(
      map, profile()->GetPrefs(), ControlType::ALLOW, GURL("http://qorai.com"));
  setting = qorai_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://qorai.com"));
  // User settings still doesn't affect QORAI_COOKIES
  EXPECT_EQ(ControlType::ALLOW, setting);

  cookies_settings =
      get_effective_cookie_state(cookies.get(), GURL("http://qorai.com"));
  EXPECT_FALSE(cookies_settings.block_first_party);
  EXPECT_FALSE(cookies_settings.block_third_party);
}

TEST_F(QoraiShieldsUtilTest, GetCookieControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());

  auto setting = qorai_shields::GetCookieControlType(map, cookies.get(),
                                                     GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  /* ALLOW */
  qorai_shields::SetCookieControlType(
      map, profile()->GetPrefs(), ControlType::ALLOW, GURL("http://qorai.com"));
  setting = qorai_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = qorai_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  /* BLOCK */
  qorai_shields::SetCookieControlType(
      map, profile()->GetPrefs(), ControlType::BLOCK, GURL("http://qorai.com"));
  setting = qorai_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = qorai_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  /* BLOCK_THIRD_PARTY */
  qorai_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK_THIRD_PARTY,
                                      GURL("http://qorai.com"));
  setting = qorai_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
  setting = qorai_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
}

TEST_F(QoraiShieldsUtilTest,
       GetCookieControlType_ManagedPrefOverridesBlockAllCookies) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());

  // Set initial value to block all cookies.
  qorai_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK, GURL());
  qorai_shields::SetCookieControlType(
      map, profile()->GetPrefs(), ControlType::BLOCK, GURL("http://qorai.com"));

  // Set policy to allow cookies.
  profile()->GetTestingPrefService()->SetManagedPref(
      prefs::kManagedDefaultCookiesSetting, base::Value(CONTENT_SETTING_ALLOW));

  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY,
            qorai_shields::GetCookieControlType(map, cookies.get(), GURL()));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY,
            qorai_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://qorai.com")));
}

TEST_F(QoraiShieldsUtilTest,
       GetCookieControlType_ManagedPrefOverridesBlockThirdPartyCookies) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());

  // Set initial value to block third party cookies.
  qorai_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK_THIRD_PARTY, GURL());
  qorai_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK_THIRD_PARTY,
                                      GURL("http://qorai.com"));

  // Set policy to block all cookies.
  profile()->GetTestingPrefService()->SetManagedPref(
      prefs::kManagedDefaultCookiesSetting, base::Value(CONTENT_SETTING_BLOCK));

  EXPECT_EQ(ControlType::BLOCK,
            qorai_shields::GetCookieControlType(map, cookies.get(), GURL()));
  EXPECT_EQ(ControlType::BLOCK,
            qorai_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://qorai.com")));
}

/* FINGERPRINTING CONTROL */
TEST_F(QoraiShieldsUtilTest, SetFingerprintingControlType_Default) {
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeature(
      qorai_shields::features::kQoraiShowStrictFingerprintingMode);

  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  // setting should be default to start with
  auto type = qorai_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::DEFAULT, type);
  type = qorai_shields::GetFingerprintingControlType(map,
                                                     GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::DEFAULT, type);

  /* ALLOW */
  qorai_shields::SetFingerprintingControlType(map, ControlType::ALLOW, GURL());
  type = qorai_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, type);

  // setting should apply to all urls
  type = qorai_shields::GetFingerprintingControlType(map,
                                                     GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, type);

  /* BLOCK */
  qorai_shields::SetFingerprintingControlType(map, ControlType::BLOCK, GURL());
  type = qorai_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, type);

  // setting should apply to all urls
  type = qorai_shields::GetFingerprintingControlType(map,
                                                     GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK, type);

  /* DEFAULT */
  qorai_shields::SetFingerprintingControlType(map, ControlType::DEFAULT,
                                              GURL());
  type = qorai_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::DEFAULT, type);

  // setting should apply to all urls
  type = qorai_shields::GetFingerprintingControlType(map,
                                                     GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::DEFAULT, type);

  /* Global ALLOW and Site explicit DEFAULT */
  qorai_shields::SetFingerprintingControlType(map, ControlType::ALLOW, GURL());
  qorai_shields::SetFingerprintingControlType(map, ControlType::DEFAULT,
                                              GURL("http://qorai.com"));
  // Site should have DEFAULT if it's explicitly set.
  type = qorai_shields::GetFingerprintingControlType(map,
                                                     GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::DEFAULT, type);

  /* Global BLOCK and Site explicit DEFAULT */
  qorai_shields::SetFingerprintingControlType(map, ControlType::BLOCK, GURL());
  // Site should have DEFAULT if it's explicitly set.
  type = qorai_shields::GetFingerprintingControlType(map,
                                                     GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::DEFAULT, type);
}

TEST_F(QoraiShieldsUtilTest, SetFingerprintingControlType_ForOrigin) {
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeature(
      qorai_shields::features::kQoraiShowStrictFingerprintingMode);

  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  qorai_shields::SetFingerprintingControlType(map, ControlType::ALLOW,
                                              GURL("http://qorai.com"));
  auto type = qorai_shields::GetFingerprintingControlType(
      map, GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, type);
  // override should also apply to different scheme
  type = qorai_shields::GetFingerprintingControlType(map,
                                                     GURL("https://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, type);

  qorai_shields::SetFingerprintingControlType(map, ControlType::BLOCK,
                                              GURL("http://qorai.com"));
  type = qorai_shields::GetFingerprintingControlType(map,
                                                     GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK, type);
  // override should also apply to different scheme
  type = qorai_shields::GetFingerprintingControlType(map,
                                                     GURL("https://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK, type);

  // override should not apply to default
  type = qorai_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::DEFAULT, type);
}

TEST_F(QoraiShieldsUtilTest, GetFingerprintingControlType_ManagedPref) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  profile()->GetTestingPrefService()->SetManagedPref(
      kManagedDefaultQoraiFingerprintingV2, base::Value(CONTENT_SETTING_ALLOW));
  EXPECT_EQ(ControlType::ALLOW,
            qorai_shields::GetFingerprintingControlType(map, GURL()));
  EXPECT_EQ(ControlType::ALLOW, qorai_shields::GetFingerprintingControlType(
                                    map, GURL("http://qorai.com")));

  profile()->GetTestingPrefService()->SetManagedPref(
      kManagedDefaultQoraiFingerprintingV2, base::Value(CONTENT_SETTING_ASK));
  EXPECT_EQ(ControlType::DEFAULT,
            qorai_shields::GetFingerprintingControlType(map, GURL()));
  EXPECT_EQ(ControlType::DEFAULT, qorai_shields::GetFingerprintingControlType(
                                      map, GURL("http://qorai.com")));
}

/* NOSCRIPT CONTROL */
TEST_F(QoraiShieldsUtilTest, SetNoScriptControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  // settings should be default
  auto setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                   ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  /* BLOCK */
  qorai_shields::SetNoScriptControlType(map, ControlType::BLOCK, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                   ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  /* ALLOW */
  qorai_shields::SetNoScriptControlType(map, ControlType::ALLOW, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                   ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
}

TEST_F(QoraiShieldsUtilTest, SetNoScriptControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  qorai_shields::SetNoScriptControlType(map, ControlType::BLOCK,
                                        GURL("http://qorai.com"));
  // setting should apply to origin
  auto setting = map->GetContentSetting(GURL("http://qorai.com"), GURL(),
                                        ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // setting should also apply to different scheme
  setting = map->GetContentSetting(GURL("https://qorai.com"), GURL(),
                                   ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // setting should not apply to default
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
}

TEST_F(QoraiShieldsUtilTest, GetNoScriptControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = qorai_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* BLOCK */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, CONTENT_SETTING_BLOCK);
  setting = qorai_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, CONTENT_SETTING_ALLOW);
  setting = qorai_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);
}

TEST_F(QoraiShieldsUtilTest, GetNoScriptControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = qorai_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting =
      qorai_shields::GetNoScriptControlType(map, GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting =
      qorai_shields::GetNoScriptControlType(map, GURL("https://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* BLOCK */
  // set override to block
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://qorai.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::JAVASCRIPT,
      CONTENT_SETTING_BLOCK);
  setting =
      qorai_shields::GetNoScriptControlType(map, GURL("http://qorai.com/*"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  // https in unchanged
  setting =
      qorai_shields::GetNoScriptControlType(map, GURL("https://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  // default is unchanged
  setting = qorai_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* ALLOW */
  // change default to block
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, CONTENT_SETTING_BLOCK);
  setting =
      qorai_shields::GetNoScriptControlType(map, GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting =
      qorai_shields::GetNoScriptControlType(map, GURL("https://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = qorai_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);

  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://qorai.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::JAVASCRIPT,
      CONTENT_SETTING_ALLOW);
  setting =
      qorai_shields::GetNoScriptControlType(map, GURL("http://qorai.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  // https in unchanged
  setting =
      qorai_shields::GetNoScriptControlType(map, GURL("https://qorai.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  // default is unchanged
  setting = qorai_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);
}

// Should not do domain blocking if domain blocking feature is disabled
TEST_F(QoraiShieldsUtilDomainBlockFeatureTest, GetDomainBlockingType) {
  ExpectDomainBlockingType(GURL("https://qorai.com"),
                           DomainBlockingType::kNone);
}

// Should not do domain blocking if Qorai Shields is down
TEST_F(QoraiShieldsUtilTest, GetDomainBlockingType_ShieldsDown) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  GURL url = GURL("https://qorai.com");
  qorai_shields::SetQoraiShieldsEnabled(map, false, url);
  ExpectDomainBlockingType(url, DomainBlockingType::kNone);
}

// Should not do domain blocking on non-HTTP(S) URLs
TEST_F(QoraiShieldsUtilTest, GetDomainBlockingType_IsNotHttpHttps) {
  ExpectDomainBlockingType(GURL("chrome://preferences"),
                           DomainBlockingType::kNone);
  ExpectDomainBlockingType(GURL("about:blank"), DomainBlockingType::kNone);
}

// Should not do domain blocking unless ad blocking is "aggressive"
TEST_F(QoraiShieldsUtilTest, GetDomainBlockingType_ControlTypes) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  const GURL url = GURL("https://qorai.com");

  const struct TestCase {
    ControlType ad_control_type;
    ControlType cosmetic_filtering_control_type;
    DomainBlockingType expected_blocking_type;
  } kTestCases[] = {
      {ControlType::ALLOW, ControlType::ALLOW, DomainBlockingType::kNone},
      {ControlType::ALLOW, ControlType::BLOCK_THIRD_PARTY,
       DomainBlockingType::kNone},
      {ControlType::ALLOW, ControlType::BLOCK, DomainBlockingType::kNone},
      {ControlType::BLOCK, ControlType::ALLOW, DomainBlockingType::kNone},
      {ControlType::BLOCK, ControlType::BLOCK_THIRD_PARTY,
       DomainBlockingType::k1PES},
      {ControlType::BLOCK, ControlType::BLOCK, DomainBlockingType::kAggressive},
  };

  for (const auto& test_case : kTestCases) {
    SCOPED_TRACE(testing::Message()
                 << static_cast<int>(test_case.ad_control_type)
                 << static_cast<int>(test_case.cosmetic_filtering_control_type)
                 << static_cast<int>(test_case.expected_blocking_type));
    qorai_shields::SetAdControlType(map, test_case.ad_control_type, url);
    qorai_shields::SetCosmeticFilteringControlType(
        map, test_case.cosmetic_filtering_control_type, url);
    ExpectDomainBlockingType(url, test_case.expected_blocking_type);
  }
}

// Should do 1PES domain blocking if domain blocking feature is enabled.
TEST_F(QoraiShieldsUtilTest, GetDomainBlockingType) {
  ExpectDomainBlockingType(GURL("https://qorai.com"),
                           DomainBlockingType::k1PES);
}
