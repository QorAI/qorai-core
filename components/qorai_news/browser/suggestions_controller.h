// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_BROWSER_SUGGESTIONS_CONTROLLER_H_
#define QORAI_COMPONENTS_QORAI_NEWS_BROWSER_SUGGESTIONS_CONTROLLER_H_

#include <memory>
#include <string>
#include <vector>

#include "base/containers/flat_map.h"
#include "base/containers/flat_set.h"
#include "base/functional/callback_forward.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/one_shot_event.h"
#include "base/task/cancelable_task_tracker.h"
#include "qorai/components/api_request_helper/api_request_helper.h"
#include "qorai/components/qorai_news/browser/background_history_querier.h"
#include "qorai/components/qorai_news/browser/qorai_news_pref_manager.h"
#include "qorai/components/qorai_news/browser/publishers_controller.h"
#include "components/history/core/browser/history_service.h"
#include "components/history/core/browser/history_types.h"

namespace qorai_news {

using GetSuggestedPublisherIdsCallback =
    mojom::QoraiNewsController::GetSuggestedPublisherIdsCallback;

class SubscriptionsSnapshot;

class SuggestionsController {
 public:
  struct PublisherSimilarity {
    std::string publisher_id;
    double score;
  };

  using PublisherSimilarities =
      base::flat_map<std::string, std::vector<PublisherSimilarity>>;

  explicit SuggestionsController(
      PublishersController* publishers_controller,
      api_request_helper::APIRequestHelper* api_request_helper,
      BackgroundHistoryQuerier& history_querier);
  SuggestionsController(const SuggestionsController&) = delete;
  SuggestionsController& operator=(const SuggestionsController&) = delete;
  ~SuggestionsController();

  void GetSuggestedPublisherIds(const SubscriptionsSnapshot& subscriptions,
                                GetSuggestedPublisherIdsCallback callback);
  void EnsureSimilarityMatrixIsUpdating(
      const SubscriptionsSnapshot& subscriptions);

 private:
  friend class QoraiNewsSuggestionsControllerTest;
  void GetOrFetchSimilarityMatrix(const SubscriptionsSnapshot& subscriptions,
                                  base::OnceClosure callback);
  std::vector<std::string> GetSuggestedPublisherIdsWithHistory(
      const Publishers& publishers,
      const history::QueryResults& history);

  bool is_update_in_progress_ = false;
  // Task tracker for HistoryService callbacks.
  base::CancelableTaskTracker task_tracker_;

  raw_ptr<PublishersController> publishers_controller_;
  raw_ptr<api_request_helper::APIRequestHelper> api_request_helper_;
  raw_ref<BackgroundHistoryQuerier> history_querier_;
  std::unique_ptr<base::OneShotEvent> on_current_update_complete_;

  std::string locale_;
  PublisherSimilarities similarities_;

  base::WeakPtrFactory<SuggestionsController> weak_ptr_factory_{this};
};
}  // namespace qorai_news

#endif  // QORAI_COMPONENTS_QORAI_NEWS_BROWSER_SUGGESTIONS_CONTROLLER_H_
