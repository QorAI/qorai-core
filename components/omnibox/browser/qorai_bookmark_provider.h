/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_BOOKMARK_PROVIDER_H_
#define QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_BOOKMARK_PROVIDER_H_

#include "components/omnibox/browser/bookmark_provider.h"

class QorAIBookmarkProvider : public BookmarkProvider {
 public:
  using BookmarkProvider::BookmarkProvider;
  QorAIBookmarkProvider(const QorAIBookmarkProvider&) = delete;
  QorAIBookmarkProvider& operator=(const QorAIBookmarkProvider&) = delete;

  void Start(const AutocompleteInput& input, bool minimal_changes) override;

 private:
  ~QorAIBookmarkProvider() override;
};

#endif  // QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_BOOKMARK_PROVIDER_H_
