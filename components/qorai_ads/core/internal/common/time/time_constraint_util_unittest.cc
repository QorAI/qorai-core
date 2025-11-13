/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/time/time_constraint_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsTimeConstraintUtilTest : public test::TestBase {};

TEST_F(QoraiAdsTimeConstraintUtilTest, DoesRespectIfNoHistory) {
  // Arrange
  const std::vector<base::Time> history;

  // Act & Assert
  EXPECT_TRUE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/1));
}

TEST_F(QoraiAdsTimeConstraintUtilTest, DoNotRespectTimeConstraintIfCapIsZero) {
  // Arrange
  const std::vector<base::Time> history;

  // Act & Assert
  EXPECT_TRUE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/0));
}

TEST_F(QoraiAdsTimeConstraintUtilTest,
       DoesRespectTimeConstraintIfNotExceededCap) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());

  // Act & Assert
  EXPECT_TRUE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/2));
}

TEST_F(QoraiAdsTimeConstraintUtilTest,
       DoesNotRespectTimeConstraintIfExceededCap) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());
  history.push_back(test::Now());

  // Act & Assert
  EXPECT_FALSE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/2));
}

TEST_F(QoraiAdsTimeConstraintUtilTest,
       DoesRespectTimeConstraintIfTimeConstraintHasPassed) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());

  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_TRUE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/1));
}

TEST_F(QoraiAdsTimeConstraintUtilTest,
       DoesRespectTimeConstraintOnCuspIfNotExceededCap) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());

  AdvanceClockBy(base::Days(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_TRUE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/2));
}

TEST_F(QoraiAdsTimeConstraintUtilTest,
       DoesNotRespectTimeConstraintOnCuspIfExceededCap) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());

  AdvanceClockBy(base::Days(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_FALSE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/1));
}

TEST_F(
    QoraiAdsTimeConstraintUtilTest,
    DoesRespectTimeConstraintIfHistorySizeIsHigherThanRemainingCapAndTimeConstraintHasPassed) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());
  history.push_back(test::Now());

  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_TRUE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/1));
}

TEST_F(QoraiAdsTimeConstraintUtilTest,
       DoesNotRespectTimeConstraintIfHistorySizeIsHigherThanRemainingCap) {
  // Arrange
  std::vector<base::Time> history;
  history.push_back(test::Now());
  history.push_back(test::Now());

  // Act & Assert
  EXPECT_FALSE(DoesHistoryRespectRollingTimeConstraint(
      history, /*time_constraint=*/base::Days(1), /*cap=*/1));
}

}  // namespace qorai_ads
