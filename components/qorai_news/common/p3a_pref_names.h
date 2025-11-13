// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_COMMON_P3A_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_NEWS_COMMON_P3A_PREF_NAMES_H_

class PrefService;
class PrefRegistrySimple;

namespace qorai_news::p3a::prefs {

inline constexpr char kQoraiNewsWeeklySessionCount[] =
    "qorai.today.p3a_weekly_session_count";
inline constexpr char kQoraiNewsWeeklyDisplayAdViewedCount[] =
    "qorai.today.p3a_weekly_display_ad_viewed_count";
inline constexpr char kQoraiNewsWeeklyAddedDirectFeedsCount[] =
    "qorai.today.p3a_weekly_added_direct_feeds_count";
inline constexpr char kQoraiNewsTotalCardViews[] =
    "qorai.today.p3a_total_card_views";
inline constexpr char kQoraiNewsTotalCardVisits[] =
    "qorai.today.p3a_total_card_visits";
inline constexpr char kQoraiNewsVisitDepthSum[] =
    "qorai.today.p3a_card_visit_depth_sum";
inline constexpr char kQoraiNewsTotalSidebarFilterUsages[] =
    "qorai.today.p3a_total_sidebar_filter_usages";
inline constexpr char kQoraiNewsFirstSessionTime[] =
    "qorai.today.p3a_first_session_time";
inline constexpr char kQoraiNewsUsedSecondDay[] =
    "qorai.today.p3a_used_second_day";
inline constexpr char kQoraiNewsLastSessionTime[] =
    "qorai.today.p3a_last_session_time";
inline constexpr char kQoraiNewsWasEverEnabled[] =
    "qorai.today.p3a_was_ever_enabled";

void RegisterProfileNewsMetricsPrefs(PrefRegistrySimple* registry);
void RegisterProfileNewsMetricsPrefsForMigration(PrefRegistrySimple* registry);
void MigrateObsoleteProfileNewsMetricsPrefs(PrefService* prefs);

}  // namespace qorai_news::p3a::prefs

#endif  // QORAI_COMPONENTS_QORAI_NEWS_COMMON_P3A_PREF_NAMES_H_
