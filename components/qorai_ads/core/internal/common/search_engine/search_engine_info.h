/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_INFO_H_

#include <string>

namespace qorai_ads {

struct SearchEngineInfo final {
  SearchEngineInfo(std::string url_pattern,
                   std::string result_page_url_pattern,
                   std::string search_term_query_key);

  std::string url_pattern;
  std::string result_page_url_pattern;
  std::string search_term_query_key;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_INFO_H_
