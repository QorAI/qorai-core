/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/algorithm/count_if_until_util.h"

#include <cstddef>
#include <vector>

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsCountIfUntilUtilTest,
     CountIfUntilWithEmptyContainerAndStopPredicate) {
  // Arrange
  const std::vector<int> container;
  const auto predicate = [](int number) { return number % 2 == 0; };
  const auto stop_predicate = [](size_t count) { return count == 3; };

  // Act & Assert
  EXPECT_EQ(0U, count_if_until(container, predicate, stop_predicate));
}

TEST(QoraiAdsCountIfUntilUtilTest, CountIfUntilWithStopPredicate) {
  // Arrange
  const std::vector<int> container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const auto predicate = [](int number) { return number % 2 == 0; };
  const auto stop_predicate = [](size_t count) { return count == 3; };

  // Act & Assert
  EXPECT_EQ(3U, count_if_until(container, predicate, stop_predicate));
}

TEST(QoraiAdsCountIfUntilUtilTest, CountIfUntilWithEmptyContainerAndStopCount) {
  // Arrange
  const std::vector<int> container;
  const auto predicate = [](int number) { return number % 2 == 0; };
  const size_t stop_count{0};

  // Act & Assert
  EXPECT_EQ(0U, count_if_until(container, predicate, stop_count));
}

TEST(QoraiAdsCountIfUntilUtilTest, CountIfUntilWithStopCount) {
  // Arrange
  const std::vector<int> container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const auto predicate = [](int number) { return number % 2 == 0; };
  const size_t stop_count{3};

  // Act & Assert
  EXPECT_EQ(3U, count_if_until(container, predicate, stop_count));
}

}  // namespace qorai_ads
