/* Copyright (c) 2024 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <memory>
#include <string_view>

#include "base/feature_list.h"
#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_component_updater/browser/local_data_files_service.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "qorai/components/qorai_shields/core/common/qorai_shield_constants.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/constants/qorai_paths.h"
#include "qorai/components/webcompat/content/browser/webcompat_exceptions_service.h"
#include "qorai/components/webcompat/core/common/features.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/test/base/chrome_test_utils.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile_manager.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "content/public/test/browser_task_environment.h"
#include "content/public/test/test_utils.h"
#include "url/origin.h"

using qorai_shields::ControlType;
using content_settings::mojom::ContentSettingsType;
using enum ContentSettingsType;
using qorai_component_updater::LocalDataFilesService;
using qorai_component_updater::LocalDataFilesServiceFactory;

namespace {

struct TestCase {
  const char* name;
  const ContentSettingsType type;
};

constexpr TestCase kTestCases[] = {
    {"all-fingerprinting", QORAI_FINGERPRINTING_V2},
    {"audio", QORAI_WEBCOMPAT_AUDIO},
    {"canvas", QORAI_WEBCOMPAT_CANVAS},
    {"device-memory", QORAI_WEBCOMPAT_DEVICE_MEMORY},
    {"eventsource-pool", QORAI_WEBCOMPAT_EVENT_SOURCE_POOL},
    {"font", QORAI_WEBCOMPAT_FONT},
    {"hardware-concurrency", QORAI_WEBCOMPAT_HARDWARE_CONCURRENCY},
    {"keyboard", QORAI_WEBCOMPAT_KEYBOARD},
    {"language", QORAI_WEBCOMPAT_LANGUAGE},
    {"media-devices", QORAI_WEBCOMPAT_MEDIA_DEVICES},
    {"plugins", QORAI_WEBCOMPAT_PLUGINS},
    {"referrer", QORAI_REFERRERS},
    {"screen", QORAI_WEBCOMPAT_SCREEN},
    {"speech-synthesis", QORAI_WEBCOMPAT_SPEECH_SYNTHESIS},
    {"usb-device-serial-number", QORAI_WEBCOMPAT_USB_DEVICE_SERIAL_NUMBER},
    {"user-agent", QORAI_WEBCOMPAT_USER_AGENT},
    {"webgl", QORAI_WEBCOMPAT_WEBGL},
    {"webgl2", QORAI_WEBCOMPAT_WEBGL2},
    {"websockets-pool", QORAI_WEBCOMPAT_WEB_SOCKETS_POOL},
};

}  // namespace

class WebcompatExceptionsTest : public testing::Test {
 public:
  WebcompatExceptionsTest()
      : testing_profile_manager_(TestingBrowserProcess::GetGlobal()) {
    feature_list_.InitAndEnableFeature(
        webcompat::features::kQorAIWebcompatExceptionsService);
  }

  void SetUp() override {
    ASSERT_TRUE(testing_profile_manager_.SetUp());
    profile_ = testing_profile_manager()->CreateTestingProfile("profile");
    testing::Test::SetUp();
  }

  TestingProfileManager* testing_profile_manager() {
    return &testing_profile_manager_;
  }

  TestingProfile* profile() { return profile_.get(); }

 private:
  content::BrowserTaskEnvironment task_environment_;
  TestingProfileManager testing_profile_manager_;
  raw_ptr<TestingProfile> profile_;
  base::test::ScopedFeatureList feature_list_;
};

TEST_F(WebcompatExceptionsTest, RemoteSettingsTest) {
  HostContentSettingsMap* map =
      HostContentSettingsMapFactory::GetForProfile(profile());

  std::unique_ptr<LocalDataFilesService> dummy_local_data_files_service =
      LocalDataFilesServiceFactory(nullptr);

  auto* webcompat_exceptions_service =
      webcompat::WebcompatExceptionsService::CreateInstance(
          dummy_local_data_files_service.get());

  for (const auto& test_case : kTestCases) {
    // Check the default setting
    const auto observed_setting_default =
        map->GetContentSetting(GURL("https://a.test"), GURL(), test_case.type);
    EXPECT_NE(observed_setting_default, CONTENT_SETTING_ALLOW);

    // Create a rule
    const std::string json_string = std::string(R"([{
      "include": [
        "*://a.test/*"
      ],
      "exceptions": [
        ")") + test_case.name + std::string(R"("
      ],
      "issue": "test"
    }])");
    webcompat_exceptions_service->SetRulesForTesting(json_string);

    // Check the remote setting gets used
    const auto observed_setting_remote =
        map->GetContentSetting(GURL("https://a.test"), GURL(), test_case.type);
    EXPECT_EQ(observed_setting_remote, CONTENT_SETTING_ALLOW);

    // Check that the remote setting doesn't leak to another domain
    const auto observed_setting_cross_site =
        map->GetContentSetting(GURL("https://b.test"), GURL(), test_case.type);
    EXPECT_NE(observed_setting_cross_site, CONTENT_SETTING_ALLOW);

    // Check that manual setting can override the remote setting
    qorai_shields::SetWebcompatEnabled(map, test_case.type, false,
                                       GURL("https://a.test"), nullptr);
    const auto observed_setting_override1 =
        map->GetContentSetting(GURL("https://a.test"), GURL(), test_case.type);
    EXPECT_EQ(observed_setting_override1, CONTENT_SETTING_BLOCK);

    // Check that manual setting can override the remote setting
    qorai_shields::SetWebcompatEnabled(map, test_case.type, true,
                                       GURL("https://b.test"), nullptr);
    const auto observed_setting_override2 =
        map->GetContentSetting(GURL("https://b.test"), GURL(), test_case.type);
    EXPECT_EQ(observed_setting_override2, CONTENT_SETTING_ALLOW);

    // Check that webcompat returns false for non-http URLs.
    bool result = qorai_shields::IsWebcompatEnabled(map, test_case.type,
                                                    GURL("file://tmp"));
    EXPECT_FALSE(result);

    // Check that the webcompat setting has been enabled as expected.
    bool result2 = qorai_shields::IsWebcompatEnabled(map, test_case.type,
                                                     GURL("https://b.test"));
    EXPECT_TRUE(result2);
  }
}
