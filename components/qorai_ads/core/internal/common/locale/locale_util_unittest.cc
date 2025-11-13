/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/common/locale/locale_util.h"

#include "qorai/components/qorai_ads/core/public/common/locale/scoped_locale_for_testing.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsLocaleUtilTest, CurrentLanguageCode) {
  // Arrange
  const test::ScopedCurrentLanguageCode scoped_current_language_code{"en"};

  // Act & Assert
  EXPECT_EQ("en", CurrentLanguageCode());
}

TEST(QoraiAdsLocaleUtilTest, CurrentCountryCode) {
  // Arrange
  const test::ScopedCurrentCountryCode scoped_current_country_code{"KY"};

  // Act & Assert
  EXPECT_EQ("KY", CurrentCountryCode());
}

}  // namespace qorai_ads
