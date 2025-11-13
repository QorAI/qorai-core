/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_TEST_UTIL_H_

#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"

namespace qorai_ads {

struct NewTabPageAdInfo;

namespace test {

NewTabPageAdInfo BuildNewTabPageAd(
    CreativeNewTabPageAdWallpaperType wallpaper_type,
    bool should_generate_random_uuids);

NewTabPageAdInfo BuildAndSaveNewTabPageAd(
    CreativeNewTabPageAdWallpaperType wallpaper_type,
    bool should_generate_random_uuids);

}  // namespace test

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_TEST_UTIL_H_
