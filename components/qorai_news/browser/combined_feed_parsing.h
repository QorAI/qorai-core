// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_BROWSER_COMBINED_FEED_PARSING_H_
#define QORAI_COMPONENTS_QORAI_NEWS_BROWSER_COMBINED_FEED_PARSING_H_

#include <string>
#include <vector>

#include "base/values.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom.h"

namespace qorai_news {

// Convert from the "combined feed" hosted remotely to Qorai News mojom items.
std::vector<mojom::FeedItemPtr> ParseFeedItems(const base::Value& value);

}  // namespace qorai_news

#endif  // QORAI_COMPONENTS_QORAI_NEWS_BROWSER_COMBINED_FEED_PARSING_H_
