/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_feature.h"

namespace qorai_ads {

BASE_FEATURE(kNewTabPageAdFeature,
             "NewTabPageAds",
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace qorai_ads
