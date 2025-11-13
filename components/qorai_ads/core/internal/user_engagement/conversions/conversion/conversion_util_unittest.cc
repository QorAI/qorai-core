/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversion/conversion_util.h"

#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversion/conversion_info.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/types/verifiable_conversion/verifiable_conversion_test_constants.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsConversionInfoUtilTest, ConversionTypeToString) {
  // Arrange
  const ConversionInfo conversion;

  // Act & Assert
  EXPECT_EQ("conversion", ConversionTypeToString(conversion));
}

TEST(QoraiAdsConversionInfoUtilTest, VerifiableConversionTypeToString) {
  // Arrange
  ConversionInfo conversion;
  conversion.verifiable = {
      test::kVerifiableConversionId,
      test::kVerifiableConversionAdvertiserPublicKeyBase64};

  // Act & Assert
  EXPECT_EQ("verifiable conversion", ConversionTypeToString(conversion));
}

}  // namespace qorai_ads
