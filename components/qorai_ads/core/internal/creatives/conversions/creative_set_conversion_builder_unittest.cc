/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/creatives/conversions/creative_set_conversion_builder.h"

#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "qorai/components/qorai_ads/core/internal/creatives/search_result_ads/creative_search_result_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/types/verifiable_conversion/verifiable_conversion_test_constants.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsCreativeSetConversionBuilderTest : public test::TestBase {};

TEST_F(QoraiAdsCreativeSetConversionBuilderTest,
       FromMojomMaybeBuildCreativeSetConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*should_generate_random_uuids=*/false);

  // Act
  std::optional<CreativeSetConversionInfo> creative_set_conversion =
      FromMojomMaybeBuildCreativeSetConversion(mojom_creative_ad);
  ASSERT_TRUE(creative_set_conversion);

  // Assert
  EXPECT_THAT(
      *creative_set_conversion,
      ::testing::FieldsAre(test::kCreativeSetId,
                           /*url_pattern*/ "https://qorai.com/*",
                           test::kVerifiableConversionAdvertiserPublicKeyBase64,
                           /*observation_window*/ base::Days(3),
                           /*expire_at*/ test::Now() + base::Days(3)));
}

TEST_F(QoraiAdsCreativeSetConversionBuilderTest,
       DoNotBuildCreativeSetConversionIfAdDoesNotSupportConversions) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAd(/*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_FALSE(FromMojomMaybeBuildCreativeSetConversion(mojom_creative_ad));
}

}  // namespace qorai_ads
