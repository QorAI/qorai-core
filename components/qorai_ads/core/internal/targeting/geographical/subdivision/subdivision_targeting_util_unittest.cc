/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/targeting/geographical/subdivision/subdivision_targeting_util.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsSubdivisionTargetingUtilTest, ShouldTargetSubdivisionCountryCode) {
  // Act & Assert
  EXPECT_TRUE(ShouldTargetSubdivisionCountryCode(
      /*United States of America*/ "US"));
  EXPECT_TRUE(ShouldTargetSubdivisionCountryCode(/*Canada*/ "CA"));
}

TEST(QoraiAdsSubdivisionTargetingUtilTest,
     ShouldNotTargetSubdivisionCountryCode) {
  // Act & Assert
  EXPECT_FALSE(ShouldTargetSubdivisionCountryCode("XX"));
}

TEST(QoraiAdsSubdivisionTargetingUtilTest, ShouldTargetSubdivision) {
  // Act & Assert
  EXPECT_TRUE(ShouldTargetSubdivision(
      /*United States of America*/ "US", /*subdivision=*/"US-CA"));
}

TEST(QoraiAdsSubdivisionTargetingUtilTest, ShouldNotTargetSubdivision) {
  // Act & Assert
  EXPECT_FALSE(ShouldTargetSubdivision(
      /*United States of America*/ "US", /*subdivision=*/"US-XX"));
}

}  // namespace qorai_ads
