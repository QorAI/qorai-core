// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_BROWSER_HTML_PARSING_H_
#define QORAI_COMPONENTS_QORAI_NEWS_BROWSER_HTML_PARSING_H_

#include <string>
#include <vector>

class GURL;

namespace qorai_news {

std::vector<GURL> GetFeedURLsFromHTMLDocument(const std::string& charset,
                                              const std::string& html_body,
                                              const GURL& html_url);

}  // namespace qorai_news

#endif  // QORAI_COMPONENTS_QORAI_NEWS_BROWSER_HTML_PARSING_H_
