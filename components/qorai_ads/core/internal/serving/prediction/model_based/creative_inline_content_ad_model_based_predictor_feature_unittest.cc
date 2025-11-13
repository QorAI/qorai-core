/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/creative_inline_content_ad_model_based_predictor_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsCreativeInlineContentAdModelBasedPredictorFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(
      kCreativeInlineContentAdModelBasedPredictorFeature));
}

TEST(QoraiAdsCreativeInlineContentAdModelBasedPredictorFeatureTest,
     ChildIntentSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0,
                   kInlineContentAdChildIntentSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeInlineContentAdModelBasedPredictorFeatureTest,
     ParentIntentSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0,
                   kInlineContentAdParentIntentSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeInlineContentAdModelBasedPredictorFeatureTest,
     ChildLatentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      0.0, kInlineContentAdChildLatentInterestSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeInlineContentAdModelBasedPredictorFeatureTest,
     ParentLatentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      0.0, kInlineContentAdParentLatentInterestSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeInlineContentAdModelBasedPredictorFeatureTest,
     ChildInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0,
                   kInlineContentAdChildInterestSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeInlineContentAdModelBasedPredictorFeatureTest,
     ParentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0,
                   kInlineContentAdParentInterestSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeInlineContentAdModelBasedPredictorFeatureTest,
     UntargetedSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0001,
                   kInlineContentAdUntargetedSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeInlineContentAdModelBasedPredictorFeatureTest,
     LastSeenAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, kInlineContentAdLastSeenPredictorWeight.Get());
}

}  // namespace qorai_ads
