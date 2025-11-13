/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_ADS_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_ADS_UTIL_H_

#include <string_view>

#include "base/values.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"
#include "qorai/components/qorai_ads/core/public/ads_callback.h"

namespace qorai_ads {

void ParseAndSaveNewTabPageAds(base::Value::Dict dict, ResultCallback callback);

std::optional<mojom::NewTabPageAdMetricType> ToMojomNewTabPageAdMetricType(
    std::string_view value);

std::string_view ToString(mojom::NewTabPageAdMetricType value);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_ADS_UTIL_H_
