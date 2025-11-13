// Copyright (c) 2023 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/omnibox/browser/qorai_local_history_zero_suggest_provider.h"

#include "qorai/components/omnibox/browser/qorai_omnibox_prefs.h"
#include "components/omnibox/browser/autocomplete_input.h"
#include "components/omnibox/browser/autocomplete_provider_client.h"
#include "components/omnibox/browser/local_history_zero_suggest_provider.h"
#include "components/prefs/pref_service.h"

// static
QorAILocalHistoryZeroSuggestProvider*
QorAILocalHistoryZeroSuggestProvider::Create(
    AutocompleteProviderClient* client,
    AutocompleteProviderListener* listener) {
  return new QorAILocalHistoryZeroSuggestProvider(client, listener);
}

QorAILocalHistoryZeroSuggestProvider::~QorAILocalHistoryZeroSuggestProvider() =
    default;

void QorAILocalHistoryZeroSuggestProvider::Start(const AutocompleteInput& input,
                                                 bool minimal_changes) {
  if (!client_->GetPrefs()->GetBoolean(omnibox::kHistorySuggestionsEnabled) ||
      !client_->GetPrefs()->GetBoolean(omnibox::kAutocompleteEnabled)) {
    matches_.clear();
    return;
  }

  LocalHistoryZeroSuggestProvider::Start(input, minimal_changes);
}
