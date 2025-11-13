/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SIDEBAR_BROWSER_PREF_NAMES_H_
#define QORAI_COMPONENTS_SIDEBAR_BROWSER_PREF_NAMES_H_

namespace sidebar {

inline constexpr char kSidebarItems[] = "qorai.sidebar.sidebar_items";
inline constexpr char kSidebarHiddenBuiltInItems[] =
    "qorai.sidebar.hidden_built_in_items";
inline constexpr char kSidebarShowOption[] =
    "qorai.sidebar.sidebar_show_option";
inline constexpr char kSidebarItemAddedFeedbackBubbleShowCount[] =
    "qorai.sidebar.item_added_feedback_bubble_shown_count";
inline constexpr char kSidePanelWidth[] = "qorai.sidebar.side_panel_width";
inline constexpr char kLastUsedBuiltInItemType[] =
    "qorai.sidebar.last_used_built_in_item_type";

// Indicates that the Qora side panel is opened once for Sidebar Enabled-by
// -default test via griffin.
inline constexpr char kQoraPanelOneShotOpen[] =
    "qorai.sidebar.qora_panel_one_shot_shot";

// Indicates that it's target user for Sidebar Enabled-by-default test via
// griffin. local state pref.
inline constexpr char kTargetUserForSidebarEnabledTest[] =
    "qorai.sidebar.target_user_for_sidebar_enabled_test";

// Indicates that sidebar alignment was changed by the browser itself, not by
// users.
inline constexpr char kSidebarAlignmentChangedTemporarily[] =
    "qorai.sidebar.sidebar_alignment_changed_for_vertical_tabs";

inline constexpr char kSidebarSettingChangeInitialP3AReport[] =
    "qorai.sidebar.setting_change_initial_p3a_reported";

}  // namespace sidebar

#endif  // QORAI_COMPONENTS_SIDEBAR_BROWSER_PREF_NAMES_H_
