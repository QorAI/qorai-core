/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/creative_new_tab_page_ad_model_based_predictor_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(
      kCreativeNewTabPageAdModelBasedPredictorFeature));
}

TEST(QoraiAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     ChildIntentSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, kNewTabPageAdChildIntentSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     ParentIntentSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, kNewTabPageAdParentIntentSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     ChildLatentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      0.0, kNewTabPageAdChildLatentInterestSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     ParentLatentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      0.0, kNewTabPageAdParentLatentInterestSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     ChildInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, kNewTabPageAdChildInterestSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     ParentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0,
                   kNewTabPageAdParentInterestSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     UntargetedSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0001, kNewTabPageAdUntargetedSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNewTabPageAdModelBasedPredictorFeatureTest,
     LastSeenAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, kNewTabPageAdLastSeenPredictorWeight.Get());
}

}  // namespace qorai_ads
