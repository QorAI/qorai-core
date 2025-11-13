/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_REWARDS_P3A_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_REWARDS_P3A_H_

#include <optional>

#include "base/memory/raw_ptr.h"
#include "base/time/time.h"
#include "base/timer/wall_clock_timer.h"
#include "qorai/components/time_period_storage/weekly_storage.h"

class PrefService;

namespace qorai_rewards {
namespace p3a {

inline constexpr char kEnabledSourceHistogramName[] =
    "Qorai.Rewards.EnabledSource";
inline constexpr char kToolbarButtonTriggerHistogramName[] =
    "Qorai.Rewards.ToolbarButtonTrigger";
inline constexpr char kTipsSentHistogramName[] = "Qorai.Rewards.TipsSent.2";
inline constexpr char kRecurringTipHistogramName[] =
    "Qorai.Rewards.RecurringTip";
inline constexpr char kAutoContributionsStateHistogramName[] =
    "Qorai.Rewards.AutoContributionsState.3";
inline constexpr char kAdTypesEnabledHistogramName[] =
    "Qorai.Rewards.AdTypesEnabled.2";
inline constexpr char kSearchResultAdsOptinHistogramName[] =
    "Qorai.Rewards.SearchResultAdsOptin";
inline constexpr char kAdsHistoryViewHistogramName[] =
    "Qorai.Rewards.AdsHistoryView";
inline constexpr char kMobileConversionHistogramName[] =
    "Qorai.Rewards.MobileConversion";
#if BUILDFLAG(IS_ANDROID)
inline constexpr char kPanelCountHistogramName[] =
    "Qorai.Rewards.MobilePanelCount.2";
#else
inline constexpr char kPanelCountHistogramName[] =
    "Qorai.Rewards.DesktopPanelCount.2";
#endif
inline constexpr char kPageViewCountHistogramName[] =
    "Qorai.Rewards.PageViewCount";
inline constexpr char kOfferClicksHistogramName[] = "Qorai.Rewards.OfferClicks";
inline constexpr char kOffersViewedHistogramName[] =
    "Qorai.Rewards.OffersViewed";

enum class AutoContributionsState {
  kNoWallet,
  kRewardsDisabled,
  kWalletCreatedAutoContributeOff,
  kAutoContributeOn,
};

enum class PanelTrigger {
  kInlineTip = 0,  // DEPRECATED
  kToolbarButton = 1,
  kNTP = 2,
  kMaxValue = kNTP
};

void RecordTipsSent(size_t tip_count);

void RecordRecurringTipConfigured(bool tip_configured);

void RecordAutoContributionsState(bool ac_enabled);

void RecordNoWalletCreatedForAllMetrics();

void RecordRewardsPageViews(PrefService* prefs, bool new_view);

void RecordAdTypesEnabled(PrefService* prefs);

void RecordSearchResultAdsOptinChange(PrefService* prefs);

void RecordAdsHistoryView();

void RecordOfferView(PrefService* prefs);
void RecordOfferClicks(PrefService* prefs, bool new_click);

class ConversionMonitor {
 public:
  explicit ConversionMonitor(PrefService* prefs);
  ~ConversionMonitor();

  ConversionMonitor(const ConversionMonitor&) = delete;
  ConversionMonitor& operator=(const ConversionMonitor&) = delete;

  // Record trigger of an action that could potentially trigger opening the
  // Rewards panel. Will immediately record the action (if applicable).
  void RecordPanelTrigger(PanelTrigger trigger);

  // Record the enabled of rewards, which may record a metric containing the
  // source of user conversion a.k.a. the action that opened the Rewards panel.
  void RecordRewardsEnable();

 private:
  void ReportPeriodicMetrics();
  void ReportPanelTriggerCount();
#if BUILDFLAG(IS_ANDROID)
  void OnMobileTriggerTimer();

  base::OneShotTimer mobile_trigger_timer_;
#else
  std::optional<PanelTrigger> last_trigger_;
  base::Time last_trigger_time_;
#endif
  raw_ptr<PrefService> prefs_;
  base::WallClockTimer daily_timer_;
  WeeklyStorage panel_trigger_count_;
};

}  // namespace p3a
}  // namespace qorai_rewards

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_REWARDS_P3A_H_
