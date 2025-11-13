/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/segments/segment_value_util.h"

#include "base/test/values_test_util.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

namespace {

constexpr char kSegmentsAsJson[] =
    R"JSON(
        [
          "technology & computing",
          "personal finance-banking",
          "food & drink-restaurants"
        ])JSON";

}  // namespace

TEST(QoraiAdsSegmentValueUtilTest, SegmentsToValue) {
  // Act
  const base::Value::List list =
      SegmentsToValue({"technology & computing", "personal finance-banking",
                       "food & drink-restaurants"});

  // Assert
  EXPECT_EQ(base::test::ParseJsonList(kSegmentsAsJson), list);
}

TEST(QoraiAdsSegmentValueUtilTest, EmptySegmentsToValue) {
  // Act
  const base::Value::List list = SegmentsToValue({});

  // Assert
  EXPECT_THAT(list, ::testing::IsEmpty());
}

TEST(QoraiAdsSegmentValueUtilTest, SegmentsFromValue) {
  // Arrange
  const base::Value::List list = base::test::ParseJsonList(kSegmentsAsJson);

  // Act
  const SegmentList segments = SegmentsFromValue(list);

  // Assert
  const SegmentList expected_segments = {"technology & computing",
                                         "personal finance-banking",
                                         "food & drink-restaurants"};
  EXPECT_EQ(expected_segments, segments);
}

TEST(QoraiAdsSegmentValueUtilTest, EmptySegmentsFromValue) {
  // Act & Assert
  EXPECT_THAT(SegmentsFromValue({}), ::testing::IsEmpty());
}

}  // namespace qorai_ads
