/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/dislike_exclusion_rule.h"

#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/ads_core/ads_core_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsDislikeExclusionRuleTest : public test::TestBase {
 protected:
  const DislikeExclusionRule exclusion_rule_;
};

TEST_F(QoraiAdsDislikeExclusionRuleTest, ShouldIncludeForNeutralReaction) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.advertiser_id = test::kAdvertiserId;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsDislikeExclusionRuleTest, ShouldIncludeForLikedReaction) {
  // Arrange
  GetReactions().AdsForTesting() = {
      {test::kAdvertiserId, mojom::ReactionType::kLiked}};

  CreativeAdInfo creative_ad;
  creative_ad.advertiser_id = test::kAdvertiserId;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsDislikeExclusionRuleTest, ShouldExcludeForDislikedReaction) {
  // Arrange
  GetReactions().AdsForTesting() = {
      {test::kAdvertiserId, mojom::ReactionType::kDisliked}};

  CreativeAdInfo creative_ad;
  creative_ad.advertiser_id = test::kAdvertiserId;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

}  // namespace qorai_ads
