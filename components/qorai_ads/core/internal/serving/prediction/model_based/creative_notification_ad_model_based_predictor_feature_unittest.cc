/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/creative_notification_ad_model_based_predictor_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsCreativeNotificationAdModelBasedPredictorFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(
      kCreativeNotificationAdModelBasedPredictorFeature));
}

TEST(QoraiAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     ChildIntentSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(1.0, kNotificationAdChildIntentSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     ParentIntentSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(1.0,
                   kNotificationAdParentIntentSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     ChildLatentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      1.0, kNotificationAdChildLatentInterestSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     ParentLatentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      1.0, kNotificationAdParentLatentInterestSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     ChildInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(1.0,
                   kNotificationAdChildInterestSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     ParentInterestSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(1.0,
                   kNotificationAdParentInterestSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     UntargetedSegmentAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0001,
                   kNotificationAdUntargetedSegmentPredictorWeight.Get());
}

TEST(QoraiAdsCreativeNotificationAdModelBasedPredictorFeatureTest,
     LastSeenAdPredictorWeight) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, kNotificationAdLastSeenPredictorWeight.Get());
}

}  // namespace qorai_ads
