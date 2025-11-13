/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/condition_matcher/matchers/numerical_operator_condition_matcher_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsNumericalOperatorConditionMatcherUtilTest
    : public test::TestBase {};

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest, IsOperator) {
  // Act & Assert
  EXPECT_TRUE(IsNumericalOperator("[R=]:1"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest, IsNotOperator) {
  // Act & Assert
  EXPECT_FALSE(IsNumericalOperator("[T=]:1"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchNonOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator("1", "baz"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchMalformedOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator("1", "[R=]: 1 "));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest, MatchEqualOperator) {
  // Act & Assert
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R=]:1"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R=]:1"));
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R=]:1.0"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R=]:1.0"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchEqualOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator("1.0", "[R=]:2"));
  EXPECT_FALSE(MatchNumericalOperator("1", "[R=]:2"));
  EXPECT_FALSE(MatchNumericalOperator("1.0", "[R=]:2.0"));
  EXPECT_FALSE(MatchNumericalOperator("1", "[R=]:2.0"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       MatchNotEqualOperator) {
  // Act & Assert
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R≠]:2"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R≠]:2"));
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R≠]:2.0"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R≠]:2.0"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchNotEqualOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator("1.0", "[R≠]:1"));
  EXPECT_FALSE(MatchNumericalOperator("1", "[R≠]:1"));
  EXPECT_FALSE(MatchNumericalOperator("1.0", "[R≠]:1.0"));
  EXPECT_FALSE(MatchNumericalOperator("1", "[R≠]:1.0"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       MatchGreaterThanOperator) {
  // Act & Assert
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R>]:0"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R>]:0"));
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R>]:0.0"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R>]:0.0"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchGreaterThanOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator("1.0", "[R>]:1"));
  EXPECT_FALSE(MatchNumericalOperator("1", "[R>]:1"));
  EXPECT_FALSE(MatchNumericalOperator("1.0", "[R>]:1.0"));
  EXPECT_FALSE(MatchNumericalOperator("1", "[R>]:1.0"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       MatchGreaterThanOrEqualOperator) {
  // Act & Assert
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R≥]:0"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R≥]:0"));
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R≥]:0.0"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R≥]:0.0"));

  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R≥]:1"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R≥]:1"));
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R≥]:1.0"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R≥]:1.0"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchGreaterThanOrEqualOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator("1.0", "[R≥]:2"));
  EXPECT_FALSE(MatchNumericalOperator("1", "[R≥]:2"));
  EXPECT_FALSE(MatchNumericalOperator("1.0", "[R≥]:2.0"));
  EXPECT_FALSE(MatchNumericalOperator("1", "[R≥]:2.0"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       MatchLessThanOperator) {
  // Act & Assert
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R<]:2"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R<]:2"));
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R<]:2.0"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R<]:2.0"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchLessThanOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator("1.0", "[R<]:1"));
  EXPECT_FALSE(MatchNumericalOperator("1", "[R<]:1"));
  EXPECT_FALSE(MatchNumericalOperator("1.0", "[R<]:1.0"));
  EXPECT_FALSE(MatchNumericalOperator("1", "[R<]:1.0"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       MatchLessThanOrEqualOperator) {
  // Act & Assert
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R≤]:1"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R≤]:1"));
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R≤]:1.0"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R≤]:1.0"));

  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R≤]:2"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R≤]:2"));
  EXPECT_TRUE(MatchNumericalOperator("1.0", "[R≤]:2.0"));
  EXPECT_TRUE(MatchNumericalOperator("1", "[R≤]:2.0"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchLessThanOrEqualOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator("1.0", "[R≤]:0"));
  EXPECT_FALSE(MatchNumericalOperator("1", "[R≤]:0"));
  EXPECT_FALSE(MatchNumericalOperator("1.0", "[R≤]:0.0"));
  EXPECT_FALSE(MatchNumericalOperator("1", "[R≤]:0.0"));
}

TEST_F(QoraiAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchUnknownOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator("1", "[_]:2"));
}

}  // namespace qorai_ads
