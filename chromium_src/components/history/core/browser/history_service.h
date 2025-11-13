/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_HISTORY_CORE_BROWSER_HISTORY_SERVICE_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_HISTORY_CORE_BROWSER_HISTORY_SERVICE_H_

class QoraiHistoryURLProviderTest;
class QoraiHistoryQuickProviderTest;

#define Cleanup                                 \
  Cleanup();                                    \
  friend class ::QoraiHistoryURLProviderTest;   \
  friend class ::QoraiHistoryQuickProviderTest; \
  void CleanupUnused

#define AddRelatedSearchesForVisit                                     \
  GetKnownToSyncCount(                                                 \
      base::OnceCallback<void(history::HistoryCountResult)> callback); \
  void AddRelatedSearchesForVisit

#include <components/history/core/browser/history_service.h>  // IWYU pragma: export

#undef AddRelatedSearchesForVisit

#undef Cleanup

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_HISTORY_CORE_BROWSER_HISTORY_SERVICE_H_
