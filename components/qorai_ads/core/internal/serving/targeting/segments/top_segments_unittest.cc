/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/segments/top_segments.h"

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

namespace {
constexpr size_t kSegmentsMaxCount = 2;
}  // namespace

class QoraiAdsTopSegmentsTest : public test::TestBase {};

TEST_F(QoraiAdsTopSegmentsTest, GetTopChildSegments) {
  // Arrange
  const SegmentList segments = {"parent_1-child", "parent_2-child",
                                "parent_3-child"};

  // Act
  const SegmentList top_segments = GetTopSegments(segments, kSegmentsMaxCount,
                                                  /*parent_only=*/false);

  // Assert
  const SegmentList expected_top_segments = {"parent_1-child",
                                             "parent_2-child"};
  EXPECT_EQ(expected_top_segments, top_segments);
}

TEST_F(QoraiAdsTopSegmentsTest, GetEmptyTopChildSegments) {
  // Act
  const SegmentList top_segments = GetTopSegments(
      /*segments=*/{}, kSegmentsMaxCount, /*parent_only=*/false);

  // Assert
  EXPECT_THAT(top_segments, ::testing::IsEmpty());
}

TEST_F(QoraiAdsTopSegmentsTest, GetTopParentSegments) {
  // Arrange
  const SegmentList segments = {"parent_1-child", "parent_2-child",
                                "parent_3-child"};

  // Act
  const SegmentList top_segments = GetTopSegments(segments, kSegmentsMaxCount,
                                                  /*parent_only=*/true);

  // Assert
  const SegmentList expected_top_segments = {"parent_1", "parent_2"};
  EXPECT_EQ(expected_top_segments, top_segments);
}

TEST_F(QoraiAdsTopSegmentsTest, GetEmptyTopParentSegments) {
  // Act
  const SegmentList top_segments = GetTopSegments(
      /*segments=*/{}, kSegmentsMaxCount, /*parent_only=*/false);

  // Assert
  EXPECT_THAT(top_segments, ::testing::IsEmpty());
}

}  // namespace qorai_ads
