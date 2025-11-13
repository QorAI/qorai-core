// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_BROWSER_PUBLISHERS_PARSING_H_
#define QORAI_COMPONENTS_QORAI_NEWS_BROWSER_PUBLISHERS_PARSING_H_

#include <optional>
#include <vector>

#include "base/values.h"
#include "qorai/components/qorai_news/browser/qorai_news_pref_manager.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom-forward.h"
#include "qorai/components/qorai_news/common/locales_helper.h"

namespace qorai_news {

std::optional<Publishers> ParseCombinedPublisherList(const base::Value& value);

void ParseDirectPublisherList(const std::vector<DirectFeed>& direct_feeds,
                              std::vector<mojom::PublisherPtr>* publishers);

}  // namespace qorai_news

#endif  // QORAI_COMPONENTS_QORAI_NEWS_BROWSER_PUBLISHERS_PARSING_H_
