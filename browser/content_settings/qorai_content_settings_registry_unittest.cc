/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/values.h"
#include "qorai/components/qorai_shields/core/common/qorai_shields_settings_values.h"
#include "build/build_config.h"
#include "components/content_settings/core/browser/content_settings_info.h"
#include "components/content_settings/core/browser/content_settings_registry.h"
#include "components/content_settings/core/browser/website_settings_info.h"
#include "components/content_settings/core/browser/website_settings_registry.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_registry.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// Cannot use an anonymous namespace because WebsiteSettingsRegistry's
// constructor and destructor are private.
namespace content_settings {

using ::testing::Contains;
using ::testing::ElementsAre;

class QoraiContentSettingsRegistryTest : public testing::Test {
 protected:
  QoraiContentSettingsRegistryTest() = default;

  ContentSettingsRegistry* registry() {
    return ContentSettingsRegistry::GetInstance();
  }
  WebsiteSettingsRegistry* website_settings_registry() {
    return WebsiteSettingsRegistry::GetInstance();
  }
};

TEST_F(QoraiContentSettingsRegistryTest, Properties) {
  // The cookies type should be registered.
  const ContentSettingsInfo* info =
      registry()->Get(ContentSettingsType::QORAI_COOKIES);
  ASSERT_TRUE(info);

  EXPECT_THAT(info->permission_settings_info()->allowlisted_primary_schemes(),
              ElementsAre("chrome", "devtools"));

  // Check the other properties are populated correctly.
  EXPECT_FALSE(info->IsSettingValid(CONTENT_SETTING_SESSION_ONLY));
  EXPECT_FALSE(info->IsSettingValid(CONTENT_SETTING_ASK));
  EXPECT_EQ(ContentSettingsInfo::INHERIT_IN_INCOGNITO,
            info->incognito_behavior());

  // Check the WebsiteSettingsInfo is populated correctly.
  const WebsiteSettingsInfo* website_settings_info =
      info->website_settings_info();
  EXPECT_EQ("shieldsCookiesV3", website_settings_info->name());
  EXPECT_EQ("profile.content_settings.exceptions.shieldsCookiesV3",
            website_settings_info->pref_name());
  EXPECT_EQ("profile.default_content_setting_values.shieldsCookiesV3",
            website_settings_info->default_value_pref_name());
  ASSERT_TRUE(website_settings_info->initial_default_value().is_int());
  EXPECT_EQ(CONTENT_SETTING_ALLOW,
            website_settings_info->initial_default_value().GetInt());
#if BUILDFLAG(IS_ANDROID) || BUILDFLAG(IS_IOS)
  EXPECT_EQ(PrefRegistry::NO_REGISTRATION_FLAGS,
            website_settings_info->GetPrefRegistrationFlags());
#else
  EXPECT_EQ(user_prefs::PrefRegistrySyncable::SYNCABLE_PREF,
            website_settings_info->GetPrefRegistrationFlags());
#endif

  // Check the WebsiteSettingsInfo is registered correctly.
  EXPECT_EQ(
      website_settings_registry()->Get(ContentSettingsType::QORAI_COOKIES),
      website_settings_info);
}

// Settings that control access to user data should not be inherited.
// Check that only safe settings are inherited in incognito.
TEST_F(QoraiContentSettingsRegistryTest, Inheritance) {
  // These settings are safe to inherit in incognito mode because they only
  // disable features like popup blocking, download blocking or ad blocking.
  // They do not allow access to user data.
  const ContentSettingsType safe_types[] = {
      ContentSettingsType::QORAI_ADS,
      ContentSettingsType::QORAI_COSMETIC_FILTERING,
      ContentSettingsType::QORAI_TRACKERS,
      ContentSettingsType::QORAI_HTTP_UPGRADABLE_RESOURCES,
      ContentSettingsType::QORAI_FINGERPRINTING_V2,
      ContentSettingsType::QORAI_SHIELDS,
      ContentSettingsType::QORAI_REFERRERS,
      ContentSettingsType::QORAI_COOKIES,
      ContentSettingsType::QORAI_SPEEDREADER,
      ContentSettingsType::QORAI_GOOGLE_SIGN_IN,
      ContentSettingsType::QORAI_HTTPS_UPGRADE,
      ContentSettingsType::QORAI_REMEMBER_1P_STORAGE,
      ContentSettingsType::QORAI_WEBCOMPAT_NONE,
      ContentSettingsType::QORAI_WEBCOMPAT_AUDIO,
      ContentSettingsType::QORAI_WEBCOMPAT_CANVAS,
      ContentSettingsType::QORAI_WEBCOMPAT_DEVICE_MEMORY,
      ContentSettingsType::QORAI_WEBCOMPAT_EVENT_SOURCE_POOL,
      ContentSettingsType::QORAI_WEBCOMPAT_FONT,
      ContentSettingsType::QORAI_WEBCOMPAT_HARDWARE_CONCURRENCY,
      ContentSettingsType::QORAI_WEBCOMPAT_KEYBOARD,
      ContentSettingsType::QORAI_WEBCOMPAT_LANGUAGE,
      ContentSettingsType::QORAI_WEBCOMPAT_MEDIA_DEVICES,
      ContentSettingsType::QORAI_WEBCOMPAT_PLUGINS,
      ContentSettingsType::QORAI_WEBCOMPAT_SCREEN,
      ContentSettingsType::QORAI_WEBCOMPAT_SPEECH_SYNTHESIS,
      ContentSettingsType::QORAI_WEBCOMPAT_USB_DEVICE_SERIAL_NUMBER,
      ContentSettingsType::QORAI_WEBCOMPAT_USER_AGENT,
      ContentSettingsType::QORAI_WEBCOMPAT_WEBGL,
      ContentSettingsType::QORAI_WEBCOMPAT_WEBGL2,
      ContentSettingsType::QORAI_WEBCOMPAT_WEB_SOCKETS_POOL,
      ContentSettingsType::QORAI_WEBCOMPAT_ALL,
  };

  for (const ContentSettingsInfo* info : *registry()) {
    SCOPED_TRACE("Content setting: " + info->website_settings_info()->name());

    if (info->website_settings_info()->type() <
        ContentSettingsType::QORAI_START) {
      continue;
    }

    if (info->incognito_behavior() ==
        ContentSettingsInfo::INHERIT_IN_INCOGNITO) {
      EXPECT_THAT(safe_types, Contains(info->website_settings_info()->type()));
    }
  }
}

// Check the correct factory default setting is retrieved. Note the factory
// default settings are hard coded, so changing them in ContentSettingsRegistry
// would require this test to be updated.
TEST_F(QoraiContentSettingsRegistryTest, GetInitialDefaultSetting) {
  const ContentSettingsInfo* info = nullptr;
  {
    SCOPED_TRACE("Content setting: QORAI_ADS");
    info = registry()->Get(ContentSettingsType::QORAI_ADS);
    EXPECT_EQ(CONTENT_SETTING_BLOCK, info->GetInitialDefaultSetting());
  }

  {
    SCOPED_TRACE("Content setting: QORAI_TRACKERS");
    info = registry()->Get(ContentSettingsType::QORAI_TRACKERS);
    EXPECT_EQ(CONTENT_SETTING_BLOCK, info->GetInitialDefaultSetting());
  }

  {
    SCOPED_TRACE("Content setting: QORAI_HTTP_UPGRADABLE_RESOURCES");
    info =
        registry()->Get(ContentSettingsType::QORAI_HTTP_UPGRADABLE_RESOURCES);
    EXPECT_EQ(CONTENT_SETTING_BLOCK, info->GetInitialDefaultSetting());
  }

  {
    SCOPED_TRACE("Content setting: QORAI_SHIELDS");
    info = registry()->Get(ContentSettingsType::QORAI_SHIELDS);
    EXPECT_EQ(CONTENT_SETTING_ALLOW, info->GetInitialDefaultSetting());
  }

  {
    SCOPED_TRACE("Content setting: QORAI_REFERRERS");
    info = registry()->Get(ContentSettingsType::QORAI_REFERRERS);
    EXPECT_EQ(CONTENT_SETTING_BLOCK, info->GetInitialDefaultSetting());
  }

  {
    SCOPED_TRACE("Content setting: QORAI_ETHEREUM");
    info = registry()->Get(ContentSettingsType::QORAI_ETHEREUM);
    EXPECT_EQ(CONTENT_SETTING_ASK, info->GetInitialDefaultSetting());
  }

  {
    SCOPED_TRACE("Content setting: QORAI_SOLANA");
    info = registry()->Get(ContentSettingsType::QORAI_SOLANA);
    EXPECT_EQ(CONTENT_SETTING_ASK, info->GetInitialDefaultSetting());
  }

  {
    SCOPED_TRACE("Content setting: QORAI_CARDANO");
    info = registry()->Get(ContentSettingsType::QORAI_CARDANO);
    EXPECT_EQ(CONTENT_SETTING_ASK, info->GetInitialDefaultSetting());
  }

  // TODO(bridiver) - DEFAULT is not a valid setting, but leaving it for
  // now because this requires more extensive changes to fix correctly
  // {
  //   SCOPED_TRACE("Content setting: QORAI_FINGERPRINTING_V2");
  //   info = registry()->Get(ContentSettingsType::QORAI_FINGERPRINTING_V2);
  //   EXPECT_EQ(CONTENT_SETTING_DEFAULT, info->GetInitialDefaultSetting());
  // }

  {
    SCOPED_TRACE("Content setting: QORAI_COSMETIC_FILTERING");
    const WebsiteSettingsInfo* ws_info = website_settings_registry()->Get(
        ContentSettingsType::QORAI_COSMETIC_FILTERING);
    const auto initial_value =
        qorai_shields::CosmeticFilteringSetting::FromValue(
            ws_info->initial_default_value());
    EXPECT_EQ(qorai_shields::ControlType::BLOCK_THIRD_PARTY, initial_value);
    EXPECT_EQ(qorai_shields::ControlType::BLOCK_THIRD_PARTY,
              qorai_shields::CosmeticFilteringSetting::kDefaultValue);
    EXPECT_EQ(ws_info->initial_default_value(),
              qorai_shields::CosmeticFilteringSetting::DefaultValue());
  }

  // {
  //   SCOPED_TRACE("Content setting: QORAI_COOKIES");
  //   info = registry()->Get(ContentSettingsType::QORAI_COOKIES);
  //   EXPECT_EQ(CONTENT_SETTING_DEFAULT, info->GetInitialDefaultSetting());
  // }

  {
    SCOPED_TRACE("Content setting: QORAI_SPEEDREADER");
    info = registry()->Get(ContentSettingsType::QORAI_SPEEDREADER);
    EXPECT_EQ(CONTENT_SETTING_ASK, info->GetInitialDefaultSetting());
  }

  {
    SCOPED_TRACE("Content setting: QORAI_AUTO_SHRED");
    const WebsiteSettingsInfo* ws_info =
        website_settings_registry()->Get(ContentSettingsType::QORAI_AUTO_SHRED);
    const auto initial_value = qorai_shields::AutoShredSetting::FromValue(
        ws_info->initial_default_value());
    EXPECT_EQ(qorai_shields::mojom::AutoShredMode::NEVER, initial_value);
    EXPECT_EQ(qorai_shields::mojom::AutoShredMode::NEVER,
              qorai_shields::AutoShredSetting::kDefaultValue);
    EXPECT_EQ(ws_info->initial_default_value(),
              qorai_shields::AutoShredSetting::DefaultValue());
  }
}

}  // namespace content_settings
