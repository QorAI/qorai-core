/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/segments/segment_util.h"

#include <optional>

#include "qorai/components/qorai_ads/core/internal/ads_core/ads_core_util.h"
#include "qorai/components/qorai_ads/core/internal/catalog/catalog_info.h"
#include "qorai/components/qorai_ads/core/internal/catalog/catalog_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/catalog/catalog_url_request_json_reader.h"
#include "qorai/components/qorai_ads/core/internal/common/test/file_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsSegmentUtilTest : public test::TestBase {};

TEST_F(QoraiAdsSegmentUtilTest, GetSegmentsFromCatalog) {
  // Arrange
  std::optional<std::string> contents =
      test::MaybeReadFileToStringAndReplaceTags(
          test::kCatalogWithMultipleCampaignsJsonFilename);
  ASSERT_TRUE(contents);

  std::optional<CatalogInfo> catalog = json::reader::ReadCatalog(*contents);
  ASSERT_TRUE(catalog);

  // Act
  const SegmentList segments = GetSegments(*catalog);

  // Assert
  const SegmentList expected_segments = {"technology & computing",
                                         "untargeted"};
  EXPECT_EQ(expected_segments, segments);
}

TEST_F(QoraiAdsSegmentUtilTest, GetSegmentsFromEmptyCatalog) {
  // Act & Assert
  EXPECT_THAT(GetSegments(/*catalog=*/{}), ::testing::IsEmpty());
}

TEST_F(QoraiAdsSegmentUtilTest, GetParentSegmentFromParentChildSegment) {
  // Act & Assert
  EXPECT_EQ("technology & computing",
            GetParentSegment("technology & computing-software"));
}

TEST_F(QoraiAdsSegmentUtilTest, GetParentSegmentFromParentSegment) {
  // Act & Assert
  EXPECT_EQ("technology & computing",
            GetParentSegment("technology & computing"));
}

TEST_F(QoraiAdsSegmentUtilTest, GetParentSegments) {
  // Arrange
  const SegmentList segments = {"technology & computing-software",
                                "personal finance-personal finance",
                                "automotive"};

  // Act
  const SegmentList parent_segments = GetParentSegments(segments);

  // Assert
  const SegmentList expected_parent_segments = {
      "technology & computing", "personal finance", "automotive"};
  EXPECT_EQ(expected_parent_segments, parent_segments);
}

TEST_F(QoraiAdsSegmentUtilTest, GetParentSegmentsForEmptyList) {
  // Act & Assert
  EXPECT_THAT(GetParentSegments(/*segments=*/{}), ::testing::IsEmpty());
}

TEST_F(QoraiAdsSegmentUtilTest, ShouldFilterMatchingParentChildSegment) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {"parent-child", mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_TRUE(ShouldFilterSegment("parent-child"));
}

TEST_F(QoraiAdsSegmentUtilTest, ShouldNotFilterNonMatchingParentChildSegment) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {"parent-child", mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_FALSE(ShouldFilterSegment("foo-bar"));
}

TEST_F(QoraiAdsSegmentUtilTest, ShouldFilterMatchingParentSegment) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {"parent", mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_TRUE(ShouldFilterSegment("parent"));
}

TEST_F(QoraiAdsSegmentUtilTest, ShouldNotFilterNonMatchingParentSegment) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {"parent", mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_FALSE(ShouldFilterSegment("foo"));
}

TEST_F(QoraiAdsSegmentUtilTest,
       ShouldFilterAgainstParentForMatchingParentSegmentWithChild) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {"parent", mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_TRUE(ShouldFilterSegment("parent-child"));
}

TEST_F(QoraiAdsSegmentUtilTest,
       ShouldNotFilterAgainstParentForNonMatchingParentSegmentWithChild) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {"parent", mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_FALSE(ShouldFilterSegment("foo-bar"));
}

TEST_F(QoraiAdsSegmentUtilTest, HasChildSegment) {
  // Act & Assert
  EXPECT_TRUE(HasChildSegment("technology & computing-windows"));
}

TEST_F(QoraiAdsSegmentUtilTest, DoesNotHaveChildSegment) {
  // Act & Assert
  EXPECT_FALSE(HasChildSegment("technology & computing"));
}

}  // namespace qorai_ads
