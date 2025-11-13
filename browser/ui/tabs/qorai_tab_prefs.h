/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_TABS_QORAI_TAB_PREFS_H_
#define QORAI_BROWSER_UI_TABS_QORAI_TAB_PREFS_H_

class PrefRegistrySimple;
class PrefService;

namespace qorai_tabs {

enum TabHoverMode { TOOLTIP = 0, CARD = 1, CARD_WITH_PREVIEW = 2 };

inline constexpr char kTabHoverMode[] = "qorai.tabs.hover_mode";

inline constexpr char kVerticalTabsEnabled[] =
    "qorai.tabs.vertical_tabs_enabled";
inline constexpr char kVerticalTabsCollapsed[] =
    "qorai.tabs.vertical_tabs_collapsed";
inline constexpr char kVerticalTabsExpandedStatePerWindow[] =
    "qorai.tabs.vertical_tabs_expanded_state_per_window";
inline constexpr char kVerticalTabsShowTitleOnWindow[] =
    "qorai.tabs.vertical_tabs_show_title_on_window";
inline constexpr char kVerticalTabsHideCompletelyWhenCollapsed[] =
    "qorai.tabs.vertical_tabs_hide_completely_when_collapsed";
inline constexpr char kVerticalTabsFloatingEnabled[] =
    "qorai.tabs.vertical_tabs_floating_enabled";
inline constexpr char kVerticalTabsExpandedWidth[] =
    "qorai.tabs.vertical_tabs_expanded_width";
inline constexpr char kVerticalTabsOnRight[] =
    "qorai.tabs.vertical_tabs_on_right";
inline constexpr char kVerticalTabsShowScrollbar[] =
    "qorai.tabs.vertical_tabs_show_scrollbar";
inline constexpr char kTreeTabsEnabled[] = "qorai.tabs.tree_tabs_enabled";

inline constexpr char kSharedPinnedTab[] = "qorai.tabs.shared_pinned_tab";

void RegisterQoraiProfilePrefs(PrefRegistrySimple* registry);
void MigrateQoraiProfilePrefs(PrefService* prefs);

bool AreTooltipsEnabled(PrefService* prefs);
bool AreCardPreviewsEnabled(PrefService* prefs);

}  // namespace qorai_tabs

#endif  // QORAI_BROWSER_UI_TABS_QORAI_TAB_PREFS_H_
