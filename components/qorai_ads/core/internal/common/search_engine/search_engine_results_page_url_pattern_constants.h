/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_RESULTS_PAGE_URL_PATTERN_CONSTANTS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_RESULTS_PAGE_URL_PATTERN_CONSTANTS_H_

#include <string>

namespace qorai_ads {

const std::string& GetAmazonResultsPageUrlPattern();
const std::string& GetGoogleResultsPageUrlPattern();
const std::string& GetMojeekResultsPageUrlPattern();
const std::string& GetWikipediaResultsPageUrlPattern();
const std::string& GetYahooResultsPageUrlPattern();

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_RESULTS_PAGE_URL_PATTERN_CONSTANTS_H_
