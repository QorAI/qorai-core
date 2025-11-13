/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type_util.h"

#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsCreativeNewTabPageAdWallpaperTypeUtilTest,
     StringToCreativeNewTabPageAdImageWallpaperType) {
  // Act & Assert
  EXPECT_EQ(CreativeNewTabPageAdWallpaperType::kImage,
            ToCreativeNewTabPageAdWallpaperType("image"));
}

TEST(QoraiAdsCreativeNewTabPageAdWallpaperTypeUtilTest,
     StringToCreativeNewTabPageAdWallpaperType) {
  // Act & Assert
  EXPECT_EQ(CreativeNewTabPageAdWallpaperType::kRichMedia,
            ToCreativeNewTabPageAdWallpaperType("richMedia"));
}

TEST(QoraiAdsCreativeNewTabPageAdWallpaperTypeUtilTest,
     CreativeNewTabPageAdImageWallpaperTypeToString) {
  // Act & Assert
  EXPECT_EQ("image", ToString(CreativeNewTabPageAdWallpaperType::kImage));
}

TEST(QoraiAdsCreativeNewTabPageAdWallpaperTypeUtilTest,
     CreativeNewTabPageAdRichMediaWallpaperTypeToString) {
  // Act & Assert
  EXPECT_EQ("richMedia",
            ToString(CreativeNewTabPageAdWallpaperType::kRichMedia));
}

}  // namespace qorai_ads
