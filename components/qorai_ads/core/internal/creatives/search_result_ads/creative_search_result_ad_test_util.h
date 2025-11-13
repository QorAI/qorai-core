/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_SEARCH_RESULT_ADS_CREATIVE_SEARCH_RESULT_AD_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_SEARCH_RESULT_ADS_CREATIVE_SEARCH_RESULT_AD_TEST_UTIL_H_

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads::test {

mojom::CreativeSearchResultAdInfoPtr BuildCreativeSearchResultAd(
    bool should_generate_random_uuids);
mojom::CreativeSearchResultAdInfoPtr BuildCreativeSearchResultAdWithConversion(
    bool should_generate_random_uuids);

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_SEARCH_RESULT_ADS_CREATIVE_SEARCH_RESULT_AD_TEST_UTIL_H_
