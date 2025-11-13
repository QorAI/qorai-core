/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_AD_WALLPAPER_TYPE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_AD_WALLPAPER_TYPE_UTIL_H_

#include <string>
#include <string_view>

#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"

namespace qorai_ads {

CreativeNewTabPageAdWallpaperType ToCreativeNewTabPageAdWallpaperType(
    std::string_view wallpaper_type);

std::string ToString(CreativeNewTabPageAdWallpaperType wallpaper_type);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_AD_WALLPAPER_TYPE_UTIL_H_
