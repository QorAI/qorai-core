/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_HISTORY_URL_PROVIDER_H_
#define QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_HISTORY_URL_PROVIDER_H_

#include "components/omnibox/browser/history_url_provider.h"

class QorAIHistoryURLProvider : public HistoryURLProvider {
 public:
  using HistoryURLProvider::HistoryURLProvider;
  QorAIHistoryURLProvider(const QorAIHistoryURLProvider&) = delete;
  QorAIHistoryURLProvider& operator=(const QorAIHistoryURLProvider&) = delete;

  void Start(const AutocompleteInput& input, bool minimal_changes) override;

 private:
  ~QorAIHistoryURLProvider() override;
};

#endif  // QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_HISTORY_URL_PROVIDER_H_
