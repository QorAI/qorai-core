// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_news/browser/qorai_news_p3a.h"

#include <memory>

#include "base/test/metrics/histogram_tester.h"
#include "qorai/components/qorai_news/browser/qorai_news_controller.h"
#include "qorai/components/qorai_news/browser/qorai_news_pref_manager.h"
#include "qorai/components/qorai_news/common/p3a_pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/time_period_storage/weekly_storage.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/scoped_user_pref_update.h"
#include "components/prefs/testing_pref_service.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace qorai_news::p3a {

class QoraiNewsP3ATest : public testing::Test {
 public:
  QoraiNewsP3ATest()
      : task_environment_(base::test::TaskEnvironment::TimeSource::MOCK_TIME) {}

 protected:
  void SetUp() override {
    task_environment_.AdvanceClock(base::Days(2));
    PrefRegistrySimple* registry = pref_service_.registry();
    ::qorai_news::prefs::RegisterProfilePrefs(registry);
    registry->RegisterBooleanPref(qorai_rewards::prefs::kEnabled, false);

    pref_manager_ = std::make_unique<QoraiNewsPrefManager>(pref_service_);
    metrics_ = std::make_unique<NewsMetrics>(&pref_service_, *pref_manager_);
  }

  void TearDown() override {
    metrics_ = nullptr;
    pref_manager_ = nullptr;
  }

  PrefService* GetPrefs() { return &pref_service_; }

  int GetWeeklySum(const char* pref_name) {
    WeeklyStorage storage(&pref_service_, pref_name);
    return storage.GetWeeklySum();
  }

  std::unique_ptr<NewsMetrics> metrics_;
  content::BrowserTaskEnvironment task_environment_;
  base::HistogramTester histogram_tester_;
  std::unique_ptr<QoraiNewsPrefManager> pref_manager_;

 private:
  TestingPrefServiceSimple pref_service_;
};

TEST_F(QoraiNewsP3ATest, TestWeeklySessionCountBasic) {
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kWeeklySessionCountHistogramName, 1);
  histogram_tester_.ExpectBucketCount(kWeeklySessionCountHistogramName, 0, 1);

  metrics_->RecordAtSessionStart();
  histogram_tester_.ExpectTotalCount(kWeeklySessionCountHistogramName, 2);
  histogram_tester_.ExpectBucketCount(kWeeklySessionCountHistogramName, 1, 1);

  metrics_->RecordAtSessionStart();
  histogram_tester_.ExpectTotalCount(kWeeklySessionCountHistogramName, 3);
  histogram_tester_.ExpectBucketCount(kWeeklySessionCountHistogramName, 2, 1);
  metrics_->RecordAtSessionStart();
  histogram_tester_.ExpectTotalCount(kWeeklySessionCountHistogramName, 4);
  histogram_tester_.ExpectBucketCount(kWeeklySessionCountHistogramName, 2, 2);

  metrics_->RecordAtSessionStart();
  metrics_->RecordAtSessionStart();
  metrics_->RecordAtSessionStart();
  metrics_->RecordAtSessionStart();
  histogram_tester_.ExpectTotalCount(kWeeklySessionCountHistogramName, 8);
  histogram_tester_.ExpectBucketCount(kWeeklySessionCountHistogramName, 3, 4);

  EXPECT_EQ(GetWeeklySum(prefs::kQoraiNewsWeeklySessionCount), 7);
}

TEST_F(QoraiNewsP3ATest, TestWeeklySessionCountTimeFade) {
  metrics_->RecordAtSessionStart();
  metrics_->RecordAtSessionStart();

  task_environment_.AdvanceClock(base::Days(2));
  metrics_->RecordAtSessionStart();

  task_environment_.AdvanceClock(base::Days(2));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kWeeklySessionCountHistogramName, 4);
  histogram_tester_.ExpectBucketCount(kWeeklySessionCountHistogramName, 2, 3);

  EXPECT_EQ(GetWeeklySum(prefs::kQoraiNewsWeeklySessionCount), 3);

  task_environment_.AdvanceClock(base::Days(3));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kWeeklySessionCountHistogramName, 5);
  histogram_tester_.ExpectBucketCount(kWeeklySessionCountHistogramName, 1, 2);

  task_environment_.AdvanceClock(base::Days(2));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kWeeklySessionCountHistogramName, 6);
  histogram_tester_.ExpectBucketCount(kWeeklySessionCountHistogramName, 0, 1);

  EXPECT_EQ(GetWeeklySum(prefs::kQoraiNewsWeeklySessionCount), 0);
}

TEST_F(QoraiNewsP3ATest, TestWeeklyDisplayAdsViewedCount) {
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kNonRewardsAdsViewsHistogramName, 1);
  histogram_tester_.ExpectBucketCount(kNonRewardsAdsViewsHistogramName, 0, 1);

  metrics_->RecordWeeklyDisplayAdsViewedCount(true);
  metrics_->RecordWeeklyDisplayAdsViewedCount(true);

  task_environment_.AdvanceClock(base::Days(2));
  metrics_->RecordWeeklyDisplayAdsViewedCount(true);

  EXPECT_EQ(GetWeeklySum(prefs::kQoraiNewsWeeklyDisplayAdViewedCount), 3);

  task_environment_.AdvanceClock(base::Days(2));
  metrics_->RecordWeeklyDisplayAdsViewedCount(false);
  histogram_tester_.ExpectTotalCount(kNonRewardsAdsViewsHistogramName, 5);
  histogram_tester_.ExpectBucketCount(kNonRewardsAdsViewsHistogramName, 2, 3);

  task_environment_.AdvanceClock(base::Days(3));
  metrics_->RecordWeeklyDisplayAdsViewedCount(false);
  histogram_tester_.ExpectTotalCount(kNonRewardsAdsViewsHistogramName, 6);
  histogram_tester_.ExpectBucketCount(kNonRewardsAdsViewsHistogramName, 1, 2);

  task_environment_.AdvanceClock(base::Days(2));
  metrics_->RecordWeeklyDisplayAdsViewedCount(false);
  histogram_tester_.ExpectTotalCount(kNonRewardsAdsViewsHistogramName, 7);
  histogram_tester_.ExpectBucketCount(kNonRewardsAdsViewsHistogramName, 0, 2);

  EXPECT_EQ(GetWeeklySum(prefs::kQoraiNewsWeeklyDisplayAdViewedCount), 0);
}

TEST_F(QoraiNewsP3ATest, TestWeeklyAddedDirectFeedsCount) {
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kWeeklyAddedDirectFeedsHistogramName, 1);
  histogram_tester_.ExpectBucketCount(kWeeklyAddedDirectFeedsHistogramName, 0,
                                      1);

  pref_manager_->AddDirectPublisher(GURL("https://foo.com"), "");
  pref_manager_->AddDirectPublisher(GURL("https://bar.com"), "");

  task_environment_.AdvanceClock(base::Days(2));

  // Add a feed we're already subscribed to (should have no effect).
  pref_manager_->AddDirectPublisher(GURL("https://foo.com"), "");

  histogram_tester_.ExpectTotalCount(kWeeklyAddedDirectFeedsHistogramName, 3);
  histogram_tester_.ExpectBucketCount(kWeeklyAddedDirectFeedsHistogramName, 1,
                                      1);

  pref_manager_->AddDirectPublisher(GURL("https://baz.com"), "");
  auto id_to_remove =
      pref_manager_->AddDirectPublisher(GURL("https://buz.com"), "");

  EXPECT_EQ(GetWeeklySum(prefs::kQoraiNewsWeeklyAddedDirectFeedsCount), 4);

  histogram_tester_.ExpectTotalCount(kWeeklyAddedDirectFeedsHistogramName, 5);
  histogram_tester_.ExpectBucketCount(kWeeklyAddedDirectFeedsHistogramName, 4,
                                      1);

  // Unsubscribe from a direct feed (should trigger a -1) being recorded.
  pref_manager_->SetPublisherSubscribed(id_to_remove,
                                        mojom::UserEnabled::DISABLED);
  histogram_tester_.ExpectTotalCount(kWeeklyAddedDirectFeedsHistogramName, 6);
  histogram_tester_.ExpectBucketCount(kWeeklyAddedDirectFeedsHistogramName, 3,
                                      2);

  task_environment_.AdvanceClock(base::Days(6));

  // Add a feed we're already subscribed to.
  pref_manager_->AddDirectPublisher(GURL("https://foo.com"), "");

  histogram_tester_.ExpectTotalCount(kWeeklyAddedDirectFeedsHistogramName, 6);
  histogram_tester_.ExpectBucketCount(kWeeklyAddedDirectFeedsHistogramName, 1,
                                      1);

  EXPECT_EQ(GetWeeklySum(prefs::kQoraiNewsWeeklyAddedDirectFeedsCount), 1);
}

TEST_F(QoraiNewsP3ATest, TestDirectFeedsTotal) {
  PrefService* prefs = GetPrefs();
  metrics_->RecordAtInit();

  // Should not report if not a monthly user
  histogram_tester_.ExpectTotalCount(kDirectFeedsTotalHistogramName, 0);

  prefs->SetTime(prefs::kQoraiNewsLastSessionTime, base::Time::Now());
  metrics_->RecordAtInit();

  histogram_tester_.ExpectTotalCount(kDirectFeedsTotalHistogramName, 1);
  histogram_tester_.ExpectBucketCount(kDirectFeedsTotalHistogramName, 0, 1);

  pref_manager_->AddDirectPublisher(GURL("https://foo.com"), "");
  pref_manager_->AddDirectPublisher(GURL("https://bar.com"), "");

  histogram_tester_.ExpectTotalCount(kDirectFeedsTotalHistogramName, 3);
  histogram_tester_.ExpectBucketCount(kDirectFeedsTotalHistogramName, 1, 1);
  histogram_tester_.ExpectBucketCount(kDirectFeedsTotalHistogramName, 2, 1);
}

TEST_F(QoraiNewsP3ATest, TestTotalCardsViewed) {
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kTotalCardViewsHistogramName, 1);
  histogram_tester_.ExpectBucketCount(kTotalCardViewsHistogramName, 0, 1);

  metrics_->RecordTotalActionCount(ActionType::kCardView, 0);
  histogram_tester_.ExpectBucketCount(kTotalCardViewsHistogramName, 0, 2);

  metrics_->RecordTotalActionCount(ActionType::kCardView, 1);
  histogram_tester_.ExpectBucketCount(kTotalCardViewsHistogramName, 1, 1);

  metrics_->RecordTotalActionCount(ActionType::kCardView, 14);
  histogram_tester_.ExpectBucketCount(kTotalCardViewsHistogramName, 3, 1);

  task_environment_.AdvanceClock(base::Days(4));
  EXPECT_EQ(GetWeeklySum(prefs::kQoraiNewsTotalCardViews), 15);

  metrics_->RecordAtSessionStart();
  metrics_->RecordTotalActionCount(ActionType::kCardView, 15);
  histogram_tester_.ExpectBucketCount(kTotalCardViewsHistogramName, 4, 1);

  metrics_->RecordAtSessionStart();
  metrics_->RecordTotalActionCount(ActionType::kCardView, 15);
  histogram_tester_.ExpectBucketCount(kTotalCardViewsHistogramName, 5, 1);

  task_environment_.AdvanceClock(base::Days(4));

  metrics_->RecordAtSessionStart();
  metrics_->RecordTotalActionCount(ActionType::kCardView, 0);
  histogram_tester_.ExpectBucketCount(kTotalCardViewsHistogramName, 4, 2);
}

TEST_F(QoraiNewsP3ATest, TestLastUsageTime) {
  metrics_->RecordAtInit();
  // Should not report if News was never used
  histogram_tester_.ExpectTotalCount(kLastUsageTimeHistogramName, 0);

  metrics_->RecordAtSessionStart();
  histogram_tester_.ExpectTotalCount(kLastUsageTimeHistogramName, 1);
  histogram_tester_.ExpectBucketCount(kLastUsageTimeHistogramName, 1, 1);

  task_environment_.AdvanceClock(base::Days(7));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kLastUsageTimeHistogramName, 2);
  histogram_tester_.ExpectBucketCount(kLastUsageTimeHistogramName, 2, 1);

  task_environment_.AdvanceClock(base::Days(7));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kLastUsageTimeHistogramName, 3);
  histogram_tester_.ExpectBucketCount(kLastUsageTimeHistogramName, 3, 1);

  metrics_->RecordAtSessionStart();
  histogram_tester_.ExpectTotalCount(kLastUsageTimeHistogramName, 4);
  histogram_tester_.ExpectBucketCount(kLastUsageTimeHistogramName, 1, 2);

  task_environment_.AdvanceClock(base::Days(21));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kLastUsageTimeHistogramName, 5);
  histogram_tester_.ExpectBucketCount(kLastUsageTimeHistogramName, 4, 1);

  task_environment_.AdvanceClock(base::Days(7));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kLastUsageTimeHistogramName, 6);
  histogram_tester_.ExpectBucketCount(kLastUsageTimeHistogramName, 5, 1);

  task_environment_.AdvanceClock(base::Days(33));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kLastUsageTimeHistogramName, 7);
  histogram_tester_.ExpectBucketCount(kLastUsageTimeHistogramName, 6, 1);

  task_environment_.AdvanceClock(base::Days(90));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kLastUsageTimeHistogramName, 8);
  histogram_tester_.ExpectBucketCount(kLastUsageTimeHistogramName, 6, 2);
}

TEST_F(QoraiNewsP3ATest, TestNewUserReturningFollowingDay) {
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kNewUserReturningHistogramName, 1);
  histogram_tester_.ExpectBucketCount(kNewUserReturningHistogramName, 0, 1);

  metrics_->RecordAtSessionStart();
  histogram_tester_.ExpectTotalCount(kNewUserReturningHistogramName, 2);
  histogram_tester_.ExpectBucketCount(kNewUserReturningHistogramName, 2, 1);

  task_environment_.AdvanceClock(base::Days(1));
  metrics_->RecordAtSessionStart();
  histogram_tester_.ExpectTotalCount(kNewUserReturningHistogramName, 3);
  histogram_tester_.ExpectBucketCount(kNewUserReturningHistogramName, 3, 1);

  task_environment_.AdvanceClock(base::Days(2));
  metrics_->RecordAtSessionStart();
  histogram_tester_.ExpectTotalCount(kNewUserReturningHistogramName, 4);
  histogram_tester_.ExpectBucketCount(kNewUserReturningHistogramName, 3, 2);

  task_environment_.AdvanceClock(base::Days(5));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kNewUserReturningHistogramName, 5);
  histogram_tester_.ExpectBucketCount(kNewUserReturningHistogramName, 1, 1);
}

TEST_F(QoraiNewsP3ATest, TestNewUserReturningNotFollowingDay) {
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kNewUserReturningHistogramName, 1);
  histogram_tester_.ExpectBucketCount(kNewUserReturningHistogramName, 0, 1);

  metrics_->RecordAtSessionStart();
  histogram_tester_.ExpectTotalCount(kNewUserReturningHistogramName, 2);
  histogram_tester_.ExpectBucketCount(kNewUserReturningHistogramName, 2, 1);

  task_environment_.AdvanceClock(base::Days(2));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kNewUserReturningHistogramName, 3);
  histogram_tester_.ExpectBucketCount(kNewUserReturningHistogramName, 2, 2);

  metrics_->RecordAtSessionStart();
  histogram_tester_.ExpectTotalCount(kNewUserReturningHistogramName, 4);
  histogram_tester_.ExpectBucketCount(kNewUserReturningHistogramName, 4, 1);

  task_environment_.AdvanceClock(base::Days(2));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kNewUserReturningHistogramName, 5);
  histogram_tester_.ExpectBucketCount(kNewUserReturningHistogramName, 4, 2);

  task_environment_.AdvanceClock(base::Days(4));
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kNewUserReturningHistogramName, 6);
  histogram_tester_.ExpectBucketCount(kNewUserReturningHistogramName, 1, 1);
}

TEST_F(QoraiNewsP3ATest, TestIsEnabled) {
  PrefService* prefs = GetPrefs();

  // should not record "disabled" if never opted in
  prefs->SetBoolean(::qorai_news::prefs::kNewTabPageShowToday, false);
  histogram_tester_.ExpectTotalCount(kIsEnabledHistogramName, 0);

  prefs->SetBoolean(::qorai_news::prefs::kQoraiNewsOptedIn, true);
  prefs->SetBoolean(::qorai_news::prefs::kNewTabPageShowToday, true);
  histogram_tester_.ExpectUniqueSample(kIsEnabledHistogramName, 1, 1);

  prefs->SetBoolean(::qorai_news::prefs::kNewTabPageShowToday, false);
  histogram_tester_.ExpectBucketCount(kIsEnabledHistogramName, 0, 1);
}

TEST_F(QoraiNewsP3ATest, TestGeneralUsage) {
  metrics_->RecordAtInit();
  histogram_tester_.ExpectTotalCount(kUsageDailyHistogramName, 0);
  histogram_tester_.ExpectTotalCount(kUsageMonthlyHistogramName, 0);

  metrics_->RecordAtSessionStart();
  histogram_tester_.ExpectUniqueSample(kUsageDailyHistogramName, 1, 1);
  histogram_tester_.ExpectUniqueSample(kUsageMonthlyHistogramName, 1, 1);
}

}  // namespace qorai_news::p3a
