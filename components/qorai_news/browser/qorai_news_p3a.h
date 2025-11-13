// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_BROWSER_QORAI_NEWS_P3A_H_
#define QORAI_COMPONENTS_QORAI_NEWS_BROWSER_QORAI_NEWS_P3A_H_

#include "base/containers/flat_map.h"
#include "base/memory/raw_ptr.h"
#include "base/scoped_observation.h"
#include "base/timer/wall_clock_timer.h"
#include "qorai/components/qorai_news/browser/qorai_news_pref_manager.h"

class PrefService;

namespace qorai_news::p3a {

enum class ActionType { kCardView, kCardVisit, kSidebarFilterUsage };

enum class SubscribeType { kChannels, kPublishers };

inline constexpr char kWeeklySessionCountHistogramName[] =
    "Qorai.Today.WeeklySessionCount";
inline constexpr char kTotalCardViewsHistogramName[] =
    "Qorai.Today.WeeklyTotalCardViews";
inline constexpr char kRewardsAdsViewsHistogramName[] =
    "Qorai.Today.RewardsAdViews";
inline constexpr char kNonRewardsAdsViewsHistogramName[] =
    "Qorai.Today.NonRewardsAdViews";
inline constexpr char kDirectFeedsTotalHistogramName[] =
    "Qorai.Today.DirectFeedsTotal.3";
inline constexpr char kWeeklyAddedDirectFeedsHistogramName[] =
    "Qorai.Today.WeeklyAddedDirectFeedsCount";
inline constexpr char kLastUsageTimeHistogramName[] =
    "Qorai.Today.LastUsageTime";
inline constexpr char kNewUserReturningHistogramName[] =
    "Qorai.Today.NewUserReturning";
inline constexpr char kTotalCardClicksHistogramName[] =
    "Qorai.Today.WeeklyTotalCardClicks";
inline constexpr char kSidebarFilterUsageHistogramName[] =
    "Qorai.Today.SidebarFilterUsages";
inline constexpr char kClickCardDepthHistogramName[] =
    "Qorai.Today.ClickCardDepth";
inline constexpr char kChannelCountHistogramName[] =
    "Qorai.Today.ChannelCount.2";
inline constexpr char kPublisherCountHistogramName[] =
    "Qorai.Today.PublisherCount.2";
inline constexpr char kIsEnabledHistogramName[] = "Qorai.Today.IsEnabled";
inline constexpr char kEnabledSettingHistogramName[] =
    "Qorai.Today.EnabledSetting";
inline constexpr char kUsageMonthlyHistogramName[] = "Qorai.Today.UsageMonthly";
inline constexpr char kUsageDailyHistogramName[] = "Qorai.Today.UsageDaily";

class NewsMetrics : public QoraiNewsPrefManager::PrefObserver {
 public:
  NewsMetrics(PrefService* prefs, QoraiNewsPrefManager& pref_manager);
  ~NewsMetrics() override;

  NewsMetrics(const NewsMetrics&) = delete;
  NewsMetrics& operator=(const NewsMetrics&) = delete;

  void RecordAtInit();
  void RecordAtSessionStart();

  void RecordWeeklyDisplayAdsViewedCount(bool is_add);

  void RecordTotalActionCount(ActionType action, uint64_t count_delta);
  void RecordVisitCardDepth(uint32_t new_visit_card_depth);

  // QoraiNewsPrefManager::PrefObserver:
  void OnConfigChanged() override;
  void OnPublishersChanged() override;
  void OnChannelsChanged() override;

 private:
  // These are managed internally, by observing prefs.
  void RecordFeatureEnabledChange();
  void RecordTotalSubscribedCount(SubscribeType subscribe_type,
                                  std::optional<size_t> total);
  void RecordDirectFeedsTotal();
  void RecordWeeklyAddedDirectFeedsCount(int change);

  uint64_t AddToWeeklyStorageAndGetSum(const char* pref_name, int change);
  bool IsMonthlyActiveUser();
  void RecordLastUsageTime();
  void RecordNewUserReturning();
  void RecordWeeklySessionCount(bool is_add);

  raw_ptr<PrefService> prefs_;
  raw_ref<QoraiNewsPrefManager> pref_manager_;
  bool was_enabled_ = false;
  uint32_t direct_feed_count_ = 0;

  base::WallClockTimer report_timer_;
  base::flat_map<SubscribeType, size_t> subscription_counts_;

  base::ScopedObservation<QoraiNewsPrefManager,
                          QoraiNewsPrefManager::PrefObserver>
      observation_{this};
};

}  // namespace qorai_news::p3a

#endif  // QORAI_COMPONENTS_QORAI_NEWS_BROWSER_QORAI_NEWS_P3A_H_
