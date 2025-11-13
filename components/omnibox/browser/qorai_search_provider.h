/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_SEARCH_PROVIDER_H_
#define QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_SEARCH_PROVIDER_H_

#include "base/auto_reset.h"
#include "components/omnibox/browser/search_provider.h"

class QorAISearchProvider : public SearchProvider {
 public:
  using SearchProvider::SearchProvider;
  QorAISearchProvider(const QorAISearchProvider&) = delete;
  QorAISearchProvider& operator=(const QorAISearchProvider&) = delete;

  void DoHistoryQuery(bool minimal_changes) override;
  bool IsQueryPotentiallyPrivate() const override;
  QorAISearchProvider* AsQorAISearchProvider() override;

  [[nodiscard]] base::AutoReset<bool> SetInputIsPastedFromClipboard(
      bool is_pasted);
  bool IsInputPastedFromClipboard() const;

 protected:
  ~QorAISearchProvider() override;

 private:
  bool input_is_pasted_from_clipboard_ = false;
};

#endif  // QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_SEARCH_PROVIDER_H_
