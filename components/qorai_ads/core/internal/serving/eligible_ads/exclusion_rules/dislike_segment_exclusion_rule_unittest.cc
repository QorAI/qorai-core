/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/dislike_segment_exclusion_rule.h"

#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/ads_core/ads_core_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsDislikeSegmentExclusionRuleTest : public test::TestBase {
 protected:
  const DislikeSegmentExclusionRule exclusion_rule_;
};

TEST_F(QoraiAdsDislikeSegmentExclusionRuleTest,
       ShouldIncludeForNeutralReaction) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.segment = test::kSegment;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsDislikeSegmentExclusionRuleTest, ShouldIncludeForLikedReaction) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {test::kSegment, mojom::ReactionType::kLiked}};

  CreativeAdInfo creative_ad;
  creative_ad.segment = test::kSegment;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsDislikeSegmentExclusionRuleTest,
       ShouldExcludeForDislikedReaction) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {test::kSegment, mojom::ReactionType::kDisliked}};

  CreativeAdInfo creative_ad;
  creative_ad.segment = test::kSegment;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

}  // namespace qorai_ads
