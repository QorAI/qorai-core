/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_SEARCH_PROVIDER_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_SEARCH_PROVIDER_H_

#define DoHistoryQuery                                        \
  DoHistoryQueryUnused();                                     \
  friend class QoraiSearchProvider;                           \
  friend class QoraiSearchProviderTest;                       \
  bool IsQoraiRichSuggestion(bool is_keyword);                \
                                                              \
 public:                                                      \
  virtual class QoraiSearchProvider* AsQoraiSearchProvider(); \
                                                              \
 private:                                                     \
  virtual void DoHistoryQuery

#define IsQueryPotentiallyPrivate virtual IsQueryPotentiallyPrivate

#include <components/omnibox/browser/search_provider.h>  // IWYU pragma: export

#undef IsQueryPotentiallyPrivate
#undef DoHistoryQuery

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_SEARCH_PROVIDER_H_
