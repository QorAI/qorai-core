/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/ads_util.h"

#include "qorai/components/qorai_ads/core/public/common/locale/scoped_locale_for_testing.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsAdsUtilTest, IsSupportedRegion) {
  // Arrange
  const test::ScopedCurrentCountryCode scoped_current_country_code{"US"};

  // Act & Assert
  EXPECT_TRUE(IsSupportedRegion());
}

TEST(QoraiAdsAdsUtilTest, IsUnsupportedRegion) {
  // Arrange
  const test::ScopedCurrentCountryCode scoped_current_country_code{
      /*cuba*/ "CU"};

  // Act & Assert
  EXPECT_FALSE(IsSupportedRegion());
}

}  // namespace qorai_ads
