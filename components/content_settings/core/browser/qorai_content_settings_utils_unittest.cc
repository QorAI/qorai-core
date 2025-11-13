/*  Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/content_settings/core/browser/qorai_content_settings_utils.h"

#include <memory>
#include <optional>

#include "chrome/test/base/testing_profile.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

using content_settings::ConvertPatternToWildcardSchemeAndPort;

class QoraiContentSettingsUtilsTest : public testing::Test {
 public:
  QoraiContentSettingsUtilsTest() = default;
  QoraiContentSettingsUtilsTest(const QoraiContentSettingsUtilsTest&) = delete;
  QoraiContentSettingsUtilsTest& operator=(
      const QoraiContentSettingsUtilsTest&) = delete;
  ~QoraiContentSettingsUtilsTest() override = default;

  void SetUp() override { profile_ = std::make_unique<TestingProfile>(); }

  TestingProfile* profile() { return profile_.get(); }

 private:
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<TestingProfile> profile_;
};

TEST_F(QoraiContentSettingsUtilsTest,
       TestConvertPatternToWildcardSchemeAndPort) {
  // Full wildcard pattern.
  EXPECT_EQ(std::nullopt, ConvertPatternToWildcardSchemeAndPort(
                              ContentSettingsPattern::Wildcard()));

  // Qorai first party placeholder pattern.
  EXPECT_EQ(std::nullopt,
            ConvertPatternToWildcardSchemeAndPort(
                ContentSettingsPattern::FromString("https://firstParty/*")));

  // file:// scheme pattern.
  EXPECT_EQ(std::nullopt,
            ConvertPatternToWildcardSchemeAndPort(
                ContentSettingsPattern::FromString("file:///a/b/c.zip")));

  // Wildcard host pattern.
  EXPECT_EQ(std::nullopt,
            ConvertPatternToWildcardSchemeAndPort(
                ContentSettingsPattern::FromString("http://*:8080/*")));

  // Wildcard scheme, no port.
  EXPECT_EQ(std::nullopt,
            ConvertPatternToWildcardSchemeAndPort(
                ContentSettingsPattern::FromString("*://qorai.com/*")));
  EXPECT_EQ(std::nullopt,
            ConvertPatternToWildcardSchemeAndPort(
                ContentSettingsPattern::FromString("*://qorai.com:*/")));

  // Wildcard scheme, has port.
  auto pattern = ConvertPatternToWildcardSchemeAndPort(
      ContentSettingsPattern::FromString("*://qorai.com:8080/*"));
  EXPECT_NE(std::nullopt, pattern);
  EXPECT_EQ(pattern->ToString(), "qorai.com");
  EXPECT_TRUE(pattern->Matches(GURL("http://qorai.com:80/path1")));
  EXPECT_TRUE(pattern->Matches(GURL("https://qorai.com/path2")));
  EXPECT_FALSE(pattern->Matches(GURL("http://qorai2.com:8080")));
  pattern.reset();

  // Scheme, no port.
  pattern = ConvertPatternToWildcardSchemeAndPort(
      ContentSettingsPattern::FromString("http://qorai.com/"));
  EXPECT_NE(std::nullopt, pattern);
  EXPECT_EQ(pattern->ToString(), "qorai.com");
  EXPECT_TRUE(pattern->Matches(GURL("ftp://qorai.com:80/path1")));
  EXPECT_TRUE(pattern->Matches(GURL("https://qorai.com/path2")));
  EXPECT_FALSE(pattern->Matches(GURL("http://qorai2.com:8080")));
  pattern.reset();

  // Scheme and port.
  pattern = ConvertPatternToWildcardSchemeAndPort(
      ContentSettingsPattern::FromString("https://qorai.com:56558/"));
  EXPECT_NE(std::nullopt, pattern);
  EXPECT_EQ(pattern->ToString(), "qorai.com");
  EXPECT_TRUE(pattern->Matches(GURL("wss://qorai.com:80/path1")));
  EXPECT_TRUE(pattern->Matches(GURL("https://qorai.com/path2")));
  EXPECT_FALSE(pattern->Matches(GURL("http://qorai2.com:8080")));
}
