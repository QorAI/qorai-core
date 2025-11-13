/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_URL_PLACEMENT_ID_EXTRACTOR_H_
#define QORAI_COMPONENTS_QORAI_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_URL_PLACEMENT_ID_EXTRACTOR_H_

#include <optional>
#include <string>

class GURL;

namespace qorai_ads {

std::optional<std::string> MaybeExtractCreativeAdPlacementIdFromUrl(
    const GURL& url);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_URL_PLACEMENT_ID_EXTRACTOR_H_
