// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_COMMON_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_NEWS_COMMON_PREF_NAMES_H_

class PrefService;
class PrefRegistrySimple;

namespace qorai_news {
namespace prefs {

inline constexpr char kNewTabPageShowToday[] =
    "qorai.new_tab_page.show_qorai_news";
inline constexpr char kQoraiNewsSources[] = "qorai.today.sources";
inline constexpr char kQoraiNewsChannels[] = "qorai.news.channels";
inline constexpr char kQoraiNewsDirectFeeds[] = "qorai.today.userfeeds";
inline constexpr char kQoraiNewsIntroDismissed[] =
    "qorai.today.intro_dismissed";
inline constexpr char kQoraiNewsOptedIn[] = "qorai.today.opted_in";
inline constexpr char kShouldShowToolbarButton[] =
    "qorai.today.should_show_toolbar_button";
inline constexpr char kQoraiNewsOpenArticlesInNewTab[] =
    "qorai.news.open-articles-in-new-tab";

// Used to enable/disable Qorai News via a policy.
inline constexpr char kQoraiNewsDisabledByPolicy[] =
    "qorai.news.disabled_by_policy";

// Dictionary value keys
inline constexpr char kQoraiNewsDirectFeedsKeyTitle[] = "title";
inline constexpr char kQoraiNewsDirectFeedsKeySource[] = "source";

void RegisterProfilePrefs(PrefRegistrySimple* registry);

}  // namespace prefs

bool IsEnabled(PrefService* prefs);

}  // namespace qorai_news

#endif  // QORAI_COMPONENTS_QORAI_NEWS_COMMON_PREF_NAMES_H_
