// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_shields/content/browser/qorai_farbling_service.h"

#include <array>
#include <memory>
#include <tuple>

#include "base/test/task_environment.h"
#include "base/token.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

class QoraiFarblingServiceTest : public testing::Test {
 public:
  QoraiFarblingServiceTest() = default;
  QoraiFarblingServiceTest(const QoraiFarblingServiceTest&) = delete;
  QoraiFarblingServiceTest& operator=(const QoraiFarblingServiceTest&) = delete;
  ~QoraiFarblingServiceTest() override = default;

  void SetUp() override {
    HostContentSettingsMap::RegisterProfilePrefs(prefs_.registry());
    settings_map_ = new HostContentSettingsMap(
        &prefs_, false /* is_off_the_record */, false /* store_last_modified */,
        false /* restore_session */, false /* should_record_metrics */);
    farbling_service_ =
        std::make_unique<qorai::QoraiFarblingService>(settings_map_.get());
  }

  void TearDown() override { settings_map_->ShutdownOnUIThread(); }

  qorai::QoraiFarblingService* farbling_service() {
    return farbling_service_.get();
  }

 protected:
  base::test::TaskEnvironment task_environment_;
  sync_preferences::TestingPrefServiceSyncable prefs_;
  scoped_refptr<HostContentSettingsMap> settings_map_;
  std::unique_ptr<qorai::QoraiFarblingService> farbling_service_;
};

TEST_F(QoraiFarblingServiceTest, PRNGKnownValues) {
  const std::array<std::tuple<GURL, uint64_t>, 2> test_cases = {
      std::make_tuple<>(GURL("http://a.com"), 10450951993123491723UL),
      std::make_tuple<>(GURL("http://b.com"), 2581208260237394178UL),
  };
  for (const auto& c : test_cases) {
    qorai::FarblingPRNG prng;
    ASSERT_TRUE(farbling_service()->MakePseudoRandomGeneratorForURL(
        std::get<0>(c), &prng));
    EXPECT_EQ(prng(), std::get<1>(c));
  }
}

TEST_F(QoraiFarblingServiceTest, PRNGKnownValuesDifferentSeeds) {
  const std::array<std::tuple<GURL, uint64_t>, 2> test_cases = {
      std::make_tuple<>(GURL("http://a.com"), 10450951993123491723UL),
      std::make_tuple<>(GURL("http://b.com"), 2581208260237394178UL),
  };
  for (const auto& c : test_cases) {
    qorai::FarblingPRNG prng;
    ASSERT_TRUE(farbling_service()->MakePseudoRandomGeneratorForURL(
        std::get<0>(c), &prng));
    EXPECT_EQ(prng(), std::get<1>(c));
  }
}

TEST_F(QoraiFarblingServiceTest, InvalidDomains) {
  const std::array<GURL, 8> test_cases = {
      GURL("about:blank"),
      GURL("qorai://settings"),
      GURL("chrome://version"),
      GURL("file:///etc/passwd"),
      GURL("javascript:alert(1)"),
      GURL("data:text/plain;base64,"),
      GURL(""),
  };
  for (const auto& url : test_cases) {
    qorai::FarblingPRNG prng;
    EXPECT_FALSE(
        farbling_service()->MakePseudoRandomGeneratorForURL(url, &prng));
    EXPECT_FALSE(
        farbling_service()->MakePseudoRandomGeneratorForURL(url, &prng));
  }
}

TEST_F(QoraiFarblingServiceTest, ShieldsDown) {
  const GURL url("http://a.com");
  qorai_shields::SetQoraiShieldsEnabled(settings_map_.get(), false, url);
  qorai::FarblingPRNG prng;
  EXPECT_FALSE(farbling_service()->MakePseudoRandomGeneratorForURL(url, &prng));
}

TEST_F(QoraiFarblingServiceTest, FingerprintingAllowed) {
  const GURL url("http://a.com");
  qorai_shields::SetFingerprintingControlType(
      settings_map_.get(), qorai_shields::ControlType::ALLOW, url);
  qorai::FarblingPRNG prng;
  EXPECT_FALSE(farbling_service()->MakePseudoRandomGeneratorForURL(url, &prng));
}
