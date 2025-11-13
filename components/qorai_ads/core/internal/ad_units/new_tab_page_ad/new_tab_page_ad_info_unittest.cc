/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"
#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/new_tab_page_ad_builder.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsNewTabPageAdInfoTest : public test::TestBase {};

TEST_F(QoraiAdsNewTabPageAdInfoTest, IsValid) {
  // Arrange
  const CreativeNewTabPageAdInfo creative_ad =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  const NewTabPageAdInfo ad = BuildNewTabPageAd(creative_ad);

  // Act & Assert
  EXPECT_TRUE(ad.IsValid());
}

TEST_F(QoraiAdsNewTabPageAdInfoTest, IsInvalid) {
  // Arrange
  const NewTabPageAdInfo ad;

  // Act & Assert
  EXPECT_FALSE(ad.IsValid());
}

}  // namespace qorai_ads
