/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/condition_matcher/matchers/epoch_operator_condition_matcher_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsEpochOperatorConditionMatcherUtilTest : public test::TestBase {};

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest, IsOperator) {
  // Act & Assert
  EXPECT_TRUE(IsEpochOperator("[T=]:1"));
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest, IsNotOperator) {
  // Act & Assert
  EXPECT_FALSE(IsEpochOperator("[R=]:1"));
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest, DoNotMatchNonOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchEpochOperator(
      "13372214400000000" /*1st October 2024 00:00:00 UTC*/, "baz"));
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchMalformedOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchEpochOperator(
      "13372214400000000" /*1st October 2024 00:00:00 UTC*/, "[T=]: 7 "));
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest, MatchEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_TRUE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T=]:2"));  // Event occurred 2 days ago.
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest, DoNotMatchEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T=]:3"));  // Event occurred 2 days ago.
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest, MatchNotEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_TRUE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T≠]:3"));  // Event occurred 2 days ago.
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchNotEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T≠]:2"));  // Event occurred 2 days ago.
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest,
       MatchGreaterThanOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_TRUE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T>]:1"));  // Event occurred 2 days ago.
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchGreaterThanOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T>]:2"));  // Event occurred 2 days ago.
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest,
       MatchGreaterThanOrEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_TRUE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T≥]:1"));  // Event occurred 2 days ago.
  EXPECT_TRUE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T≥]:2"));  // Event occurred 2 days ago.
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchGreaterThanOrEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T≥]:3"));  // Event occurred 2 days ago.
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest, MatchLessThanOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_TRUE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T<]:3"));  // Event occurred 2 days ago.
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchLessThanOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T<]:2"));  // Event occurred 2 days ago.
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest,
       MatchLessThanOrEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_TRUE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T≤]:3"));  // Event occurred 2 days ago.
  EXPECT_TRUE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T≤]:2"));  // Event occurred 2 days ago.
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchLessThanOrEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         "[T≤]:1"));  // Event occurred 2 days ago.
}

TEST_F(QoraiAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchUnknownOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(MatchEpochOperator(
      "13372214400000000" /*1st October 2024 00:00:00 UTC*/, "[T_]:2"));
}

}  // namespace qorai_ads
