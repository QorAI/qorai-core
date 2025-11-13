// Copyright (c) 2023 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_LOCAL_HISTORY_ZERO_SUGGEST_PROVIDER_H_
#define QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_LOCAL_HISTORY_ZERO_SUGGEST_PROVIDER_H_

#include "components/omnibox/browser/local_history_zero_suggest_provider.h"

class QorAILocalHistoryZeroSuggestProvider
    : public LocalHistoryZeroSuggestProvider {
 public:
  static QorAILocalHistoryZeroSuggestProvider* Create(
      AutocompleteProviderClient* client,
      AutocompleteProviderListener* listener);

  using LocalHistoryZeroSuggestProvider::LocalHistoryZeroSuggestProvider;

  QorAILocalHistoryZeroSuggestProvider(
      const QorAILocalHistoryZeroSuggestProvider&) = delete;
  QorAILocalHistoryZeroSuggestProvider& operator=(
      const QorAILocalHistoryZeroSuggestProvider&) = delete;

  void Start(const AutocompleteInput& input, bool minimal_changes) override;

 private:
  ~QorAILocalHistoryZeroSuggestProvider() override;
};

#endif  // QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_LOCAL_HISTORY_ZERO_SUGGEST_PROVIDER_H_
