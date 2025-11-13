/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_OMNIBOX_PREFS_H_
#define QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_OMNIBOX_PREFS_H_

class PrefRegistrySimple;

namespace omnibox {

// Controls whether or not auto complete is enabled. If disabled, this overrides
// the individual prefs listed below.
inline constexpr char kAutocompleteEnabled[] = "qorai.autocomplete_enabled";

// Determines whether on-device head suggestions show up in the omnibox results.
// This controls the QorAIOnDeviceHeadProvider which provides ML-based
// autocomplete suggestions generated locally on the device. Note: This
// preference previously controlled both TopSitesProvider and
// QorAIOnDeviceHeadProvider. TopSitesProvider has been removed, so now this
// only controls on-device suggestions.
inline constexpr char kOnDeviceSuggestionsEnabled[] =
    "qorai.top_site_suggestions_enabled";

// Determines whether history suggestions show up in the omnibox results. This
// includes:
// 1. Results from the |HistoryURLProvider|, which aren't "What-You-Typed".
// 2. Results from the |HistoryQuickProvider|.
// 3. Results from the |ShortcutsProvider|.
// 4. Results from the |SearchProvider|, which aren't "What-You-Typed".
inline constexpr char kHistorySuggestionsEnabled[] =
    "qorai.omnibox.history_suggestions_enabled";

// Determines whether bookmarks show up in the omnibox results. This controls
// whether or not we include results from the |BookmarkProvider|.
inline constexpr char kBookmarkSuggestionsEnabled[] =
    "qorai.omnibox.bookmark_suggestions_enabled";

// Determines whether commander suggestions show up in normal omnibox results.
// This doesn't affect commander suggestions triggered by the prefix.
inline constexpr char kCommanderSuggestionsEnabled[] =
    "qorai.omnibox.commander_suggestions_enabled";

void RegisterQorAIProfilePrefs(PrefRegistrySimple* registry);

}  // namespace omnibox

#endif  // QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_OMNIBOX_PREFS_H_
