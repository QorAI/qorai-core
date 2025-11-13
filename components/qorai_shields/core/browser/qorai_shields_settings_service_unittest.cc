// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_shields/core/browser/qorai_shields_settings_service.h"

#include "base/test/scoped_feature_list.h"
#include "base/test/task_environment.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_p3a.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

using qorai_shields::mojom::AdBlockMode;
using qorai_shields::mojom::AutoShredMode;
using qorai_shields::mojom::FingerprintMode;

class QoraiShieldsSettingsServiceTest : public testing::Test {
 public:
  QoraiShieldsSettingsServiceTest() {}
  ~QoraiShieldsSettingsServiceTest() override = default;

  void SetUp() override {
    HostContentSettingsMap::RegisterProfilePrefs(profile_prefs_.registry());
    qorai_shields::RegisterShieldsP3AProfilePrefs(profile_prefs_.registry());
    qorai_shields::RegisterShieldsP3ALocalPrefs(local_state_.registry());
    host_content_settings_map_ = new HostContentSettingsMap(
        &profile_prefs_, false /* is_off_the_record */,
        false /* store_last_modified */, false /* restore_session */,
        false /* should_record_metrics */);
    qorai_shields_settings_ =
        std::make_unique<qorai_shields::QoraiShieldsSettingsService>(
            *GetHostContentSettingsMap(), GetLocalState(), &profile_prefs_);
  }

  void TearDown() override { host_content_settings_map_->ShutdownOnUIThread(); }

  TestingPrefServiceSimple* GetLocalState() { return &local_state_; }
  HostContentSettingsMap* GetHostContentSettingsMap() {
    return host_content_settings_map_.get();
  }

  const GURL kTestUrl{"https://qorai.com"};

  qorai_shields::QoraiShieldsSettingsService* qorai_shields_settings() {
    return qorai_shields_settings_.get();
  }

  base::Value AutoShredDictFrom(AutoShredMode mode) {
    base::Value dict(base::Value::Type::DICT);
    dict.GetDict().Set(qorai_shields::AutoShredSetting::kName,
                       static_cast<int>(mode));
    return dict;
  }

 private:
  base::test::TaskEnvironment task_environment_;
  TestingPrefServiceSimple local_state_;
  sync_preferences::TestingPrefServiceSyncable profile_prefs_;
  scoped_refptr<HostContentSettingsMap> host_content_settings_map_;
  std::unique_ptr<qorai_shields::QoraiShieldsSettingsService>
      qorai_shields_settings_;
};

TEST_F(QoraiShieldsSettingsServiceTest, QoraiShieldsEnabled) {
  // verify the initial values
  EXPECT_TRUE(qorai_shields_settings()->GetQoraiShieldsEnabled(kTestUrl));
  EXPECT_TRUE(qorai_shields::GetQoraiShieldsEnabled(GetHostContentSettingsMap(),
                                                    kTestUrl));

  qorai_shields_settings()->SetQoraiShieldsEnabled(false, kTestUrl);
  EXPECT_FALSE(qorai_shields_settings()->GetQoraiShieldsEnabled(kTestUrl));
  // verify underlying value GetQoraiShieldsEnabled is updated
  EXPECT_FALSE(qorai_shields::GetQoraiShieldsEnabled(
      GetHostContentSettingsMap(), kTestUrl));

  // verify other urls unchanged
  EXPECT_TRUE(qorai_shields_settings()->GetQoraiShieldsEnabled(
      GURL("https://example.com")));
  EXPECT_TRUE(qorai_shields::GetQoraiShieldsEnabled(
      GetHostContentSettingsMap(), GURL("https://example.com")));
}

TEST_F(QoraiShieldsSettingsServiceTest, AdBlockMode) {
  // verify the initial values
  EXPECT_EQ(qorai_shields_settings()->GetAdBlockMode(kTestUrl),
            AdBlockMode::STANDARD);
  EXPECT_EQ(
      qorai_shields::GetAdControlType(GetHostContentSettingsMap(), kTestUrl),
      qorai_shields::ControlType::BLOCK);
  EXPECT_EQ(qorai_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), kTestUrl),
            qorai_shields::ControlType::BLOCK_THIRD_PARTY);

  qorai_shields_settings()->SetAdBlockMode(AdBlockMode::AGGRESSIVE, kTestUrl);
  EXPECT_EQ(qorai_shields_settings()->GetAdBlockMode(kTestUrl),
            AdBlockMode::AGGRESSIVE);
  // verify underlying AdControlType & CosmeticFilteringControlType is updated
  EXPECT_EQ(
      qorai_shields::GetAdControlType(GetHostContentSettingsMap(), kTestUrl),
      qorai_shields::ControlType::BLOCK);
  EXPECT_EQ(qorai_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), kTestUrl),
            qorai_shields::ControlType::BLOCK);

  qorai_shields_settings()->SetAdBlockMode(AdBlockMode::ALLOW, kTestUrl);
  EXPECT_EQ(qorai_shields_settings()->GetAdBlockMode(kTestUrl),
            AdBlockMode::ALLOW);
  // verify underlying AdControlType & CosmeticFilteringControlType is updated
  EXPECT_EQ(
      qorai_shields::GetAdControlType(GetHostContentSettingsMap(), kTestUrl),
      qorai_shields::ControlType::ALLOW);
  EXPECT_EQ(qorai_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), kTestUrl),
            qorai_shields::ControlType::ALLOW);

  // verify other urls remain unchanged
  EXPECT_EQ(
      qorai_shields_settings()->GetAdBlockMode(GURL("https://example.com")),
      AdBlockMode::STANDARD);
}

TEST_F(QoraiShieldsSettingsServiceTest, DefaultAdBlockMode) {
  // explicitly set so we can verify this is unchanged by updating default
  qorai_shields_settings()->SetAdBlockMode(AdBlockMode::STANDARD, kTestUrl);

  // verify the initial default values
  EXPECT_EQ(qorai_shields_settings()->GetDefaultAdBlockMode(),
            AdBlockMode::STANDARD);
  EXPECT_EQ(
      qorai_shields::GetAdControlType(GetHostContentSettingsMap(), GURL()),
      qorai_shields::ControlType::BLOCK);
  EXPECT_EQ(qorai_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), GURL()),
            qorai_shields::ControlType::BLOCK_THIRD_PARTY);

  qorai_shields_settings()->SetDefaultAdBlockMode(AdBlockMode::AGGRESSIVE);
  EXPECT_EQ(qorai_shields_settings()->GetDefaultAdBlockMode(),
            AdBlockMode::AGGRESSIVE);
  // verify underlying AdControlType & CosmeticFilteringControlType is updated
  EXPECT_EQ(
      qorai_shields::GetAdControlType(GetHostContentSettingsMap(), GURL()),
      qorai_shields::ControlType::BLOCK);
  EXPECT_EQ(qorai_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), GURL()),
            qorai_shields::ControlType::BLOCK);
  // verify defaults apply to all
  EXPECT_EQ(
      qorai_shields_settings()->GetAdBlockMode(GURL("https://example.com")),
      AdBlockMode::AGGRESSIVE);
  // verify underlying AdControlType & CosmeticFilteringControlType is updated
  EXPECT_EQ(qorai_shields::GetAdControlType(GetHostContentSettingsMap(),
                                            GURL("https://example.com")),
            qorai_shields::ControlType::BLOCK);
  EXPECT_EQ(qorai_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), GURL("https://example.com")),
            qorai_shields::ControlType::BLOCK);

  // verify explict set adblock mode is unchanged
  EXPECT_EQ(qorai_shields_settings()->GetAdBlockMode(kTestUrl),
            AdBlockMode::STANDARD);
  // verify underlying AdControlType & CosmeticFilteringControlType is unchanged
  EXPECT_EQ(
      qorai_shields::GetAdControlType(GetHostContentSettingsMap(), kTestUrl),
      qorai_shields::ControlType::BLOCK);
  EXPECT_EQ(qorai_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), kTestUrl),
            qorai_shields::ControlType::BLOCK_THIRD_PARTY);
}

TEST_F(QoraiShieldsSettingsServiceTest, FingerprintMode) {
  // verify the initial values
  EXPECT_EQ(qorai_shields_settings()->GetFingerprintMode(kTestUrl),
            FingerprintMode::STANDARD_MODE);
  EXPECT_EQ(qorai_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), kTestUrl),
            qorai_shields::ControlType::DEFAULT);

  qorai_shields_settings()->SetFingerprintMode(FingerprintMode::ALLOW_MODE,
                                               kTestUrl);
  EXPECT_EQ(qorai_shields_settings()->GetFingerprintMode(kTestUrl),
            FingerprintMode::ALLOW_MODE);
  // verify underlying FingerprintingControlType is updated
  EXPECT_EQ(qorai_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), kTestUrl),
            qorai_shields::ControlType::ALLOW);

  // iOS does not support FingerprintMode::STRICT_MODE
#if !BUILDFLAG(IS_IOS)
  // when kQoraiShowStrictFingerprintingMode flag is disabled
  qorai_shields_settings()->SetFingerprintMode(FingerprintMode::STRICT_MODE,
                                               kTestUrl);
  // verify it returns FingerprintMode::STANDARD_MODE
  EXPECT_EQ(qorai_shields_settings()->GetFingerprintMode(kTestUrl),
            FingerprintMode::STANDARD_MODE);
  // verify underlying FingerprintingControlType is updated
  EXPECT_EQ(qorai_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), kTestUrl),
            qorai_shields::ControlType::DEFAULT);

  // enable kQoraiShowStrictFingerprintingMode flag
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeature(
      qorai_shields::features::kQoraiShowStrictFingerprintingMode);
  qorai_shields_settings()->SetFingerprintMode(FingerprintMode::STRICT_MODE,
                                               kTestUrl);
  // verify it returns FingerprintMode::STRICT_MODE
  EXPECT_EQ(qorai_shields_settings()->GetFingerprintMode(kTestUrl),
            FingerprintMode::STRICT_MODE);
  // verify underlying FingerprintingControlType is updated
  EXPECT_EQ(qorai_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), kTestUrl),
            qorai_shields::ControlType::BLOCK);
#endif

  // verify other urls remain unchanged
  EXPECT_EQ(
      qorai_shields_settings()->GetFingerprintMode(GURL("https://example.com")),
      FingerprintMode::STANDARD_MODE);
  // verify underlying FingerprintingControlType is unchanged
  EXPECT_EQ(qorai_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), GURL("https://example.com")),
            qorai_shields::ControlType::DEFAULT);
}

TEST_F(QoraiShieldsSettingsServiceTest, DefaultFingerprintMode) {
  // explicitly set so we can verify this is unchanged by updating default
  qorai_shields_settings()->SetFingerprintMode(FingerprintMode::STANDARD_MODE,
                                               kTestUrl);

  // verify the initial default values
  EXPECT_EQ(qorai_shields_settings()->GetDefaultFingerprintMode(),
            FingerprintMode::STANDARD_MODE);
  EXPECT_EQ(qorai_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), GURL()),
            qorai_shields::ControlType::DEFAULT);

  qorai_shields_settings()->SetDefaultFingerprintMode(
      FingerprintMode::ALLOW_MODE);
  EXPECT_EQ(qorai_shields_settings()->GetDefaultFingerprintMode(),
            FingerprintMode::ALLOW_MODE);
  // verify underlying FingerprintingControlType is updated
  EXPECT_EQ(qorai_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), GURL()),
            qorai_shields::ControlType::ALLOW);

  EXPECT_EQ(
      qorai_shields_settings()->GetFingerprintMode(GURL("https://example.com")),
      FingerprintMode::ALLOW_MODE);

  // verify explict set fingerprint mode is unchanged
  EXPECT_EQ(qorai_shields_settings()->GetFingerprintMode(kTestUrl),
            FingerprintMode::STANDARD_MODE);
  // verify underlying FingerprintingControlType is unchanged
  EXPECT_EQ(qorai_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), kTestUrl),
            qorai_shields::ControlType::DEFAULT);
}

TEST_F(QoraiShieldsSettingsServiceTest, NoScriptsEnabled) {
  // verify the initial values
  EXPECT_FALSE(qorai_shields_settings()->IsNoScriptEnabled(kTestUrl));
  EXPECT_EQ(qorai_shields::GetNoScriptControlType(GetHostContentSettingsMap(),
                                                  kTestUrl),
            qorai_shields::ControlType::ALLOW);

  qorai_shields_settings()->SetNoScriptEnabled(true, kTestUrl);
  EXPECT_TRUE(qorai_shields_settings()->IsNoScriptEnabled(kTestUrl));
  // verify underlying NoScriptControlType is updated
  EXPECT_EQ(qorai_shields::GetNoScriptControlType(GetHostContentSettingsMap(),
                                                  kTestUrl),
            qorai_shields::ControlType::BLOCK);

  // verify other urls remain unchanged
  EXPECT_FALSE(
      qorai_shields_settings()->IsNoScriptEnabled(GURL("https://example.com")));
  // verify underlying NoScriptControlType is unchanged
  EXPECT_EQ(qorai_shields::GetNoScriptControlType(GetHostContentSettingsMap(),
                                                  GURL("https://example.com")),
            qorai_shields::ControlType::ALLOW);
}

TEST_F(QoraiShieldsSettingsServiceTest, NoScriptsEnabledByDefault) {
  // explicitly set so we can verify this is unchanged by updating default
  qorai_shields_settings()->SetNoScriptEnabled(false, kTestUrl);

  // verify the initial default values
  EXPECT_FALSE(qorai_shields_settings()->IsNoScriptEnabledByDefault());
  EXPECT_EQ(qorai_shields::GetNoScriptControlType(GetHostContentSettingsMap(),
                                                  GURL()),
            qorai_shields::ControlType::ALLOW);

  qorai_shields_settings()->SetNoScriptEnabledByDefault(true);
  EXPECT_TRUE(qorai_shields_settings()->IsNoScriptEnabledByDefault());
  EXPECT_TRUE(
      qorai_shields_settings()->IsNoScriptEnabled(GURL("https://example.com")));
  // verify underlying NoScriptControlType is updated
  EXPECT_EQ(qorai_shields::GetNoScriptControlType(GetHostContentSettingsMap(),
                                                  GURL()),
            qorai_shields::ControlType::BLOCK);

  // verify explict set no script enabled setting is unchanged
  EXPECT_FALSE(qorai_shields_settings()->IsNoScriptEnabled(kTestUrl));
  // verify underlying NoScriptControlType is unchanged
  EXPECT_EQ(qorai_shields::GetNoScriptControlType(GetHostContentSettingsMap(),
                                                  kTestUrl),
            qorai_shields::ControlType::ALLOW);
}

TEST_F(QoraiShieldsSettingsServiceTest, AutoShredMode) {
  // verify the initial values
  EXPECT_EQ(qorai_shields_settings()->GetAutoShredMode(kTestUrl),
            AutoShredMode::NEVER);
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                kTestUrl, GURL(),
                qorai_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::NEVER));

  qorai_shields_settings()->SetAutoShredMode(AutoShredMode::LAST_TAB_CLOSED,
                                             kTestUrl);
  EXPECT_EQ(qorai_shields_settings()->GetAutoShredMode(kTestUrl),
            AutoShredMode::LAST_TAB_CLOSED);
  // verify underlying AutoShredMode is updated
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                kTestUrl, GURL(),
                qorai_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::LAST_TAB_CLOSED));

  qorai_shields_settings()->SetAutoShredMode(AutoShredMode::APP_EXIT, kTestUrl);
  EXPECT_EQ(qorai_shields_settings()->GetAutoShredMode(kTestUrl),
            AutoShredMode::APP_EXIT);
  // verify underlying AutoShredMode is updated
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                kTestUrl, GURL(),
                qorai_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::APP_EXIT));

  // verify other urls remain unchanged
  EXPECT_EQ(
      qorai_shields_settings()->GetAutoShredMode(GURL("https://example.com")),
      AutoShredMode::NEVER);
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                GURL("https://example.com"), GURL(),
                qorai_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::NEVER));
}

TEST_F(QoraiShieldsSettingsServiceTest, DefaultAutoShredMode) {
  // explicitly set so we can verify this is unchanged by updating default
  qorai_shields_settings()->SetAutoShredMode(AutoShredMode::NEVER, kTestUrl);

  // verify the initial default values
  EXPECT_EQ(qorai_shields_settings()->GetDefaultAutoShredMode(),
            AutoShredMode::NEVER);
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                GURL(), GURL(),
                qorai_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::NEVER));

  qorai_shields_settings()->SetDefaultAutoShredMode(
      AutoShredMode::LAST_TAB_CLOSED);
  EXPECT_EQ(qorai_shields_settings()->GetDefaultAutoShredMode(),
            AutoShredMode::LAST_TAB_CLOSED);
  EXPECT_EQ(
      qorai_shields_settings()->GetAutoShredMode(GURL("https://example.com")),
      AutoShredMode::LAST_TAB_CLOSED);
  // verify underlying AutoShredMode is updated
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                GURL(), GURL(),
                qorai_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::LAST_TAB_CLOSED));

  // verify explict set auto shred mode unchanged
  EXPECT_EQ(qorai_shields_settings()->GetAutoShredMode(kTestUrl),
            AutoShredMode::NEVER);
  // verify underlying AutoShredMode is unchanged
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                kTestUrl, GURL(),
                qorai_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::NEVER));
}

#if !BUILDFLAG(IS_IOS)
TEST_F(QoraiShieldsSettingsServiceTest, DefaultForgetFirstPartyStorage) {
  // verify the initial values
  EXPECT_EQ(qorai_shields_settings()->GetForgetFirstPartyStorageEnabled(GURL()),
            false);
  EXPECT_EQ(
      qorai_shields_settings()->GetForgetFirstPartyStorageEnabled(kTestUrl),
      false);
}

TEST_F(QoraiShieldsSettingsServiceTest, DefaultForgetFirstPartyStorageEnabled) {
  // verify the initial default values
  EXPECT_EQ(qorai_shields_settings()->GetForgetFirstPartyStorageEnabled(GURL()),
            false);
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                GURL(), GURL(), ContentSettingsType::QORAI_REMEMBER_1P_STORAGE),
            CONTENT_SETTING_ALLOW);
}

TEST_F(QoraiShieldsSettingsServiceTest,
       SetForgetFirstPartyStorageEnabledUsesETLD) {
  const GURL test_url("https://qorai.com");
  const GURL test_subdomain_url("https://www.qorai.com");

  EXPECT_EQ(
      GetHostContentSettingsMap()->GetWebsiteSetting(
          test_url, GURL(), ContentSettingsType::QORAI_REMEMBER_1P_STORAGE),
      CONTENT_SETTING_ALLOW);
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                test_subdomain_url, GURL(),
                ContentSettingsType::QORAI_REMEMBER_1P_STORAGE),
            CONTENT_SETTING_ALLOW);

  qorai_shields_settings()->SetForgetFirstPartyStorageEnabled(
      true, test_subdomain_url);

  EXPECT_EQ(
      GetHostContentSettingsMap()->GetWebsiteSetting(
          test_url, GURL(), ContentSettingsType::QORAI_REMEMBER_1P_STORAGE),
      CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                test_subdomain_url, GURL(),
                ContentSettingsType::QORAI_REMEMBER_1P_STORAGE),
            CONTENT_SETTING_BLOCK);
}
#endif
