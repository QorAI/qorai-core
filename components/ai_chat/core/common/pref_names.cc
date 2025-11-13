/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/ai_chat/core/common/pref_names.h"

#include <string_view>

#include "base/time/time.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "components/prefs/pref_registry_simple.h"

namespace ai_chat::prefs {

void RegisterProfilePrefs(PrefRegistrySimple* registry) {
  if (ai_chat::features::IsAIChatEnabled()) {
    registry->RegisterTimePref(kLastAcceptedDisclaimer, {});
    registry->RegisterBooleanPref(kQoraiChatStorageEnabled, true);
    registry->RegisterBooleanPref(kQoraiChatAutocompleteProviderEnabled, true);
    registry->RegisterBooleanPref(kUserDismissedPremiumPrompt, false);
    registry->RegisterBooleanPref(kUserDismissedStorageNotice, false);
#if BUILDFLAG(IS_ANDROID)
    registry->RegisterBooleanPref(kQoraiChatSubscriptionActiveAndroid, false);
    registry->RegisterStringPref(kQoraiChatPurchaseTokenAndroid, "");
    registry->RegisterStringPref(kQoraiChatPackageNameAndroid, "");
    registry->RegisterStringPref(kQoraiChatProductIdAndroid, "");
    registry->RegisterStringPref(kQoraiChatOrderIdAndroid, "");
    // 0 is not linked
    registry->RegisterIntegerPref(kQoraiChatSubscriptionLinkStatusAndroid, 0);
#endif
    registry->RegisterBooleanPref(kQoraiAIChatContextMenuEnabled, true);
    registry->RegisterBooleanPref(kQoraiAIChatShowToolbarButton, true);
    registry->RegisterBooleanPref(kQoraiAIChatToolbarButtonOpensFullPage,
                                  false);
    registry->RegisterBooleanPref(kQoraiAIChatTabOrganizationEnabled, true);
    registry->RegisterBooleanPref(kQoraiAIChatUserCustomizationEnabled, true);
    registry->RegisterBooleanPref(kQoraiAIChatUserMemoryEnabled, true);
    registry->RegisterDictionaryPref(kQoraiAIChatUserCustomizations);
    registry->RegisterListPref(kQoraiAIChatUserMemories);
    registry->RegisterDictionaryPref(kQoraiAIChatSkills);
    registry->RegisterBooleanPref(kQoraiAIChatOllamaFetchEnabled, false);
  }
  registry->RegisterBooleanPref(kEnabledByPolicy, true);
}

void RegisterProfilePrefsForMigration(PrefRegistrySimple* registry) {
  if (ai_chat::features::IsAIChatEnabled()) {
    registry->RegisterBooleanPref(kObseleteQoraiChatAutoGenerateQuestions,
                                  false);
  }
}

void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  // Added 11/2023
  registry->RegisterDictionaryPref(kQoraiChatPremiumCredentialCache);
}

}  // namespace ai_chat::prefs
