/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_AI_CHAT_CORE_COMMON_PREF_NAMES_H_
#define QORAI_COMPONENTS_AI_CHAT_CORE_COMMON_PREF_NAMES_H_

#include "base/component_export.h"
#include "build/build_config.h"

class PrefRegistrySimple;

namespace ai_chat::prefs {

inline constexpr char kLastAcceptedDisclaimer[] =
    "qorai.ai_chat.last_accepted_disclaimer";
inline constexpr char kQoraiChatStorageEnabled[] =
    "qorai.ai_chat.storage_enabled";
inline constexpr char kQoraiChatAutocompleteProviderEnabled[] =
    "qorai.ai_chat.autocomplete_provider_enabled";
inline constexpr char kQoraiChatP3AChatCountWeeklyStorage[] =
    "qorai.ai_chat.p3a_chat_count";
inline constexpr char kQoraiChatP3AChatWithHistoryCountWeeklyStorage[] =
    "qorai.ai_chat.p3a_chat_with_history_count";
inline constexpr char kQoraiChatP3AChatDurationsWeeklyStorage[] =
    "qorai.ai_chat.p3a_chat_durations";
inline constexpr char kQoraiChatP3APromptCountWeeklyStorage[] =
    "qorai.ai_chat.p3a_prompt_count";
// Stores Qora Premium credentials that have already been fetched from the
// SKU SDK but were not used because the chat server was unavailable.
inline constexpr char kQoraiChatPremiumCredentialCache[] =
    "qorai.ai_chat.premium_credential_cache";
inline constexpr char kUserDismissedPremiumPrompt[] =
    "qorai.ai_chat.user_dismissed_premium_prompt";
inline constexpr char kUserDismissedStorageNotice[] =
    "qorai.ai_chat.user_dismissed_storage_notice";
inline constexpr char kQoraiChatP3AOmniboxOpenWeeklyStorage[] =
    "qorai.ai_chat.p3a_omnibox_open";
inline constexpr char kQoraiChatP3AOmniboxAutocompleteWeeklyStorage[] =
    "qorai.ai_chat.p3a_omnibox_autocomplete";
inline constexpr char kQoraiChatP3ALastPremiumCheck[] =
    "qorai.ai_chat.p3a_last_premium_check";
inline constexpr char kQoraiChatP3ALastPremiumStatus[] =
    "qorai.ai_chat.p3a_last_premium_status";
inline constexpr char kQoraiChatP3AFirstUsageTime[] =
    "qorai.ai_chat.p3a_first_usage_time";
inline constexpr char kQoraiChatP3ALastUsageTime[] =
    "qorai.ai_chat.p3a_last_usage_time";
inline constexpr char kQoraiChatP3AUsedSecondDay[] =
    "qorai.ai_chat.p3a_used_second_day";
inline constexpr char kQoraiChatP3AContextMenuUsages[] =
    "qorai.ai_chat.p3a_context_menu_usages";
inline constexpr char kQoraiChatP3AEntryPointUsages[] =
    "qorai.ai_chat.p3a_entry_point_usages";
inline constexpr char kQoraiChatP3ASidebarUsages[] =
    "qorai.ai_chat.p3a_sidebar_usages";
inline constexpr char kQoraiChatP3AFullPageSwitches[] =
    "qorai.ai_chat.p3a_full_page_switches";
inline constexpr char kQoraiChatP3ALastContextMenuUsageTime[] =
    "qorai.ai_chat.p3a_last_context_menu_time";
inline constexpr char kQoraiChatP3AFirstChatPromptsReported[] =
    "qorai.ai_chat.p3a_first_chat_prompts_reported";
inline constexpr char kQoraiChatP3AContextSourceUsages[] =
    "qorai.ai_chat.p3a_context_source_usages";
inline constexpr char kQoraiChatP3ARateLimitStops[] =
    "qorai.ai_chat.p3a_rate_limit_stops";
inline constexpr char kQoraiChatP3AContextLimits[] =
    "qorai.ai_chat.p3a_context_limits";
inline constexpr char kTabFocusP3ATotalTabCount[] =
    "qorai.ai_chat.p3a_tab_focus_total_tab_count";
inline constexpr char kTabFocusP3AMaxTabCount[] =
    "qorai.ai_chat.p3a_tab_focus_max_tab_count";
inline constexpr char kTabFocusP3ASessionCount[] =
    "qorai.ai_chat.p3a_tab_focus_session_count";
inline constexpr char kTabFocusP3ALastUsageTime[] =
    "qorai.ai_chat.p3a_tab_focus_last_usage_time";
#if BUILDFLAG(IS_ANDROID)
inline constexpr char kQoraiChatSubscriptionActiveAndroid[] =
    "qorai.ai_chat.subscription_active_android";
inline constexpr char kQoraiChatPurchaseTokenAndroid[] =
    "qorai.ai_chat.purchase_token_android";
inline constexpr char kQoraiChatPackageNameAndroid[] =
    "qorai.ai_chat.package_name_android";
inline constexpr char kQoraiChatProductIdAndroid[] =
    "qorai.ai_chat.product_id_android";
inline constexpr char kQoraiChatOrderIdAndroid[] =
    "qorai.ai_chat.order_id_android";
inline constexpr char kQoraiChatSubscriptionLinkStatusAndroid[] =
    "qorai.ai_chat.subscription_link_status_android";
#endif
inline constexpr char kQoraiAIChatContextMenuEnabled[] =
    "qorai.ai_chat.context_menu_enabled";

// Indicates whether a toolbar button can be shown on a normal browser UI
inline constexpr char kQoraiAIChatShowToolbarButton[] =
    "qorai.ai_chat.show_toolbar_button";
inline constexpr char kQoraiAIChatToolbarButtonOpensFullPage[] =
    "qorai.ai_chat.toolbar_button_opens_full_page";

// Used to indicate whether the feature is enabled by group policy.
inline constexpr char kEnabledByPolicy[] = "qorai.ai_chat.enabled_by_policy";
inline constexpr char kObseleteQoraiChatAutoGenerateQuestions[] =
    "qorai.ai_chat.auto_generate_questions";

inline constexpr char kQoraiAIChatTabOrganizationEnabled[] =
    "qorai.ai_chat.tab_organization_enabled";

inline constexpr char kQoraiAIChatUserCustomizationEnabled[] =
    "qorai.ai_chat.user_customization_enabled";
inline constexpr char kQoraiAIChatUserCustomizations[] =
    "qorai.ai_chat.user_customizations";
inline constexpr char kQoraiAIChatUserMemoryEnabled[] =
    "qorai.ai_chat.user_memory_enabled";
inline constexpr char kQoraiAIChatUserMemories[] =
    "qorai.ai_chat.user_memories";
// Note: Pref key kept as 'smart_modes' for backward compatibility
// (feature is now called 'skills').
inline constexpr char kQoraiAIChatSkills[] = "qorai.ai_chat.smart_modes";
inline constexpr char kQoraiAIChatOllamaFetchEnabled[] =
    "qorai.ai_chat.ollama_fetch_enabled";

COMPONENT_EXPORT(AI_CHAT_COMMON)
void RegisterProfilePrefs(PrefRegistrySimple* registry);

COMPONENT_EXPORT(AI_CHAT_COMMON)
void RegisterProfilePrefsForMigration(PrefRegistrySimple* registry);

COMPONENT_EXPORT(AI_CHAT_COMMON)
void RegisterLocalStatePrefs(PrefRegistrySimple* registry);

}  // namespace ai_chat::prefs

#endif  // QORAI_COMPONENTS_AI_CHAT_CORE_COMMON_PREF_NAMES_H_
