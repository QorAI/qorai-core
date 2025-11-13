/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/algorithm/split_vector_util.h"

#include <string>

#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsSplitVectorUtilTest, SplitVectorIntoSingleChunk) {
  // Arrange
  const std::vector<std::string> element = {"item 1", "item 2", "item 3",
                                            "item 4", "item 5", "item 6"};

  // Act
  const std::vector<std::vector<std::string>> elements =
      SplitVector(element, 6);

  // Assert
  EXPECT_THAT(elements, ::testing::SizeIs(1));
}

TEST(QoraiAdsSplitVectorUtilTest,
     SplitVectorIntoSingleChunkWhenChunkSizeIsLargerThanVectorSize) {
  // Arrange
  const std::vector<std::string> element = {"item 1", "item 2", "item 3",
                                            "item 4", "item 5", "item 6"};

  // Act
  const std::vector<std::vector<std::string>> elements =
      SplitVector(element, 7);

  // Assert
  const std::vector<std::vector<std::string>> expected_elements = {element};
  EXPECT_EQ(expected_elements, elements);
}

TEST(QoraiAdsSplitVectorUtilTest, SplitVectorIntoMultipleEvenChunks) {
  // Arrange
  const std::vector<std::string> element = {
      "item 1", "item 2", "item 3", "item 4", "item 5", "item 6",
  };

  // Act
  const std::vector<std::vector<std::string>> elements =
      SplitVector(element, 3);

  // Assert
  const std::vector<std::vector<std::string>> expected_elements = {
      {"item 1", "item 2", "item 3"}, {"item 4", "item 5", "item 6"}};
  EXPECT_EQ(expected_elements, elements);
}

TEST(QoraiAdsSplitVectorUtilTest, SplitVectorIntoMultipleUnevenChunks) {
  // Arrange
  const std::vector<std::string> element = {"item 1", "item 2", "item 3",
                                            "item 4", "item 5"};

  // Act
  const std::vector<std::vector<std::string>> elements =
      SplitVector(element, 3);

  // Assert
  const std::vector<std::vector<std::string>> expected_elements = {
      {"item 1", "item 2", "item 3"}, {"item 4", "item 5"}};
  EXPECT_EQ(expected_elements, elements);
}

TEST(QoraiAdsSplitVectorUtilTest, SplitEmptyVector) {
  // Arrange
  const std::vector<std::string> element;

  // Act
  const std::vector<std::vector<std::string>> elements =
      SplitVector(element, 5);

  // Assert
  EXPECT_THAT(elements, ::testing::IsEmpty());
}

}  // namespace qorai_ads
