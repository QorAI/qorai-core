/* Copyright (c) 2019 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_stats/qorai_stats_updater.h"

#include <memory>
#include <utility>

#include "base/command_line.h"
#include "base/files/scoped_temp_dir.h"
#include "base/strings/string_split.h"
#include "base/system/sys_info.h"
#include "base/test/bind.h"
#include "base/test/metrics/histogram_tester.h"
#include "base/test/scoped_feature_list.h"
#include "base/time/time.h"
#include "qorai/browser/qorai_ads/analytics/p3a/qorai_stats_helper.h"
#include "qorai/browser/qorai_stats/qorai_stats_updater_params.h"
#include "qorai/browser/qorai_stats/features.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_referrals/browser/qorai_referrals_service.h"
#include "qorai/components/qorai_referrals/common/pref_names.h"
#include "qorai/components/qorai_rewards/content/rewards_service.h"
#include "qorai/components/qorai_stats/browser/qorai_stats_updater_util.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_prefs.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/misc_metrics/general_browser_usage.h"
#include "build/build_config.h"
#include "chrome/browser/prefs/browser_prefs.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "content/public/common/content_switches.h"
#include "content/public/test/browser_task_environment.h"
#include "net/base/url_util.h"
#include "services/network/public/cpp/weak_wrapper_shared_url_loader_factory.h"
#include "services/network/test/test_url_loader_factory.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "ui/gfx/switches.h"

using testing::HasSubstr;

// npm run test -- qorai_unit_tests --filter=QorAIStatsUpdaterTest.*

constexpr char kYesterday[] = "2018-06-21";
constexpr char kToday[] = "2018-06-22";
constexpr char kTomorrow[] = "2018-06-23";

constexpr int kLastWeek = 24;
constexpr int kThisWeek = 25;
constexpr int kNextWeek = 26;

constexpr int kLastMonth = 5;
constexpr int kThisMonth = 6;
constexpr int kNextMonth = 7;

class QorAIStatsUpdaterTest : public testing::Test {
 public:
  QorAIStatsUpdaterTest()
      : task_environment_(base::test::TaskEnvironment::TimeSource::MOCK_TIME),
        shared_url_loader_factory_(
            base::MakeRefCounted<network::WeakWrapperSharedURLLoaderFactory>(
                &url_loader_factory_)) {}
  ~QorAIStatsUpdaterTest() override = default;

  void SetUp() override {
#if BUILDFLAG(IS_ANDROID)
    task_environment_.AdvanceClock(base::Days(2));
#else
    base::Time future_mock_time;
    if (base::Time::FromString("3000-01-04", &future_mock_time)) {
      task_environment_.AdvanceClock(future_mock_time - base::Time::Now());
    }
#endif
    qorai_wallet::RegisterLocalStatePrefs(testing_local_state_.registry());
    task_environment_.AdvanceClock(base::Minutes(30));

    qorai_stats::RegisterLocalStatePrefs(testing_local_state_.registry());
    misc_metrics::GeneralBrowserUsage::RegisterPrefs(
        testing_local_state_.registry());
    qorai::RegisterPrefsForQorAIReferralsService(
        testing_local_state_.registry());
    qorai_ads::QorAIStatsHelper::RegisterLocalStatePrefs(
        testing_local_state_.registry());
    SetCurrentTimeForTest(base::Time());
    qorai_stats::QorAIStatsUpdaterParams::SetFirstRunForTest(true);
  }

  void TearDown() override { qorai_stats_updater_ = nullptr; }

  PrefService* GetLocalState() { return &testing_local_state_; }
  std::unique_ptr<qorai_stats::QorAIStatsUpdaterParams> BuildUpdaterParams() {
    return std::make_unique<qorai_stats::QorAIStatsUpdaterParams>(
        GetLocalState(), qorai_stats::ProcessArch::kArchSkip);
  }
  void SetEnableAds(bool ads_enabled) {
    GetLocalState()->SetBoolean(qorai_ads::prefs::kEnabledForLastProfile,
                                ads_enabled);
  }

  void SetCurrentTimeForTest(const base::Time& current_time) {
    qorai_stats::QorAIStatsUpdaterParams::SetCurrentTimeForTest(current_time);
  }

 protected:
  content::BrowserTaskEnvironment task_environment_;
  base::test::ScopedFeatureList scoped_feature_list_;
  network::TestURLLoaderFactory url_loader_factory_;
  scoped_refptr<network::SharedURLLoaderFactory> shared_url_loader_factory_;
  base::HistogramTester histogram_tester_;
  std::unique_ptr<qorai_stats::QorAIStatsUpdater> qorai_stats_updater_;

  void SetupStatsUpdater(
      qorai_stats::QorAIStatsUpdater::StatsUpdatedCallback* update_cb) {
    url_loader_factory_.SetInterceptor(base::BindLambdaForTesting(
        [&](const network::ResourceRequest& request) {
          url_loader_factory_.ClearResponses();
          url_loader_factory_.AddResponse(request.url.spec(), "{\"ok\":1}");
          EXPECT_EQ(request.url.spec().find("https://localhost:8443"),
                    (size_t)0);
        }));
    qorai_stats_updater_ = std::make_unique<qorai_stats::QorAIStatsUpdater>(
        GetLocalState(),
        /*profile_manager*/ nullptr);
    qorai_stats_updater_->SetURLLoaderFactoryForTesting(
        shared_url_loader_factory_);
    qorai_stats_updater_->SetStatsUpdatedCallbackForTesting(update_cb);
    qorai_stats_updater_->SetUsageServerForTesting("https://localhost:8443");
  }

 private:
  TestingPrefServiceSimple testing_local_state_;
};

TEST_F(QorAIStatsUpdaterTest, IsDailyUpdateNeededLastCheckedYesterday) {
  GetLocalState()->SetString(kLastCheckYMD, kYesterday);

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetDailyParam(), "true");
  qorai_stats_updater_params.SavePrefs();

  EXPECT_EQ(GetLocalState()->GetString(kLastCheckYMD), kToday);
}

TEST_F(QorAIStatsUpdaterTest, IsDailyUpdateNeededLastCheckedToday) {
  GetLocalState()->SetString(kLastCheckYMD, kToday);

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetDailyParam(), "false");
  qorai_stats_updater_params.SavePrefs();

  EXPECT_EQ(GetLocalState()->GetString(kLastCheckYMD), kToday);
}

TEST_F(QorAIStatsUpdaterTest, IsDailyUpdateNeededLastCheckedTomorrow) {
  GetLocalState()->SetString(kLastCheckYMD, kTomorrow);

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetDailyParam(), "false");
  qorai_stats_updater_params.SavePrefs();

  EXPECT_EQ(GetLocalState()->GetString(kLastCheckYMD), kToday);
}

TEST_F(QorAIStatsUpdaterTest, IsWeeklyUpdateNeededLastCheckedLastWeek) {
  GetLocalState()->SetInteger(kLastCheckWOY, kLastWeek);

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetWeeklyParam(), "true");
  qorai_stats_updater_params.SavePrefs();

  EXPECT_EQ(GetLocalState()->GetInteger(kLastCheckWOY), kThisWeek);
}

TEST_F(QorAIStatsUpdaterTest, IsWeeklyUpdateNeededLastCheckedThisWeek) {
  GetLocalState()->SetInteger(kLastCheckWOY, kThisWeek);

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetWeeklyParam(), "false");
  qorai_stats_updater_params.SavePrefs();

  EXPECT_EQ(GetLocalState()->GetInteger(kLastCheckWOY), kThisWeek);
}

TEST_F(QorAIStatsUpdaterTest, IsWeeklyUpdateNeededLastCheckedNextWeek) {
  GetLocalState()->SetInteger(kLastCheckWOY, kNextWeek);

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetWeeklyParam(), "true");
  qorai_stats_updater_params.SavePrefs();

  EXPECT_EQ(GetLocalState()->GetInteger(kLastCheckWOY), kThisWeek);
}

TEST_F(QorAIStatsUpdaterTest, IsMonthlyUpdateNeededLastCheckedLastMonth) {
  GetLocalState()->SetInteger(kLastCheckMonth, kLastMonth);

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetMonthlyParam(), "true");
  qorai_stats_updater_params.SavePrefs();

  EXPECT_EQ(GetLocalState()->GetInteger(kLastCheckMonth), kThisMonth);
}

TEST_F(QorAIStatsUpdaterTest, IsMonthlyUpdateNeededLastCheckedThisMonth) {
  GetLocalState()->SetInteger(kLastCheckMonth, kThisMonth);

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetMonthlyParam(), "false");
  qorai_stats_updater_params.SavePrefs();

  EXPECT_EQ(GetLocalState()->GetInteger(kLastCheckMonth), kThisMonth);
}

TEST_F(QorAIStatsUpdaterTest, IsMonthlyUpdateNeededLastCheckedNextMonth) {
  GetLocalState()->SetInteger(kLastCheckMonth, kNextMonth);

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetMonthlyParam(), "true");
  qorai_stats_updater_params.SavePrefs();

  EXPECT_EQ(GetLocalState()->GetInteger(kLastCheckMonth), kThisMonth);
}

TEST_F(QorAIStatsUpdaterTest, HasAdsDisabled) {
  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  SetEnableAds(false);
  EXPECT_EQ(qorai_stats_updater_params.GetAdsEnabledParam(), "false");
}

TEST_F(QorAIStatsUpdaterTest, HasAdsEnabled) {
  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  SetEnableAds(true);
  EXPECT_EQ(qorai_stats_updater_params.GetAdsEnabledParam(), "true");
}

TEST_F(QorAIStatsUpdaterTest, HasArchSkip) {
  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetProcessArchParam(), "");
}

TEST_F(QorAIStatsUpdaterTest, HasArchVirt) {
  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchVirt, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetProcessArchParam(), "virt");
}

TEST_F(QorAIStatsUpdaterTest, HasArchMetal) {
  auto arch = base::SysInfo::OperatingSystemArchitecture();
  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchMetal, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetProcessArchParam(), arch);
}

TEST_F(QorAIStatsUpdaterTest, HasDateOfInstallationFirstRun) {
  base::Time::Exploded exploded;
  base::Time current_time;

  // Set date to 2018-11-04 (ISO week #44)
  exploded.hour = 0;
  exploded.minute = 0;
  exploded.second = 0;
  exploded.millisecond = 0;
  exploded.day_of_week = 0;
  exploded.year = 2018;
  exploded.month = 11;
  exploded.day_of_month = 4;

  EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));
  SetCurrentTimeForTest(current_time);

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(qorai_stats_updater_params.GetDateOfInstallationParam(),
            "2018-11-04");
}

TEST_F(QorAIStatsUpdaterTest, HasDailyRetention) {
  base::Time::Exploded exploded;
  base::Time current_time, dtoi_time;

  // Set date to 2018-11-04
  exploded.hour = 0;
  exploded.minute = 0;
  exploded.second = 0;
  exploded.millisecond = 0;
  exploded.day_of_week = 0;
  exploded.year = 2018;
  exploded.month = 11;
  exploded.day_of_month = 4;

  EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &dtoi_time));
  // Make first run date 15 days earlier (still within 30 day window)
  exploded.day_of_month = 20;
  EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));

  SetCurrentTimeForTest(dtoi_time);
  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  SetCurrentTimeForTest(current_time);
  EXPECT_EQ(qorai_stats_updater_params.GetDateOfInstallationParam(),
            "2018-11-04");
}

TEST_F(QorAIStatsUpdaterTest, GetUpdateURLHasFirstAndDtoi) {
  base::Time current_time, install_time;

  // Set date to 2018-11-04
  EXPECT_TRUE(base::Time::FromString("2018-11-04", &install_time));

  // Make first run date 15 days earlier (still within 30 day window)
  current_time = install_time + base::Days(16);

  SetCurrentTimeForTest(install_time);
  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  SetCurrentTimeForTest(current_time);

  GURL response = qorai_stats_updater_params.GetUpdateURL(
      GURL("https://demo.qorai.com"), "platform id here", "channel name here",
      "full qorai version here");

  base::StringPairs kv_pairs;
  // this will return `false` because at least one argument has no value
  // ex: `arch` will have an empty value (because of kArchSkip).
  base::SplitStringIntoKeyValuePairsUsingSubstr(response.query(), '=', "&",
                                                &kv_pairs);
  EXPECT_FALSE(kv_pairs.empty());

  bool first_is_true = false;
  bool has_dtoi = false;
  for (auto& kv : kv_pairs) {
    if (kv.first == "first") {
      EXPECT_EQ(kv.second, "true");
      first_is_true = true;
    } else if (kv.first == "dtoi") {
      EXPECT_EQ(kv.second, "2018-11-04");
      has_dtoi = true;
      // Audit passed-through parameters.
      // Should not be modified (other than url encode).
    } else if (kv.first == "platform") {
      EXPECT_EQ(kv.second, "platform+id+here");
    } else if (kv.first == "channel") {
      EXPECT_EQ(kv.second, "channel+name+here");
    } else if (kv.first == "version") {
      EXPECT_EQ(kv.second, "full+qorai+version+here");
    }
  }

  EXPECT_EQ(true, first_is_true);
  EXPECT_EQ(true, has_dtoi);
}

TEST_F(QorAIStatsUpdaterTest, HasDailyRetentionExpiration) {
  base::Time::Exploded exploded;
  base::Time current_time, dtoi_time;

  // Set date to 2018-11-04
  exploded.hour = 0;
  exploded.minute = 0;
  exploded.second = 0;
  exploded.millisecond = 0;
  exploded.day_of_week = 0;
  exploded.year = 2018;
  exploded.month = 11;
  exploded.day_of_month = 4;

  EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &dtoi_time));
  // Make first run date a month earlier (outside 30 day window)
  exploded.month = 12;
  EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));

  SetCurrentTimeForTest(dtoi_time);
  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  SetCurrentTimeForTest(current_time);
  EXPECT_EQ(qorai_stats_updater_params.GetDateOfInstallationParam(), "null");
}

// This test ensures that our weekly stats cut over on Monday
TEST_F(QorAIStatsUpdaterTest, IsWeeklyUpdateNeededOnMondayLastCheckedOnSunday) {
  base::Time::Exploded exploded;
  base::Time current_time;

  {
    // Set our local state to indicate that the last weekly check was
    // performed during ISO week #43
    GetLocalState()->SetInteger(kLastCheckWOY, 43);

    // Set date to 2018-11-04 (ISO week #44)
    exploded.hour = 0;
    exploded.minute = 0;
    exploded.second = 0;
    exploded.millisecond = 0;
    exploded.day_of_week = 0;
    exploded.year = 2018;
    exploded.month = 11;
    exploded.day_of_month = 4;

    EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));

    SetCurrentTimeForTest(current_time);
    qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
        GetLocalState(), qorai_stats::ProcessArch::kArchSkip);

    // Make sure that the weekly param was set to true, since this is
    // a new ISO week (#44)
    EXPECT_EQ(qorai_stats_updater_params.GetWeeklyParam(), "true");
    qorai_stats_updater_params.SavePrefs();

    // Make sure that local state was updated to reflect this as well
    EXPECT_EQ(GetLocalState()->GetInteger(kLastCheckWOY), 44);
  }

  {
    // Now it's the next day (Monday)
    exploded.day_of_week = 1;
    exploded.day_of_month = 5;

    EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));

    SetCurrentTimeForTest(current_time);
    qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
        GetLocalState(), qorai_stats::ProcessArch::kArchSkip);

    // Make sure that the weekly param was set to true, since this is
    // a new ISO week (#45)
    EXPECT_EQ(qorai_stats_updater_params.GetWeeklyParam(), "true");
    qorai_stats_updater_params.SavePrefs();

    // Make sure that local state was updated to reflect this as well
    EXPECT_EQ(GetLocalState()->GetInteger(kLastCheckWOY), 45);
  }

  {
    // Now it's the next day (Tuesday)
    exploded.day_of_week = 2;
    exploded.day_of_month = 6;

    EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));

    SetCurrentTimeForTest(current_time);
    qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
        GetLocalState(), qorai_stats::ProcessArch::kArchSkip);

    // Make sure that the weekly param was set to false, since this is
    // still the same ISO week (#45)
    EXPECT_EQ(qorai_stats_updater_params.GetWeeklyParam(), "false");
    qorai_stats_updater_params.SavePrefs();

    // Make sure that local state also didn't change
    EXPECT_EQ(GetLocalState()->GetInteger(kLastCheckWOY), 45);
  }
}

TEST_F(QorAIStatsUpdaterTest, HasCorrectWeekOfInstallation) {
  base::Time::Exploded exploded;
  base::Time current_time;

  {
    // Set date to 2019-03-24 (Sunday)
    exploded.hour = 0;
    exploded.minute = 0;
    exploded.second = 0;
    exploded.millisecond = 0;
    exploded.day_of_week = 0;
    exploded.year = 2019;
    exploded.month = 3;
    exploded.day_of_month = 24;

    EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));
    SetCurrentTimeForTest(current_time);

    // Make sure that week of installation is previous Monday
    qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
        GetLocalState(), qorai_stats::ProcessArch::kArchSkip);
    EXPECT_EQ(qorai_stats_updater_params.GetWeekOfInstallationParam(),
              "2019-03-18");
  }

  {
    // Set date to 2019-03-25 (Monday)
    exploded.hour = 0;
    exploded.minute = 0;
    exploded.second = 0;
    exploded.millisecond = 0;
    exploded.day_of_week = 0;
    exploded.year = 2019;
    exploded.month = 3;
    exploded.day_of_month = 25;

    EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));
    SetCurrentTimeForTest(current_time);

    // Make sure that week of installation is today, since today is a
    // Monday
    qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
        GetLocalState(), qorai_stats::ProcessArch::kArchSkip);
    EXPECT_EQ(qorai_stats_updater_params.GetWeekOfInstallationParam(),
              "2019-03-25");
  }

  {
    // Set date to 2019-03-30 (Saturday)
    exploded.hour = 0;
    exploded.minute = 0;
    exploded.second = 0;
    exploded.millisecond = 0;
    exploded.day_of_week = 0;
    exploded.year = 2019;
    exploded.month = 3;
    exploded.day_of_month = 30;

    EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &current_time));
    SetCurrentTimeForTest(current_time);

    // Make sure that week of installation is previous Monday
    qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
        GetLocalState(), qorai_stats::ProcessArch::kArchSkip);
    EXPECT_EQ(qorai_stats_updater_params.GetWeekOfInstallationParam(),
              "2019-03-25");
  }
}

TEST_F(QorAIStatsUpdaterTest, GetIsoWeekNumber) {
  base::Time::Exploded exploded;
  exploded.hour = 0;
  exploded.minute = 0;
  exploded.second = 0;
  exploded.millisecond = 0;
  exploded.day_of_week = 1;
  exploded.day_of_month = 29;
  exploded.month = 7;
  exploded.year = 2019;

  base::Time time;
  EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &time));
  EXPECT_EQ(qorai_stats::GetIsoWeekNumber(time), 31);

  exploded.day_of_month = 30;
  exploded.month = 9;

  EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &time));
  EXPECT_EQ(qorai_stats::GetIsoWeekNumber(time), 40);

  exploded.day_of_month = 1;
  exploded.month = 9;
  exploded.day_of_week = 0;

  EXPECT_TRUE(base::Time::FromLocalExploded(exploded, &time));
  EXPECT_EQ(qorai_stats::GetIsoWeekNumber(time), 35);
}

TEST_F(QorAIStatsUpdaterTest, UsageBitstringDaily) {
  base::Time last_reported_use;
  base::Time last_use;

  EXPECT_TRUE(base::Time::FromString("2020-03-31", &last_use));
  EXPECT_TRUE(base::Time::FromString("2020-03-30", &last_reported_use));

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);

  EXPECT_EQ(0b001, qorai_stats::UsageBitfieldFromTimestamp(last_use,
                                                           last_reported_use));
}

TEST_F(QorAIStatsUpdaterTest, UsageBitstringWeekly) {
  base::Time last_reported_use;
  base::Time last_use;

  EXPECT_TRUE(base::Time::FromString("2020-03-31", &last_use));
  EXPECT_TRUE(base::Time::FromString("2020-03-26", &last_reported_use));

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);

  EXPECT_EQ(0b011, qorai_stats::UsageBitfieldFromTimestamp(last_use,
                                                           last_reported_use));
}

TEST_F(QorAIStatsUpdaterTest, UsageBitstringMonthlySameWeek) {
  base::Time last_reported_use;
  base::Time last_use;

  EXPECT_TRUE(base::Time::FromString("2020-07-01", &last_use));
  EXPECT_TRUE(base::Time::FromString("2020-06-30", &last_reported_use));

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(0b101, qorai_stats::UsageBitfieldFromTimestamp(last_use,
                                                           last_reported_use));
}

TEST_F(QorAIStatsUpdaterTest, UsageBitstringMonthlyDiffWeek) {
  base::Time last_reported_use;
  base::Time last_use;

  EXPECT_TRUE(base::Time::FromString("2020-03-01", &last_use));
  EXPECT_TRUE(base::Time::FromString("2020-02-15", &last_reported_use));

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(0b111, qorai_stats::UsageBitfieldFromTimestamp(last_use,
                                                           last_reported_use));
}

TEST_F(QorAIStatsUpdaterTest, UsageBitstringInactive) {
  base::Time last_reported_use;
  base::Time last_use;

  EXPECT_TRUE(base::Time::FromString("2020-03-31", &last_use));
  EXPECT_TRUE(base::Time::FromString("2020-03-31", &last_reported_use));

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(0b000, qorai_stats::UsageBitfieldFromTimestamp(last_use,
                                                           last_reported_use));
}

TEST_F(QorAIStatsUpdaterTest, UsageBitstringNeverUsed) {
  base::Time last_reported_use;
  base::Time last_use;

  qorai_stats::QorAIStatsUpdaterParams qorai_stats_updater_params(
      GetLocalState(), qorai_stats::ProcessArch::kArchSkip, kToday, kThisWeek,
      kThisMonth);
  EXPECT_EQ(0b000, qorai_stats::UsageBitfieldFromTimestamp(last_use,
                                                           last_reported_use));
}

TEST_F(QorAIStatsUpdaterTest, UsageURLFlags) {
  auto params = BuildUpdaterParams();

  GURL base_url("http://localhost:8080");
  GURL url;

  PrefService* local_state = GetLocalState();

  url = params->GetUpdateURL(base_url, "", "", "");
  EXPECT_THAT(url.query(), HasSubstr("daily=true&weekly=true&monthly=true"));
  EXPECT_THAT(url.query(), HasSubstr("wallet2=0"));
  params->SavePrefs();

  task_environment_.AdvanceClock(base::Days(1));
  local_state->SetTime(kQorAIWalletLastUnlockTime, base::Time::Now());

  params = BuildUpdaterParams();
  url = params->GetUpdateURL(base_url, "", "", "");
  EXPECT_THAT(url.query(), HasSubstr("daily=true&weekly=false&monthly=false"));
  EXPECT_THAT(url.query(), HasSubstr("wallet2=7"));
  params->SavePrefs();

  task_environment_.AdvanceClock(base::Days(6));
  local_state->SetTime(kQorAIWalletLastUnlockTime, base::Time::Now());
  params = BuildUpdaterParams();
  url = params->GetUpdateURL(base_url, "", "", "");
  EXPECT_THAT(url.query(), HasSubstr("daily=true&weekly=true&monthly=false"));
  EXPECT_THAT(url.query(), HasSubstr("wallet2=3"));
  params->SavePrefs();

  task_environment_.AdvanceClock(base::Days(1));
  local_state->SetTime(kQorAIWalletLastUnlockTime, base::Time::Now());
  params = BuildUpdaterParams();
  url = params->GetUpdateURL(base_url, "", "", "");
  EXPECT_THAT(url.query(), HasSubstr("daily=true&weekly=false&monthly=false"));
  EXPECT_THAT(url.query(), HasSubstr("wallet2=1"));
  params->SavePrefs();
}

TEST_F(QorAIStatsUpdaterTest, UsagePingRequest) {
  int ping_count = 0;
  GURL last_url;

  qorai_stats::QorAIStatsUpdater::StatsUpdatedCallback cb = base::BindRepeating(
      [](int* ping_count, GURL* last_url, const GURL& url) {
        *last_url = url;
        (*ping_count)++;
      },
      &ping_count, &last_url);
  SetupStatsUpdater(&cb);

  // daily, monthly, weekly ping
  task_environment_.FastForwardBy(base::Hours(1));
  EXPECT_THAT(last_url.query(),
              HasSubstr("daily=true&weekly=true&monthly=true"));
  EXPECT_THAT(last_url.query(), Not(HasSubstr(qorai_stats::kHeadlessRefcode)));

  // daily ping
  task_environment_.AdvanceClock(base::Days(1));
  task_environment_.FastForwardBy(base::Seconds(1));
  EXPECT_THAT(last_url.query(),
              HasSubstr("daily=true&weekly=false&monthly=false"));
  EXPECT_THAT(last_url.query(), Not(HasSubstr(qorai_stats::kHeadlessRefcode)));

  // daily, weekly ping
  task_environment_.AdvanceClock(base::Days(7));
  task_environment_.FastForwardBy(base::Seconds(1));
  EXPECT_THAT(last_url.query(),
              HasSubstr("daily=true&weekly=true&monthly=false"));
  EXPECT_THAT(last_url.query(), Not(HasSubstr(qorai_stats::kHeadlessRefcode)));

  ASSERT_EQ(ping_count, 3);
}

#if !BUILDFLAG(IS_ANDROID)
TEST_F(QorAIStatsUpdaterTest, HeadlessPing) {
  scoped_feature_list_.InitWithFeatures(
      {}, {qorai_stats::features::kHeadlessRefcode});
  base::CommandLine::ForCurrentProcess()->AppendSwitch(switches::kHeadless);

  qorai_stats::QorAIStatsUpdater::StatsUpdatedCallback cb =
      base::BindRepeating([](const GURL& url) { FAIL(); });
  SetupStatsUpdater(&cb);

  // daily, monthly, weekly ping
  task_environment_.FastForwardBy(base::Hours(1));

  qorai_stats_updater_ = nullptr;

  scoped_feature_list_.Reset();
  scoped_feature_list_.InitWithFeatures(
      {qorai_stats::features::kHeadlessRefcode}, {});

  size_t pings_sent = 0;
  cb = base::BindRepeating(
      [](size_t* pings_sent, const GURL& url) {
        (*pings_sent)++;
        EXPECT_THAT(url.query(), HasSubstr(qorai_stats::kHeadlessRefcode));
      },
      &pings_sent);
  SetupStatsUpdater(&cb);

  // daily, monthly, weekly ping
  task_environment_.FastForwardBy(base::Hours(1));
  EXPECT_EQ(pings_sent, 1u);
}
#endif

TEST_F(QorAIStatsUpdaterTest, AutomationEnabledPing) {
  scoped_feature_list_.InitWithFeatures(
      {}, {qorai_stats::features::kHeadlessRefcode});
  base::CommandLine::ForCurrentProcess()->AppendSwitch(
      switches::kEnableAutomation);

  qorai_stats::QorAIStatsUpdater::StatsUpdatedCallback cb =
      base::BindRepeating([](const GURL& url) { FAIL(); });
  SetupStatsUpdater(&cb);

  // daily, monthly, weekly ping
  task_environment_.FastForwardBy(base::Hours(1));

  qorai_stats_updater_ = nullptr;

  scoped_feature_list_.Reset();
  scoped_feature_list_.InitWithFeatures(
      {qorai_stats::features::kHeadlessRefcode}, {});

  size_t pings_sent = 0;
  cb = base::BindRepeating(
      [](size_t* pings_sent, const GURL& url) {
        (*pings_sent)++;

        EXPECT_THAT(url.query(), HasSubstr(qorai_stats::kHeadlessRefcode));
      },
      &pings_sent);
  SetupStatsUpdater(&cb);

  // daily, monthly, weekly ping
  task_environment_.FastForwardBy(base::Hours(1));
  EXPECT_EQ(pings_sent, 1u);
}

TEST_F(QorAIStatsUpdaterTest, RecordP3APing) {
  qorai_stats::QorAIStatsUpdater updater(GetLocalState(),
                                         /*profile_manager*/ nullptr);
  updater.SetURLLoaderFactoryForTesting(shared_url_loader_factory_);

  histogram_tester_.ExpectUniqueSample(
      qorai_stats::kP3AMonthlyPingHistogramName, 1, 1);
  histogram_tester_.ExpectUniqueSample(qorai_stats::kP3ADailyPingHistogramName,
                                       1, 1);

  task_environment_.FastForwardBy(base::Days(1));

  histogram_tester_.ExpectUniqueSample(
      qorai_stats::kP3AMonthlyPingHistogramName, 1, 1);
  histogram_tester_.ExpectUniqueSample(qorai_stats::kP3ADailyPingHistogramName,
                                       1, 1);
}

TEST_F(QorAIStatsUpdaterTest, StatsUpdaterMigration) {
  // Create a pre 1.19 user.
  // Has a download_id, kReferralCheckedForPromoCodeFile is set, has promo code.
  ASSERT_FALSE(GetLocalState()->GetBoolean(kReferralInitialization));
  GetLocalState()->SetString(kReferralDownloadID, "migration");
  GetLocalState()->SetString(kReferralPromoCode, "BRV001");
  GetLocalState()->SetBoolean(kReferralCheckedForPromoCodeFile, true);

  auto params = BuildUpdaterParams();
  GURL base_url("http://localhost:8080");

  // Verify that update url is valid
  const GURL update_url = params->GetUpdateURL(base_url, "", "", "");
  EXPECT_TRUE(update_url.is_valid());

  // Verify that daily parameter is true
  std::string query_value;
  EXPECT_TRUE(net::GetValueForKeyInQuery(update_url, "daily", &query_value));
  EXPECT_EQ(query_value, "true");

  // Verify that there is the correct referral code
  EXPECT_TRUE(net::GetValueForKeyInQuery(update_url, "ref", &query_value));
  EXPECT_EQ(query_value, "BRV001");
}
