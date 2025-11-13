/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_P3A_METRIC_NAMES_H_
#define QORAI_COMPONENTS_P3A_METRIC_NAMES_H_

#include <string_view>

#include "base/containers/fixed_flat_map.h"
#include "qorai/components/p3a/metric_config.h"

namespace p3a {

// Allowlist for histograms that we collect.
// A metric must be listed here to be reported.
//
// Please keep them properly sorted within their categories.
//
// Could be replaced with something built dynamically,
// although so far we've found it a useful review point.
//
// TODO(iefremov) Clean up obsolete metrics.
//
// clang-format off
inline constexpr auto kCollectedTypicalHistograms =
  base::MakeFixedFlatMap<std::string_view, std::optional<MetricConfig>>({
    {"Qorai.AIChat.AcquisitionSource", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.AvgPromptCount", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.ChatCount", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.ChatCount.Nebula", MetricConfig{.ephemeral = true,.nebula = true}},
    {"Qorai.AIChat.ChatHistoryUsage", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.ContextLimits", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.ContextMenu.FreeUsages", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.ContextMenu.MostUsedAction", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.ContextMenu.PremiumUsages", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.Enabled.2", {}},
    {"Qorai.AIChat.FirstChatPrompts", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.FullPageSwitches", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.MaxChatDuration", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.MostUsedContextSource", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.MostUsedEntryPoint", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.NewUserReturning", {}},
    {"Qorai.AIChat.OmniboxOpens", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.OmniboxWeekCompare", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.RateLimitStops", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.TabFocus.AvgTabCount", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.TabFocus.Enabled", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.TabFocus.MaxTabCount", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.TabFocus.SessionCount", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.TabFocus.LastUsageTime", MetricConfig{.ephemeral = true,.nebula = true}},
    {"Qorai.AIChat.UsageWeekly", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.UsedConversationStarter", {}},
    {"Qorai.Ads.ClearData", MetricConfig{.ephemeral = true}},
    {"Qorai.Core.BookmarkCount", {}},
    {"Qorai.Core.CrashReportsEnabled", {}},
    {"Qorai.Core.DomainsLoaded", {}},
    {"Qorai.Core.FailedHTTPSUpgrades.2", MetricConfig{.ephemeral = true}},
    {"Qorai.Core.FirstPageLoadTime", MetricConfig{.ephemeral = true}},
    {"Qorai.Core.IsDefault", MetricConfig{
      .attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kChannel, MetricAttribute::kGeneralPlatform, MetricAttribute::kYoi, MetricAttribute::kSubregion, MetricAttribute::kVersion, MetricAttribute::kWoi},
    }},
    {"Qorai.Core.NumberOfExtensions", {}},
    {"Qorai.Core.PagesLoaded.NonRewards", {}},
    {"Qorai.Core.PagesLoaded.Rewards", {}},
    {"Qorai.Core.PagesLoaded.RewardsWallet", {}},
    {"Qorai.Core.PagesReloaded", {}},
    {"Qorai.Core.TabCount", {}},
    {"Qorai.Core.WeeklyUsage", {}},
    {"Qorai.Core.WeeklyUsage.Nebula", MetricConfig{.nebula = true}},
    {"Qorai.Core.WindowCount.2", {}},
    {"Qorai.DNS.AutoSecureRequests.2", MetricConfig{.ephemeral = true}},
    {"Qorai.DNS.AutoSecureRequests.Cloudflare.2", MetricConfig{.ephemeral = true}},
    {"Qorai.DNS.AutoSecureRequests.Quad9.2", MetricConfig{.ephemeral = true}},
    {"Qorai.DNS.AutoSecureRequests.Wikimedia.2", MetricConfig{.ephemeral = true}},
    {"Qorai.DNS.SecureSetting", {}},
    {"Qorai.Extensions.AdBlock", {}},
    {"Qorai.Extensions.SelectManifestV2", {}},
    {"Qorai.IOS.IsLikelyDefault", MetricConfig{
      .attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kChannel, MetricAttribute::kYoi, MetricAttribute::kWoi, MetricAttribute::kWeekOfActivation, MetricAttribute::kSubregion, MetricAttribute::kVersion},
      .record_activation_date = true,
    }},
    {"Qorai.Importer.ImporterSource.2", {}},
    {"Qorai.NTP.CustomizeUsageStatus.2", {}},
    {"Qorai.NTP.DefaultPage", {}},
    {"Qorai.NTP.NewTabsCreated.3", {}},
    {"Qorai.NTP.SponsoredMediaType", {}},
    {"Qorai.Omnibox.SearchCount.NonRewards", {}},
    {"Qorai.Omnibox.SearchCount.Rewards", {}},
    {"Qorai.Omnibox.SearchCount.RewardsWallet", {}},
    {"Qorai.PermissionLifetime.7Days", MetricConfig{.ephemeral = true}},
    {"Qorai.P3A.SentAnswersCount", {}},
    {"Qorai.Playlist.FirstTimeOffset", MetricConfig{.ephemeral = true}},
    {"Qorai.Playlist.NewUserReturning", {}},
    {"Qorai.Playlist.UsageDaysInWeek", MetricConfig{.ephemeral = true}},
    {"Qorai.Rewards.AdTypesEnabled.2", {}},
    {"Qorai.Rewards.DesktopPanelCount.2", MetricConfig{.ephemeral = true}},
    {"Qorai.Rewards.EnabledSource", MetricConfig{.ephemeral = true}},
    {"Qorai.Rewards.MobileConversion", MetricConfig{.ephemeral = true}},
    {"Qorai.Rewards.MobilePanelCount.2", MetricConfig{.ephemeral = true}},
    {"Qorai.Rewards.OfferClicks", MetricConfig{.ephemeral = true}},
    {"Qorai.Rewards.OffersViewed", MetricConfig{.ephemeral = true}},
    {"Qorai.Rewards.SearchResultAdsOptin", MetricConfig{.ephemeral = true}},
    {"Qorai.Rewards.TipsState.2", {}},
    {"Qorai.Rewards.ToolbarButtonTrigger", MetricConfig{.ephemeral = true}},
    {"Qorai.Rewards.WalletBalance.3", {}},
    {"Qorai.Rewards.WalletState", {}},
    {"Qorai.Search.GoogleWidgetUsage", MetricConfig{.ephemeral = true}},
    {"Qorai.Search.Promo.BannerB", {}},
    {"Qorai.Search.Promo.BannerC", {}},
    {"Qorai.Search.Promo.BannerD", {}},
    {"Qorai.Search.Promo.Button", {}},
    {"Qorai.Search.Promo.DDGBannerA", {}},
    {"Qorai.Search.Promo.DDGBannerB", {}},
    {"Qorai.Search.Promo.DDGBannerC", {}},
    {"Qorai.Search.Promo.DDGBannerD", {}},
    {"Qorai.Search.Promo.NewTabPage", {}},
    {"Qorai.Search.QueriesBeforeChurn", MetricConfig{.ephemeral = true}},
    {"Qorai.Search.WebDiscoveryAndAds", {}},
    {"Qorai.Search.WebDiscoveryDefaultEngine", {}},
    {"Qorai.Search.WidgetDefault", {}},
    {"Qorai.Search.WidgetUsage", MetricConfig{.ephemeral = true}},
    {"Qorai.Shields.AdBlockSetting", {}},
    {"Qorai.Shields.DomainAdsSettingsAboveGlobal", {}},
    {"Qorai.Shields.DomainAdsSettingsBelowGlobal", {}},
    {"Qorai.Shields.FingerprintBlockSetting", {}},
    {"Qorai.Shields.UsageStatus", {}},
    {"Qorai.Sidebar.Enabled", {}},
    {"Qorai.Sync.JoinType", MetricConfig{.ephemeral = true}},
    {"Qorai.Sync.Status.2", {}},
    {"Qorai.Today.ClickCardDepth", MetricConfig{.ephemeral = true}},
    {"Qorai.Today.LastUsageTime", {}},
    {"Qorai.Today.NewUserReturning", {}},
    {"Qorai.Today.NonRewardsAdViews", {}},
    {"Qorai.Today.RewardsAdViews", {}},
    {"Qorai.Today.SidebarFilterUsages", MetricConfig{.ephemeral = true}},
    {"Qorai.Today.WeeklySessionCount", {}},
    {"Qorai.Today.WeeklyTotalCardClicks", MetricConfig{.ephemeral = true}},
    {"Qorai.Today.WeeklyTotalCardViews", {}},
    {"Qorai.Update.Status", {}},
    {"Qorai.VPN.ConnectedDuration", MetricConfig{.ephemeral = true}},
    {"Qorai.VPN.HideWidget", MetricConfig{.ephemeral = true}},
    {"Qorai.VPN.LastUsageTime", MetricConfig{.record_activation_date = true}},
    {"Qorai.VPN.NewUserReturning", MetricConfig{
      .attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kDateOfActivation, MetricAttribute::kDateOfInstall, MetricAttribute::kVersion, MetricAttribute::kChannel, MetricAttribute::kPlatform, MetricAttribute::kCountryCode},
      .activation_metric_name = "Qorai.VPN.LastUsageTime"
    }},
    {"Qorai.VPN.WidgetUsage", MetricConfig{.ephemeral = true}},
    {"Qorai.VerticalTabs.GroupTabs", MetricConfig{.ephemeral = true}},
    {"Qorai.VerticalTabs.OpenTabs", MetricConfig{.ephemeral = true}},
    {"Qorai.VerticalTabs.PinnedTabs", MetricConfig{.ephemeral = true}},
    {"Qorai.Wallet.ActiveBtcAccounts", {}},
    {"Qorai.Wallet.ActiveEthAccounts", {}},
    {"Qorai.Wallet.ActiveSolAccounts", {}},
    {"Qorai.Wallet.ActiveZecAccounts", {}},
    {"Qorai.Wallet.BtcTransactionSent", {}},
    {"Qorai.Wallet.EthTransactionSent", {}},
    {"Qorai.Wallet.NFTCount", MetricConfig{.ephemeral = true}},
    {"Qorai.Wallet.NewUserReturning", {}},
    {"Qorai.Wallet.OnboardingConversion.3", MetricConfig{.ephemeral = true}},
    {"Qorai.Wallet.SolTransactionSent", {}},
    {"Qorai.Wallet.ZecTransactionSent", {}},
    {"Qorai.WebTorrent.UsageWeekly", MetricConfig{.ephemeral = true}},
});

inline constexpr auto kCollectedSlowHistograms =
  base::MakeFixedFlatMap<std::string_view, std::optional<MetricConfig>>({
    {"Qorai.AIChat.ContextMenu.LastUsageTime", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.LastUsageTime", MetricConfig{.ephemeral = true}},
    {"Qorai.AIChat.UsageMonthly", MetricConfig{.ephemeral = true}},
    {"Qorai.Core.PrimaryLang", MetricConfig{}},
    {"Qorai.Core.ProfileCount", {}},
    {"Qorai.Core.UsageMonthly", {}},
    {"Qorai.Extensions.ManifestV2", {}},
    {"Qorai.P3A.TestSlowMetric", {}},
    {"Qorai.Playlist.LastUsageTime", {}},
    {"Qorai.Rewards.PageViewCount", MetricConfig{.ephemeral = true}},
    {"Qorai.Rewards.RecurringTip", MetricConfig{.ephemeral = true}},
    {"Qorai.Rewards.TipsSent.2", MetricConfig{.ephemeral = true}},
    {"Qorai.Search.SearchSuggest", {}},
    {"Qorai.Shields.ForgetFirstParty", {}},
    {"Qorai.Speedreader.EnabledSites", {}},
    {"Qorai.Speedreader.PageViews", MetricConfig{.ephemeral = true}},
    {"Qorai.SplitView.UsageMonthly", {}},
    {"Qorai.Sync.EnabledTypes", {}},
    {"Qorai.Sync.SyncedObjectsCount.2", {}},
    {"Qorai.Today.ChannelCount.2", MetricConfig{.ephemeral = true}},
    {"Qorai.Today.DirectFeedsTotal.3", MetricConfig{.ephemeral = true}},
    {"Qorai.Today.PublisherCount.2", MetricConfig{.ephemeral = true}},
    {"Qorai.Today.UsageMonthly", MetricConfig{.ephemeral = true}},
    {"Qorai.Wallet.UsageMonthly", MetricConfig{.ephemeral = true}},
});

inline constexpr auto kCollectedExpressHistograms =
  base::MakeFixedFlatMap<std::string_view, std::optional<MetricConfig>>({
    {"Qorai.Ads.SurveyPanelistEnabled", {}},
    {"Qorai.AIChat.UsageDaily.2", MetricConfig{
      .ephemeral = true,
      .attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kDateOfActivation, MetricAttribute::kVersion, MetricAttribute::kYoi, MetricAttribute::kChannel, MetricAttribute::kPlatform, MetricAttribute::kCountryCode, MetricAttribute::kWoi},
      .record_activation_date = true,
    }},
    {"Qorai.Core.IsDefaultDaily", MetricConfig{
      .attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kChannel, MetricAttribute::kDateOfInstall, MetricAttribute::kDateOfActivation, MetricAttribute::kGeneralPlatform, MetricAttribute::kSubregion, MetricAttribute::kVersion},
      .record_activation_date = true,
    }},
    {"Qorai.Core.UsageDaily", {}},
    {"Qorai.DayZero.Variant", MetricConfig{
      .ephemeral = true,
      .attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kDateOfInstall, MetricAttribute::kVersion, MetricAttribute::kChannel, MetricAttribute::kPlatform, MetricAttribute::kCountryCode, MetricAttribute::kRef}
    }},
    {"Qorai.PermissionLifetime.24Hours", MetricConfig{.ephemeral = true}},
    {"Qorai.Rewards.EnabledInstallationTime", MetricConfig{.ephemeral = true}},
    {"Qorai.Search.BackupResultsFailures", MetricConfig{
      .ephemeral = true,
      .attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kVersion, MetricAttribute::kChannel, MetricAttribute::kPlatform, MetricAttribute::kCountryCode},
    }},
    {"Qorai.Search.QoraiDaily", MetricConfig{.ephemeral = true}},
    {"Qorai.Search.DefaultEngine.4", MetricConfig{
      .attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kChannel, MetricAttribute::kPlatform, MetricAttribute::kDateOfInstall, MetricAttribute::kVersion, MetricAttribute::kLocaleCountryCode},
    }},
    {"Qorai.Search.SwitchEngine.2", MetricConfig{
      .attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kChannel, MetricAttribute::kPlatform, MetricAttribute::kDateOfInstall, MetricAttribute::kVersion, MetricAttribute::kLocaleCountryCode},
    }},
    {"Qorai.Search.WebDiscoveryEnabled", {}},
    {"Qorai.Today.EnabledSetting", MetricConfig{.attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kDateOfActivation, MetricAttribute::kDateOfInstall, MetricAttribute::kVersion, MetricAttribute::kChannel, MetricAttribute::kPlatform, MetricAttribute::kCountryCode}}},
    {"Qorai.Today.IsEnabled", MetricConfig{
      .ephemeral = true,
      .attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kDateOfActivation, MetricAttribute::kDateOfInstall, MetricAttribute::kVersion, MetricAttribute::kChannel, MetricAttribute::kPlatform, MetricAttribute::kCountryCode},
      .activation_metric_name = "Qorai.Today.UsageDaily"
    }},
    {"Qorai.Today.UsageDaily", MetricConfig{
      .ephemeral = true,
      .attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kDateOfActivation, MetricAttribute::kVersion, MetricAttribute::kYoi, MetricAttribute::kChannel, MetricAttribute::kPlatform, MetricAttribute::kCountryCode, MetricAttribute::kWoi},
      .record_activation_date = true
    }},
    {"Qorai.Uptime.BrowserOpenTime.2", MetricConfig{.ephemeral = true}},
    {"Qorai.Welcome.InteractionStatus.2", MetricConfig{
      .attributes = MetricAttributes{MetricAttribute::kAnswerIndex, MetricAttribute::kChannel, MetricAttribute::kPlatform, MetricAttribute::kDateOfInstall, MetricAttribute::kSubregion, MetricAttribute::kVersion},
    }},
    {"creativeInstanceId.total.count", {}},
});

}  // namespace p3a

// clang-format on

#endif  // QORAI_COMPONENTS_P3A_METRIC_NAMES_H_
