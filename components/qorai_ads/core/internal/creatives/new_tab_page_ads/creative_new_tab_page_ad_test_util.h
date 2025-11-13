/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_AD_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_AD_TEST_UTIL_H_

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"

namespace qorai_ads::test {

CreativeNewTabPageAdList BuildCreativeNewTabPageAds(
    CreativeNewTabPageAdWallpaperType wallpaper_type,
    size_t count);
CreativeNewTabPageAdInfo BuildCreativeNewTabPageAd(
    CreativeNewTabPageAdWallpaperType wallpaper_type,
    bool should_generate_random_uuids);

void SaveCreativeNewTabPageAds(const CreativeNewTabPageAdList& creative_ads);

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_AD_TEST_UTIL_H_
