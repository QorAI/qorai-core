// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_BROWSER_PEEKING_CARD_H_
#define QORAI_COMPONENTS_QORAI_NEWS_BROWSER_PEEKING_CARD_H_

#include <string>

#include "base/containers/flat_set.h"
#include "qorai/components/qorai_news/browser/feed_fetcher.h"
#include "qorai/components/qorai_news/browser/feed_sampling.h"
#include "qorai/components/qorai_news/browser/topics_fetcher.h"
#include "qorai/components/qorai_news/common/subscriptions_snapshot.h"

namespace qorai_news {

base::flat_set<std::string> GetTopStoryUrls(
    const base::span<TopicAndArticles>& topics);

std::optional<size_t> PickPeekingCardWithMax(
    SubscriptionsSnapshot subscriptions,
    const base::flat_set<std::string>& top_story_urls,
    const ArticleInfos& articles,
    size_t max_candidates);

std::optional<size_t> PickPeekingCard(
    SubscriptionsSnapshot subscriptions,
    const base::flat_set<std::string>& top_story_urls,
    const ArticleInfos& articles);

}  // namespace qorai_news

#endif  // QORAI_COMPONENTS_QORAI_NEWS_BROWSER_PEEKING_CARD_H_
