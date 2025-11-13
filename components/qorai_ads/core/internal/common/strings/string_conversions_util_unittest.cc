/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/strings/string_conversions_util.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsStringConversionsUtilTest, TrueBoolToString) {
  // Act & Assert
  EXPECT_EQ("true", BoolToString(true));
}

TEST(QoraiAdsStringConversionsUtilTest, FalseBoolToString) {
  // Act & Assert
  EXPECT_EQ("false", BoolToString(false));
}

}  // namespace qorai_ads
