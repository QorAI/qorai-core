// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CORE_COMMON_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CORE_COMMON_PREF_NAMES_H_

namespace qorai_shields {
namespace prefs {

inline constexpr char kAdBlockCheckedDefaultRegion[] =
    "qorai.ad_block.checked_default_region";
inline constexpr char kAdBlockCheckedAllDefaultRegions[] =
    "qorai.ad_block.checked_all_default_regions";
inline constexpr char kAdBlockCookieListOptInShown[] =
    "qorai.ad_block.cookie_list_opt_in_shown";
inline constexpr char kAdBlockCookieListSettingTouched[] =
    "qorai.ad_block.cookie_list_setting_touched";
inline constexpr char kAdBlockMobileNotificationsListSettingTouched[] =
    "qorai.ad_block.mobile_notifications_list_setting_touched";

inline constexpr char kAdBlockCustomFilters[] = "qorai.ad_block.custom_filters";
inline constexpr char kAdBlockRegionalFilters[] =
    "qorai.ad_block.regional_filters";
inline constexpr char kAdBlockListSubscriptions[] =
    "qorai.ad_block.list_subscriptions";
inline constexpr char kAdBlockDeveloperMode[] = "qorai.ad_block.developer_mode";

inline constexpr char kFBEmbedControlType[] = "qorai.fb_embed_default";
inline constexpr char kTwitterEmbedControlType[] =
    "qorai.twitter_embed_default";
inline constexpr char kLinkedInEmbedControlType[] =
    "qorai.linkedin_embed_default";
inline constexpr char kReduceLanguageEnabled[] = "qorai.reduce_language";

inline constexpr char kAdBlockOnlyModeEnabled[] =
    "qorai.shields.adblock_only_mode_enabled";
inline constexpr char kAdBlockOnlyModeWasEnabledForSupportedLocale[] =
    "qorai.shields.adblock_only_mode_was_enabled_for_supported_locale";
inline constexpr char kShieldsDisabledCount[] = "qorai.shields.disabled_count";
inline constexpr char kAdBlockOnlyModePromptDismissed[] =
    "qorai.shields.adblock_only_mode_prompt_dismissed";

}  // namespace prefs
}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CORE_COMMON_PREF_NAMES_H_
