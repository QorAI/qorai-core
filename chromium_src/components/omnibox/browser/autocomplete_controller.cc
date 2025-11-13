/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "components/omnibox/browser/autocomplete_controller.h"

#include <algorithm>
#include <memory>
#include <vector>

#include "base/check.h"
#include "base/memory/scoped_refptr.h"
#include "qorai/components/ai_chat/core/browser/utils.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/qorai_search_conversion/utils.h"
#include "qorai/components/commander/common/buildflags/buildflags.h"
#include "qorai/components/omnibox/browser/qorai_bookmark_provider.h"
#include "qorai/components/omnibox/browser/qorai_history_quick_provider.h"
#include "qorai/components/omnibox/browser/qorai_history_url_provider.h"
#include "qorai/components/omnibox/browser/qorai_local_history_zero_suggest_provider.h"
#include "qorai/components/omnibox/browser/qorai_on_device_head_provider.h"
#include "qorai/components/omnibox/browser/qorai_search_provider.h"
#include "qorai/components/omnibox/browser/qorai_shortcuts_provider.h"
#include "qorai/components/omnibox/browser/qora_provider.h"
#include "qorai/components/omnibox/browser/promotion_provider.h"
#include "qorai/components/omnibox/browser/promotion_utils.h"
#include "components/omnibox/browser/autocomplete_input.h"
#include "components/omnibox/browser/autocomplete_match.h"
#include "components/omnibox/browser/calculator_provider.h"
#include "components/omnibox/browser/clipboard_provider.h"
#include "components/omnibox/browser/history_cluster_provider.h"
#include "components/omnibox/browser/history_fuzzy_provider.h"

#if BUILDFLAG(ENABLE_COMMANDER)
#include "qorai/components/commander/common/buildflags/buildflags.h"
#include "qorai/components/commander/common/constants.h"
#include "qorai/components/commander/common/features.h"
#include "qorai/components/omnibox/browser/commander_provider.h"
#endif

using qorai_search_conversion::IsQoraiSearchConversionFeatureEnabled;

namespace {
// If this input has triggered the commander then only show commander results.
void MaybeShowCommands(AutocompleteResult* result,
                       const AutocompleteInput& input) {
#if BUILDFLAG(ENABLE_COMMANDER)
  // If this input isn't a command, return and don't do any work.
  if (!base::FeatureList::IsEnabled(features::kQoraiCommander) ||
      !input.text().starts_with(commander::kCommandPrefix)) {
    return;
  }

  // At this point all commands are moved to the top, and everything else is
  // discarded.
  result->RemoveAllMatchesNotOfType(AutocompleteProvider::TYPE_QORAI_COMMANDER);
#endif
}

void MaybeAddCommanderProvider(AutocompleteController::Providers& providers,
                               AutocompleteController* controller) {
#if BUILDFLAG(ENABLE_COMMANDER)
  if (base::FeatureList::IsEnabled(features::kQoraiCommander)) {
    providers.push_back(base::MakeRefCounted<commander::CommanderProvider>(
        controller->autocomplete_provider_client(), controller));
  }
#endif
}

void MaybeAddQoraProvider(AutocompleteController::Providers& providers,
                         AutocompleteController* controller) {
  auto* provider_client = controller->autocomplete_provider_client();
  // TestOmniboxClient has null prefs getter
  auto* prefs = provider_client->GetPrefs();
  if (prefs && ai_chat::IsAIChatEnabled(prefs) &&
      !provider_client->IsOffTheRecord()) {
    providers.push_back(base::MakeRefCounted<QoraProvider>(provider_client));
  }
}

}  // namespace

namespace ai_chat {

void MaybeShowQoraMatch(AutocompleteResult* result) {
  DCHECK(result);

  // If we're not in AI first mode, regardless of the relevance score, we want
  // to show the Qora match at the bottom. But could be followed by Qorai Search
  // promotion.
  if (!ai_chat::features::IsAIChatFirstEnabled()) {
    result->MoveMatchToBeLast(&QoraProvider::IsMatchFromQoraProvider);
  }
}

}  // namespace ai_chat

#define SearchProvider QoraiSearchProvider
#define HistoryQuickProvider QoraiHistoryQuickProvider
#define HistoryURLProvider QoraiHistoryURLProvider
#define LocalHistoryZeroSuggestProvider QoraiLocalHistoryZeroSuggestProvider
#define BookmarkProvider QoraiBookmarkProvider
#define ShortcutsProvider QoraiShortcutsProvider
#define OnDeviceHeadProvider QoraiOnDeviceHeadProvider
#define QORAI_AUTOCOMPLETE_CONTROLLER_AUTOCOMPLETE_CONTROLLER         \
  MaybeAddCommanderProvider(providers_, this);                        \
  MaybeAddQoraProvider(providers_, this);                              \
  if (IsQoraiSearchConversionFeatureEnabled() &&                      \
      !provider_client_->IsOffTheRecord())                            \
    providers_.push_back(new PromotionProvider(provider_client_.get()));

// This sort should be done right after AutocompleteResult::SortAndCull() in
// the AutocompleteController::SortCullAndAnnotateResult() to make our sorting
// run last but before notifying.
#define QORAI_AUTOCOMPLETE_CONTROLLER_UPDATE_RESULT \
  ai_chat::MaybeShowQoraMatch(&internal_result_);    \
  SortQoraiSearchPromotionMatch(&internal_result_); \
  MaybeShowCommands(&internal_result_, input_);

#include <components/omnibox/browser/autocomplete_controller.cc>

#undef QORAI_AUTOCOMPLETE_CONTROLLER_UPDATE_RESULT
#undef QORAI_AUTOCOMPLETE_CONTROLLER_AUTOCOMPLETE_CONTROLLER
#undef OnDeviceHeadProvider
#undef ShortcutsProvider
#undef BookmarkProvider
#undef LocalHistoryZeroSuggestProvider
#undef HistoryURLProvider
#undef HistoryQuickProvider
#undef SearchProvider
