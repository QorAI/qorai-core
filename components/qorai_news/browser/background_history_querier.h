// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_BROWSER_BACKGROUND_HISTORY_QUERIER_H_
#define QORAI_COMPONENTS_QORAI_NEWS_BROWSER_BACKGROUND_HISTORY_QUERIER_H_

#include "base/functional/callback_forward.h"
#include "base/task/cancelable_task_tracker.h"
#include "components/history/core/browser/history_service.h"
#include "components/history/core/browser/history_types.h"

namespace qorai_news {

using QueryHistoryCallback = history::HistoryService::QueryHistoryCallback;
using BackgroundHistoryQuerier =
    base::RepeatingCallback<void(QueryHistoryCallback)>;

history::QueryOptions GetQueryOptions();

// Creates a function for querying history from a non-main thread. This lets
// us lazily pull a recent snapshot of history into our worker sequence.
// |history_service| a weak pointer to a history service
// |get_tracker| a repeatable callback for getting the task tracker to use. If
// the returned task tracker is null, the task will not be posted.
BackgroundHistoryQuerier MakeHistoryQuerier(
    base::WeakPtr<history::HistoryService> history_service,
    base::RepeatingCallback<base::CancelableTaskTracker*()> get_tracker);

}  // namespace qorai_news

#endif  // QORAI_COMPONENTS_QORAI_NEWS_BROWSER_BACKGROUND_HISTORY_QUERIER_H_
