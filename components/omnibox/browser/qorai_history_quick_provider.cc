/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/omnibox/browser/qorai_history_quick_provider.h"

#include "qorai/components/omnibox/browser/qorai_omnibox_prefs.h"
#include "components/omnibox/browser/actions/omnibox_action.h"
#include "components/omnibox/browser/autocomplete_provider.h"
#include "components/omnibox/browser/history_quick_provider.h"
#include "components/prefs/pref_service.h"

QorAIHistoryQuickProvider::~QorAIHistoryQuickProvider() = default;

void QorAIHistoryQuickProvider::Start(const AutocompleteInput& input,
                                      bool minimal_changes) {
  if (!client()->GetPrefs()->GetBoolean(omnibox::kHistorySuggestionsEnabled)) {
    matches_.clear();
    return;
  }
  HistoryQuickProvider::Start(input, minimal_changes);
}
