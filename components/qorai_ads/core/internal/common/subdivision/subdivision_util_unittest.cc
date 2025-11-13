/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/subdivision/subdivision_util.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsSubdivisionUtilTest, GetSubdivisionCountryCode) {
  // Act & Assert
  EXPECT_EQ("US", GetSubdivisionCountryCode(/*subdivision=*/"US-CA"));
}

TEST(QoraiAdsSubdivisionUtilTest, DoNotGetSubdivisionCountryCode) {
  // Act & Assert
  EXPECT_FALSE(GetSubdivisionCountryCode(/*subdivision=*/""));
}

TEST(QoraiAdsSubdivisionUtilTest, GetSubdivisionCode) {
  // Act & Assert
  EXPECT_EQ("CA", GetSubdivisionCode(/*subdivision=*/"US-CA"));
}

TEST(QoraiAdsSubdivisionUtilTest, DoNotGetSubdivisionCode) {
  // Act & Assert
  EXPECT_FALSE(GetSubdivisionCode(/*subdivision=*/""));
}

}  // namespace qorai_ads
