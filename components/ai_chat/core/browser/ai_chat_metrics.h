/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_AI_CHAT_CORE_BROWSER_AI_CHAT_METRICS_H_
#define QORAI_COMPONENTS_AI_CHAT_CORE_BROWSER_AI_CHAT_METRICS_H_

#include <memory>
#include <optional>
#include <string>

#include "base/containers/flat_map.h"
#include "base/functional/callback.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/timer/timer.h"
#include "base/timer/wall_clock_timer.h"
#include "qorai/components/ai_chat/core/browser/ai_chat_tab_focus_metrics.h"
#include "qorai/components/ai_chat/core/common/mojom/ai_chat.mojom.h"
#include "qorai/components/ai_chat/core/common/mojom/common.mojom.h"
#include "qorai/components/time_period_storage/time_period_storage.h"
#include "qorai/components/time_period_storage/weekly_storage.h"
#include "build/build_config.h"
#include "mojo/public/cpp/bindings/receiver_set.h"

class PrefRegistrySimple;
class PrefService;

namespace ai_chat {

inline constexpr char kChatCountHistogramName[] = "Qorai.AIChat.ChatCount";
inline constexpr char kAvgPromptCountHistogramName[] =
    "Qorai.AIChat.AvgPromptCount";
inline constexpr char kEnabledHistogramName[] = "Qorai.AIChat.Enabled.2";
inline constexpr char kUsageDailyHistogramName[] = "Qorai.AIChat.UsageDaily.2";
inline constexpr char kUsageMonthlyHistogramName[] =
    "Qorai.AIChat.UsageMonthly";
inline constexpr char kUsageWeeklyHistogramName[] = "Qorai.AIChat.UsageWeekly";
inline constexpr char kOmniboxWeekCompareHistogramName[] =
    "Qorai.AIChat.OmniboxWeekCompare";
inline constexpr char kOmniboxOpensHistogramName[] =
    "Qorai.AIChat.OmniboxOpens";
inline constexpr char kAcquisitionSourceHistogramName[] =
    "Qorai.AIChat.AcquisitionSource";
inline constexpr char kNewUserReturningHistogramName[] =
    "Qorai.AIChat.NewUserReturning";
inline constexpr char kLastUsageTimeHistogramName[] =
    "Qorai.AIChat.LastUsageTime";
inline constexpr char kContextMenuLastUsageTimeHistogramName[] =
    "Qorai.AIChat.ContextMenu.LastUsageTime";
inline constexpr char kMostUsedContextMenuActionHistogramName[] =
    "Qorai.AIChat.ContextMenu.MostUsedAction";
inline constexpr char kContextMenuFreeUsageCountHistogramName[] =
    "Qorai.AIChat.ContextMenu.FreeUsages";
inline constexpr char kContextMenuPremiumUsageCountHistogramName[] =
    "Qorai.AIChat.ContextMenu.PremiumUsages";
inline constexpr char kEnabledSidebarEnabledAHistogramName[] =
    "Qorai.AIChat.Enabled.SidebarEnabledA";
inline constexpr char kEnabledSidebarEnabledBHistogramName[] =
    "Qorai.AIChat.Enabled.SidebarEnabledB";
inline constexpr char kUsageDailySidebarEnabledAHistogramName[] =
    "Qorai.AIChat.UsageDaily.SidebarEnabledA";
inline constexpr char kUsageDailySidebarEnabledBHistogramName[] =
    "Qorai.AIChat.UsageDaily.SidebarEnabledB";
inline constexpr char kUsageWeeklySidebarEnabledAHistogramName[] =
    "Qorai.AIChat.UsageWeekly.SidebarEnabledA";
inline constexpr char kUsageWeeklySidebarEnabledBHistogramName[] =
    "Qorai.AIChat.UsageWeekly.SidebarEnabledB";
inline constexpr char kChatCountNebulaHistogramName[] =
    "Qorai.AIChat.ChatCount.Nebula";
inline constexpr char kMostUsedEntryPointHistogramName[] =
    "Qorai.AIChat.MostUsedEntryPoint";
inline constexpr char kFirstChatPromptsHistogramName[] =
    "Qorai.AIChat.FirstChatPrompts";
inline constexpr char kChatHistoryUsageHistogramName[] =
    "Qorai.AIChat.ChatHistoryUsage";
inline constexpr char kMaxChatDurationHistogramName[] =
    "Qorai.AIChat.MaxChatDuration";
inline constexpr char kMostUsedContextSourceHistogramName[] =
    "Qorai.AIChat.MostUsedContextSource";
inline constexpr char kUsedConversationStarterHistogramName[] =
    "Qorai.AIChat.UsedConversationStarter";
inline constexpr char kFullPageSwitchesHistogramName[] =
    "Qorai.AIChat.FullPageSwitches";
inline constexpr char kRateLimitStopsHistogramName[] =
    "Qorai.AIChat.RateLimitStops";
inline constexpr char kContextLimitsHistogramName[] =
    "Qorai.AIChat.ContextLimits";

enum class EntryPoint {
  kOmniboxItem = 0,
  kSidebar = 1,
  kContextMenu = 2,
  kToolbarButton = 3,
  kMenuItem = 4,
  kOmniboxCommand = 5,
  kQoraiSearch = 6,
  kMaxValue = kQoraiSearch
};

enum class ContextMenuAction {
  kSummarize = 0,
  kExplain = 1,
  kParaphrase = 2,
  kCreateTagline = 3,
  kCreateSocialMedia = 4,
  kImprove = 5,
  kChangeTone = 6,
  kChangeLength = 7,
  kMaxValue = kChangeLength
};

enum class ContextSource {
  kOmniboxInput = 0,
  kConversationStarter = 1,
  kPageSummary = 2,
  kTextInputWithPage = 3,
  kTextInputWithoutPage = 4,
  kTextInputViaFullPage = 5,
  kQuickAction = 6,
  kMaxValue = kQuickAction
};

class ConversationHandlerForMetrics {
 public:
  virtual ~ConversationHandlerForMetrics() = default;
  virtual size_t GetConversationHistorySize() = 0;
  virtual bool should_send_page_contents() const = 0;
  virtual mojom::APIError current_error() const = 0;
};

class AIChatMetrics : public mojom::Metrics,
                      public AIChatTabFocusMetrics::Delegate {
 public:
  using RetrievePremiumStatusCallback =
      base::OnceCallback<void(mojom::Service::GetPremiumStatusCallback)>;

  AIChatMetrics(PrefService* local_state, PrefService* profile_prefs);
  ~AIChatMetrics() override;

  AIChatMetrics(const AIChatMetrics&) = delete;
  AIChatMetrics& operator=(const AIChatMetrics&) = delete;

  static void RegisterPrefs(PrefRegistrySimple* registry);

  void Bind(mojo::PendingReceiver<mojom::Metrics> receiver);

  AIChatTabFocusMetrics* tab_focus_metrics() {
    return tab_focus_metrics_.get();
  }

  void RecordEnabled(
      bool is_enabled,
      bool is_new_user,
      RetrievePremiumStatusCallback retrieve_premium_status_callback);
  void RecordReset();

  void RecordNewPrompt(ConversationHandlerForMetrics* handler,
                       mojom::ConversationPtr& conversation,
                       mojom::ConversationTurnPtr& entry);
  void RecordConversationUnload(std::string_view conversation_uuid);
  void RecordConversationsCleared();

#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
  void RecordOmniboxOpen();
  void RecordOmniboxSearchQuery();

  void RecordContextMenuUsage(ContextMenuAction action);
  void HandleOpenViaEntryPoint(EntryPoint entry_point);
  void RecordSidebarUsage();
  void RecordFullPageSwitch();
#endif  // !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)

  void OnPremiumStatusUpdated(bool is_enabled,
                              bool is_new_user,
                              mojom::PremiumStatus premium_status,
                              mojom::PremiumInfoPtr);
  void MaybeRecordLastError(ConversationHandlerForMetrics* handler);

  // Metrics:
  void OnSendingPromptWithFullPage() override;
  void OnQuickActionStatusChange(bool is_enabled) override;

  // AIChatTabFocusMetrics::Delegate:
  bool IsPremium() const override;

 private:
  void ReportAllMetrics();
  void ReportFeatureUsageMetrics();
  void ReportChatCounts();
  void ReportContextSource();
  void ReportFullPageUsage();
  void ReportLimitMetrics();
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
  void ReportOmniboxCounts();
  void ReportContextMenuMetrics();
  void ReportEntryPointUsageMetric();
  void ReportFullPageUsageMetric();
#endif  // !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)

  void MaybeReportFirstChatPrompts(bool new_prompt_made);
  void RecordContextSource(ConversationHandlerForMetrics* handler,
                           mojom::ConversationTurnPtr& entry);

  bool is_enabled_ = false;
  bool is_premium_ = false;
  bool premium_check_in_progress_ = false;
  bool prompted_via_omnibox_ = false;
  bool prompted_via_full_page_ = false;
  bool prompted_via_quick_action_ = false;
  std::optional<EntryPoint> acquisition_source_ = std::nullopt;

  WeeklyStorage chat_count_storage_;
  WeeklyStorage chat_with_history_count_storage_;
  WeeklyStorage chat_durations_storage_;
  WeeklyStorage prompt_count_storage_;
  WeeklyStorage rate_limit_storage_;
  WeeklyStorage context_limit_storage_;
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
  base::flat_map<ContextMenuAction, std::unique_ptr<WeeklyStorage>>
      context_menu_usage_storages_;

  TimePeriodStorage omnibox_open_storage_;
  TimePeriodStorage omnibox_autocomplete_storage_;

  base::flat_map<EntryPoint, std::unique_ptr<WeeklyStorage>>
      entry_point_storages_;
  WeeklyStorage sidebar_usage_storage_;
  WeeklyStorage full_page_switch_storage_;
#endif  // !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
  base::flat_map<ContextSource, std::unique_ptr<WeeklyStorage>>
      context_source_storages_;

  base::flat_map<std::string, base::Time> conversation_start_times_;

  base::OneShotTimer report_debounce_timer_;
  base::OneShotTimer first_chat_report_debounce_timer_;

  base::WallClockTimer periodic_report_timer_;

  raw_ptr<PrefService> local_state_;

  mojo::ReceiverSet<mojom::Metrics> receivers_;

  std::unique_ptr<AIChatTabFocusMetrics> tab_focus_metrics_;

  base::WeakPtrFactory<AIChatMetrics> weak_ptr_factory_{this};
};

}  // namespace ai_chat

#endif  // QORAI_COMPONENTS_AI_CHAT_CORE_BROWSER_AI_CHAT_METRICS_H_
