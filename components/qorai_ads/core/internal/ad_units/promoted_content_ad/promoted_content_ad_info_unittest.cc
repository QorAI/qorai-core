/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/ad_units/promoted_content_ad/promoted_content_ad_info.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/creatives/promoted_content_ads/creative_promoted_content_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/creatives/promoted_content_ads/creative_promoted_content_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/promoted_content_ads/promoted_content_ad_builder.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsPromotedContentAdInfoTest : public test::TestBase {};

TEST_F(QoraiAdsPromotedContentAdInfoTest, IsValid) {
  // Arrange
  const CreativePromotedContentAdInfo creative_ad =
      test::BuildCreativePromotedContentAd(
          /*should_generate_random_uuids=*/true);
  const PromotedContentAdInfo ad = BuildPromotedContentAd(creative_ad);

  // Act & Assert
  EXPECT_TRUE(ad.IsValid());
}

TEST_F(QoraiAdsPromotedContentAdInfoTest, IsInvalid) {
  // Arrange
  const PromotedContentAdInfo ad;

  // Act & Assert
  EXPECT_FALSE(ad.IsValid());
}

}  // namespace qorai_ads
