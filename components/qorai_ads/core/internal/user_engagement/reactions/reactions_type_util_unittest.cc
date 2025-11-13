/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/reactions/reactions_type_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsReactionsTypeUtilTest : public test::TestBase {};

TEST_F(QoraiAdsReactionsTypeUtilTest,
       ToggleLikedReactionTypeFromNeutralToLiked) {
  // Act & Assert
  EXPECT_EQ(mojom::ReactionType::kLiked,
            ToggleLikedReactionType(mojom::ReactionType::kNeutral));
}

TEST_F(QoraiAdsReactionsTypeUtilTest,
       ToggleLikedReactionTypeFromLikedToNeutral) {
  // Act & Assert
  EXPECT_EQ(mojom::ReactionType::kNeutral,
            ToggleLikedReactionType(mojom::ReactionType::kLiked));
}

TEST_F(QoraiAdsReactionsTypeUtilTest,
       ToggleLikedReactionTypeFromDislikedToLiked) {
  // Act & Assert
  EXPECT_EQ(mojom::ReactionType::kLiked,
            ToggleLikedReactionType(mojom::ReactionType::kDisliked));
}

TEST_F(QoraiAdsReactionsTypeUtilTest,
       ToggleDislikedReactionTypeFromNeutralToDisliked) {
  // Act & Assert
  EXPECT_EQ(mojom::ReactionType::kDisliked,
            ToggleDislikedReactionType(mojom::ReactionType::kNeutral));
}

TEST_F(QoraiAdsReactionsTypeUtilTest,
       ToggleDislikedReactionTypeFromDislikedToNeutral) {
  // Act & Assert
  EXPECT_EQ(mojom::ReactionType::kNeutral,
            ToggleDislikedReactionType(mojom::ReactionType::kDisliked));
}

TEST_F(QoraiAdsReactionsTypeUtilTest,
       ToggleDislikedReactionTypeFromLikedToDisliked) {
  // Act & Assert
  EXPECT_EQ(mojom::ReactionType::kDisliked,
            ToggleDislikedReactionType(mojom::ReactionType::kLiked));
}

}  // namespace qorai_ads
