/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/qorai_ads/color_util.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/skia/include/core/SkColor.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsColorUtilTest, RgbStringToSkColor) {
  SkColor color;
  EXPECT_TRUE(RgbStringToSkColor("42fe4c", &color));
}

TEST(QoraiAdsColorUtilTest, DoNotConvertInvalidRgbStringToSkColor) {
  SkColor color;
  EXPECT_FALSE(RgbStringToSkColor("42fe4", &color));
}

TEST(QoraiAdsColorUtilTest, DoNotConvertEmptyRgbStringToSkColor) {
  SkColor color;
  EXPECT_FALSE(RgbStringToSkColor("", &color));
}

TEST(QoraiAdsColorUtilTest, DoNotConvertNonHexadecimalRgbStringToSkColor) {
  SkColor color;
  EXPECT_FALSE(RgbStringToSkColor("xxxxxx", &color));
}

}  // namespace qorai_ads
