/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_PREF_NAMES_H_

class PrefService;

namespace qorai_search_conversion::prefs {

inline constexpr char kDismissed[] = "qorai.qorai_search_conversion.dismissed";
inline constexpr char kMaybeLaterClickedTime[] =
    "qorai.qorai_search_conversion.maybe_later_clicked_time";

// Index ranges from 0 to 1 and it's matched DDGTypeC to DDGTypeD.
// It's the type index for now.
inline constexpr char kDDGBannerTypeIndex[] =
    "qorai.qorai_search_conversion.ddg_banner_type_index";

// It's the time that current index type is shown first.
// We rotate 4 types when specific time is passed.
inline constexpr char kLatestDDGBannerTypeFirstShownTime[] =
    "qorai.qorai_search_conversion.latest_ddg_banner_type_first_shown_time";

inline constexpr char kShowNTPSearchBox[] =
    "qorai.qorai_search.show-ntp-search";

inline constexpr char kLastUsedNTPSearchEngine[] =
    "qorai.qorai_search.last-used-ntp-search-engine";

// Determines whether the search box on the NTP prompts the user to enable
// search suggestions.
inline constexpr char kPromptEnableSuggestions[] =
    "qorai.qorai_search.ntp-search_prompt_enable_suggestions";

inline constexpr char kP3AActionStatuses[] =
    "qorai.qorai_search_conversion.action_statuses";

inline constexpr char kP3ADefaultEngineConverted[] =
    "qorai.qorai_search_conversion.default_changed";
inline constexpr char kP3AQueryCountBeforeChurn[] =
    "qorai.qorai_search_conversion.query_count";
inline constexpr char kP3AAlreadyChurned[] =
    "qorai.qorai_search_conversion.already_churned";

inline constexpr char kP3ABannerShown[] =
    "qorai.qorai_search_conversion.banner_shown";  // DEPRECATED
inline constexpr char kP3ABannerTriggered[] =
    "qorai.qorai_search_conversion.banner_triggered";  // DEPRECATED
inline constexpr char kP3AButtonShown[] =
    "qorai.qorai_search_conversion.button_shown";  // DEPRECATED
inline constexpr char kP3ANTPShown[] =
    "qorai.qorai_search_conversion.ntp_shown";  // DEPRECATED
inline constexpr char kP3AButtonTriggered[] =
    "qorai.qorai_search_conversion.button_triggered";  // DEPRECATED
inline constexpr char kP3ANTPTriggered[] =
    "qorai.qorai_search_conversion.ntp_triggered";  // DEPRECATED

}  // namespace qorai_search_conversion::prefs

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_PREF_NAMES_H_
