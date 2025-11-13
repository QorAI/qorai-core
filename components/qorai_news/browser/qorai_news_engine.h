// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_BROWSER_QORAI_NEWS_ENGINE_H_
#define QORAI_COMPONENTS_QORAI_NEWS_BROWSER_QORAI_NEWS_ENGINE_H_

#include <memory>
#include <string>

#include "base/functional/callback_forward.h"
#include "base/memory/scoped_refptr.h"
#include "base/memory/weak_ptr.h"
#include "base/sequence_checker.h"
#include "base/thread_annotations.h"
#include "qorai/components/qorai_news/browser/background_history_querier.h"
#include "qorai/components/qorai_news/browser/direct_feed_fetcher.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom.h"

namespace api_request_helper {
class APIRequestHelper;
}

namespace network {
class PendingSharedURLLoaderFactory;
class SharedURLLoaderFactory;
}  // namespace network

namespace qorai_news {

class PublishersController;
class SuggestionsController;
class ChannelsController;
class FeedController;
class FeedV2Builder;
class SubscriptionsSnapshot;

using HashCallback = base::OnceCallback<void(const std::string&)>;
using GetPublisherCallback = base::OnceCallback<void(mojom::PublisherPtr)>;

// This class lives on a background thread. It exists so that we can do heavy
// lifting such as building a feed or generating suggestions without blocking
// the UI thread. Its essentially the backend for the QoraiNewsController.
class QoraiNewsEngine {
 public:
  // Alias so its easier to reuse the callbacks from the mojom interface.
  using m = mojom::QoraiNewsController;

  explicit QoraiNewsEngine(
      std::unique_ptr<network::PendingSharedURLLoaderFactory>
          pending_shared_url_loader_factory,
      BackgroundHistoryQuerier history_querier,
      base::WeakPtr<DirectFeedFetcher::Delegate> direct_feed_fetcher_delegate);
  QoraiNewsEngine(const QoraiNewsEngine&) = delete;
  QoraiNewsEngine& operator=(const QoraiNewsEngine&) = delete;
  ~QoraiNewsEngine();

  void GetLocale(SubscriptionsSnapshot snapshot, m::GetLocaleCallback callback);
  void GetFeed(SubscriptionsSnapshot snapshot, m::GetFeedCallback callback);
  void GetFollowingFeed(SubscriptionsSnapshot snapshot,
                        m::GetFollowingFeedCallback callback);
  void GetChannelFeed(SubscriptionsSnapshot snapshot,
                      const std::string& channel,
                      m::GetChannelFeedCallback callback);
  void GetPublisherFeed(SubscriptionsSnapshot snapshot,
                        const std::string& publisher_id,
                        m::GetPublisherFeedCallback callback);
  void EnsurePublishersIsUpdating(SubscriptionsSnapshot snapshot);
  void GetFeedV2(SubscriptionsSnapshot snapshot, m::GetFeedV2Callback callback);
  void CheckForFeedsUpdate(SubscriptionsSnapshot snapshot,
                           bool refetch_data,
                           HashCallback callback);
  void PrefetchFeed(SubscriptionsSnapshot snapshot);

  void GetSignals(SubscriptionsSnapshot snapshot,
                  m::GetSignalsCallback callback);
  void GetPublishers(SubscriptionsSnapshot snapshot,
                     m::GetPublishersCallback callback);
  void GetPublisherForSite(SubscriptionsSnapshot snapshot,
                           GURL site_url,
                           GetPublisherCallback callback);
  void GetPublisherForFeed(SubscriptionsSnapshot snapshot,
                           GURL feed_url,
                           GetPublisherCallback callback);
  void GetChannels(SubscriptionsSnapshot snapshot,
                   m::GetChannelsCallback callback);

  void GetSuggestedPublisherIds(SubscriptionsSnapshot snapshot,
                                m::GetSuggestedPublisherIdsCallback callback);

  base::WeakPtr<QoraiNewsEngine> AsWeakPtr();

 private:
  FeedV2Builder* MaybeFeedV2Builder();
  FeedController* MaybeFeedV1Builder();

  scoped_refptr<network::SharedURLLoaderFactory> GetSharedURLLoaderFactory();
  api_request_helper::APIRequestHelper* GetApiRequestHelper();
  PublishersController* GetPublishersController();
  ChannelsController* GetChannelsController();
  SuggestionsController* GetSuggestionsController();

  std::unique_ptr<network::PendingSharedURLLoaderFactory>
      pending_shared_url_loader_factory_ GUARDED_BY_CONTEXT(sequence_checker_);

  BackgroundHistoryQuerier history_querier_
      GUARDED_BY_CONTEXT(sequence_checker_);

  base::WeakPtr<DirectFeedFetcher::Delegate> direct_feed_fetcher_delegate_;

  std::unique_ptr<api_request_helper::APIRequestHelper> api_request_helper_
      GUARDED_BY_CONTEXT(sequence_checker_);

  std::unique_ptr<PublishersController> publishers_controller_
      GUARDED_BY_CONTEXT(sequence_checker_);
  std::unique_ptr<ChannelsController> channels_controller_
      GUARDED_BY_CONTEXT(sequence_checker_);
  std::unique_ptr<SuggestionsController> suggestions_controller_
      GUARDED_BY_CONTEXT(sequence_checker_);

  std::unique_ptr<FeedController> feed_controller_
      GUARDED_BY_CONTEXT(sequence_checker_);

  std::unique_ptr<FeedV2Builder> feed_v2_builder_
      GUARDED_BY_CONTEXT(sequence_checker_);

  SEQUENCE_CHECKER(sequence_checker_);

  base::WeakPtrFactory<QoraiNewsEngine> weak_ptr_factory_{this};
};

}  // namespace qorai_news

#endif  // QORAI_COMPONENTS_QORAI_NEWS_BROWSER_QORAI_NEWS_ENGINE_H_
