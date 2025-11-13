// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_PREFS_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_PREFS_H_

#include "build/build_config.h"

namespace qorai_search {
namespace prefs {

inline constexpr char kDailyAsked[] = "qorai.qorai_search.daily_asked";
inline constexpr char kTotalAsked[] = "qorai.qorai_search.total_asked";
#if BUILDFLAG(IS_ANDROID)
inline constexpr char kFetchFromNative[] =
    "qorai.qorai_search.fetch_se_from_native";
#endif

inline constexpr char kBackupResultsLastQueryTime[] =
    "qorai.search.backup_results.last_query_time";
inline constexpr char kBackupResultsFailuresStorage[] =
    "qorai.search.backup_results.failures_storage";

}  // namespace prefs
}  // namespace qorai_search

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_PREFS_H_
