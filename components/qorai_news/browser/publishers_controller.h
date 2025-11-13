// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_BROWSER_PUBLISHERS_CONTROLLER_H_
#define QORAI_COMPONENTS_QORAI_NEWS_BROWSER_PUBLISHERS_CONTROLLER_H_

#include <memory>
#include <string>

#include "base/functional/callback_forward.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/one_shot_event.h"
#include "qorai/components/api_request_helper/api_request_helper.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom-forward.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom.h"
#include "qorai/components/qorai_news/common/locales_helper.h"

namespace qorai_news {

using GetPublishersCallback = mojom::QoraiNewsController::GetPublishersCallback;
using GetPublisherCallback = base::OnceCallback<void(mojom::PublisherPtr)>;

class SubscriptionsSnapshot;

bool IsSubscribed(const mojom::PublisherPtr& publisher);

class PublishersController {
 public:
  explicit PublishersController(
      api_request_helper::APIRequestHelper* api_request_helper);
  ~PublishersController();
  PublishersController(const PublishersController&) = delete;
  PublishersController& operator=(const PublishersController&) = delete;

  // The following methods return a pointer to a |Publisher|. This pointer is
  // not safe to hold onto, as the object it points to will be destroyed when
  // the publishers are updated (which happens regularly). If you need it to
  // live longer, take a clone.
  void GetPublisherForSite(const SubscriptionsSnapshot& subscriptions,
                           const GURL& site_url,
                           GetPublisherCallback callback);
  void GetPublisherForFeed(const SubscriptionsSnapshot& subscriptions,
                           const GURL& feed_url,
                           GetPublisherCallback callback);

  void GetOrFetchPublishers(const SubscriptionsSnapshot& subscriptions,
                            GetPublishersCallback callback,
                            bool wait_for_current_update = false);
  void GetLocale(const SubscriptionsSnapshot& subscriptions,
                 mojom::QoraiNewsController::GetLocaleCallback);
  const std::string& GetLastLocale() const;
  void EnsurePublishersIsUpdating(const SubscriptionsSnapshot& subscriptions);
  void ClearCache();

  const Publishers& last_publishers() { return publishers_; }

 private:
  void GetOrFetchPublishers(const SubscriptionsSnapshot& subscriptions,
                            base::OnceClosure callback,
                            bool wait_for_current_update);
  void UpdateDefaultLocale();

  raw_ptr<api_request_helper::APIRequestHelper> api_request_helper_;

  std::unique_ptr<base::OneShotEvent> on_current_update_complete_;
  std::string default_locale_;
  Publishers publishers_;

  base::WeakPtrFactory<PublishersController> weak_ptr_factory_{this};
};

}  // namespace qorai_news

#endif  // QORAI_COMPONENTS_QORAI_NEWS_BROWSER_PUBLISHERS_CONTROLLER_H_
