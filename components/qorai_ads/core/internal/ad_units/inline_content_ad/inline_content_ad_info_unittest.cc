/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/ad_units/inline_content_ad/inline_content_ad_info.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/creatives/inline_content_ads/creative_inline_content_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/creatives/inline_content_ads/creative_inline_content_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/inline_content_ads/inline_content_ad_builder.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsInlineContentAdInfoTest : public test::TestBase {};

TEST_F(QoraiAdsInlineContentAdInfoTest, IsValid) {
  // Arrange
  const CreativeInlineContentAdInfo creative_ad =
      test::BuildCreativeInlineContentAd(/*should_generate_random_uuids=*/true);
  const InlineContentAdInfo ad = BuildInlineContentAd(creative_ad);

  // Act & Assert
  EXPECT_TRUE(ad.IsValid());
}

TEST_F(QoraiAdsInlineContentAdInfoTest, IsInvalid) {
  // Arrange
  const InlineContentAdInfo ad;

  // Act & Assert
  EXPECT_FALSE(ad.IsValid());
}

}  // namespace qorai_ads
