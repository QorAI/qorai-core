/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/condition_matcher/matchers/internal/numerical_operator_condition_matcher_util_internal.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsNumericalOperatorConditionMatcherUtilInternalTest
    : public test::TestBase {};

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilInternalTest,
       ParseIntegerNumber) {
  // Act & Assert
  std::optional<double> number = ParseNumber("[R=]:1");
  ASSERT_TRUE(number);

  EXPECT_DOUBLE_EQ(1.0, *number);
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilInternalTest,
       ParseDoubleNumber) {
  // Act & Assert
  std::optional<double> number = ParseNumber("[R=]:1.0");
  ASSERT_TRUE(number);

  EXPECT_DOUBLE_EQ(1.0, *number);
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilInternalTest,
       DoNotParseMalformedNumber) {
  // Act & Assert
  EXPECT_FALSE(ParseNumber("[R=]: 1 "));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilInternalTest,
       DoNotParseInvalidNumber) {
  // Act & Assert
  EXPECT_FALSE(ParseNumber("[R=]:one"));
}

}  // namespace qorai_ads
