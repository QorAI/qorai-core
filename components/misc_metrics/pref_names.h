/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_MISC_METRICS_PREF_NAMES_H_
#define QORAI_COMPONENTS_MISC_METRICS_PREF_NAMES_H_

namespace misc_metrics {
inline constexpr char kMiscMetricsBrowserUsageList[] =
    "qorai.misc_metrics.browser_usage";
inline constexpr char kMiscMetricsMenuDismissStorage[] =
    "qorai.misc_metrics.menu_dismiss_storage";
inline constexpr char kMiscMetricsMenuGroupActionCounts[] =
    "qorai.misc_metrics.menu_group_actions";
inline constexpr char kMiscMetricsMenuShownStorage[] =
    "qorai.misc_metrics.menu_shown_storage";
inline constexpr char kMiscMetricsPagesLoadedCount[] =
    "qorai.core_metrics.pages_loaded";
inline constexpr char kMiscMetricsPagesReloadedCount[] =
    "qorai.core_metrics.pages_reloaded";
inline constexpr char kMiscMetricsInterstitialAllowDecisionCount[] =
    "qorai.misc_metrics.interstitial_allow_decisions";
inline constexpr char kMiscMetricsFailedHTTPSUpgradeCount[] =
    "qorai.misc_metrics.failed_https_upgrades";
inline constexpr char kMiscMetricsFailedHTTPSUpgradeMetricAddedTime[] =
    "qorai.misc_metrics.failed_https_upgrade_metric_added_time";
inline constexpr char kMiscMetricsPrivacyHubViews[] =
    "qorai.misc_metrics.privacy_hub_views";
inline constexpr char kMiscMetricsOpenTabsStorage[] =
    "qorai.misc_metrics.open_tabs_storage";
inline constexpr char kMiscMetricsGroupTabsStorage[] =
    "qorai.misc_metrics.group_tabs_storage";
inline constexpr char kMiscMetricsPinnedTabsStorage[] =
    "qorai.misc_metrics.pinned_tabs_storage";

inline constexpr char kMiscMetricsSearchSwitchedAwayFromQorai[] =
    "qorai.misc_metrics.search_switched_from_qorai";
inline constexpr char kMiscMetricsSearchQoraiQueryCount[] =
    "qorai.misc_metrics.search_qorai_query_count";

inline constexpr char kMiscMetricsTotalDnsRequestStorage[] =
    "qorai.misc_metrics.total_dns_requests";
inline constexpr char kMiscMetricsUpgradedDnsRequestStorage[] =
    "qorai.misc_metrics.upgraded_dns_requests";
inline constexpr char kMiscMetricsLastDohFallback[] =
    "qorai.misc_metrics.last_doh_fallback";

inline constexpr char kDailyUptimesListPrefName[] =
    "daily_uptimes";  // DEPRECATED
inline constexpr char kDailyUptimeSumPrefName[] =
    "qorai.misc_metrics.uptime_sum";
inline constexpr char kDailyUptimeFrameStartTimePrefName[] =
    "qorai.misc_metrics.uptime_frame_start_time_v2";
inline constexpr char kWeeklyUptimeStoragePrefName[] =
    "qorai.misc_metrics.weekly_uptime_storage";

inline constexpr char kMiscMetricsTabSwitcherNewTabsStorage[] =
    "qorai.misc_metrics.tab_switcher_new_tabs_storage";
inline constexpr char kMiscMetricsTotalNewTabsStorage[] =
    "qorai.misc_metrics.total_new_tabs_storage";
inline constexpr char kMiscMetricsNewTabLocationBarEntriesStorage[] =
    "qorai.misc_metrics.new_tab_location_bar_entries_storage";
inline constexpr char kMiscMetricsTotalLocationBarEntriesStorage[] =
    "qorai.misc_metrics.total_location_bar_entries_storage";

inline constexpr char kMiscMetricsDayZeroVariantAtInstall[] =
    "qorai.misc_metrics.day_zero_variant_at_install";
inline constexpr char kMiscMetricsLastDayZeroReport[] =
    "qorai.misc_metrics.last_day_zero_report";

inline constexpr char kMiscMetricsNTPWidgetUsageStorage[] =
    "qorai.misc_metrics.ntp_widget_usage";

inline constexpr char kMiscMetricsSplitViewUsageStorage[] =
    "qorai.misc_metrics.split_view_usage";

}  // namespace misc_metrics

#endif  // QORAI_COMPONENTS_MISC_METRICS_PREF_NAMES_H_
