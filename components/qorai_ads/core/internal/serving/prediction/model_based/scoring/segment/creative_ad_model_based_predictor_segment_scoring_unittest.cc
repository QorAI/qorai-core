/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/scoring/segment/creative_ad_model_based_predictor_segment_scoring.h"

#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/input_variable/segment/creative_ad_model_based_predictor_segment_input_variables_info.h"
#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/input_variable/segment/creative_ad_model_based_predictor_untargeted_segment_input_variable_info.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsCreativeAdModelBasedPredictorSegmentScoringTest,
     ComputeMatchingChildSegmentScore) {
  // Arrange
  CreativeAdModelBasedPredictorSegmentInputVariablesInfo segment_input_variable;
  segment_input_variable.child_matches.value = true;

  // Act & Assert
  EXPECT_DOUBLE_EQ(1.0, ComputeSegmentScore(segment_input_variable));
}

TEST(QoraiAdsCreativeAdModelBasedPredictorSegmentScoringTest,
     ComputeMatchingParentSegmentScore) {
  // Arrange
  CreativeAdModelBasedPredictorSegmentInputVariablesInfo segment_input_variable;
  segment_input_variable.parent_matches.value = true;

  // Act & Assert
  EXPECT_DOUBLE_EQ(1.0, ComputeSegmentScore(segment_input_variable));
}

TEST(QoraiAdsCreativeAdModelBasedPredictorSegmentScoringTest,
     ComputeNonMatchingSegmentScore) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      0.0, ComputeSegmentScore(
               CreativeAdModelBasedPredictorSegmentInputVariablesInfo{}));
}

TEST(QoraiAdsCreativeAdModelBasedPredictorSegmentScoringTest,
     ComputeMatchingUntargetedSegmentScore) {
  // Arrange
  CreativeAdModelBasedPredictorUntargetedSegmentInputVariableInfo
      segment_input_variable;
  segment_input_variable.value = true;

  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0001, ComputeSegmentScore(segment_input_variable));
}

TEST(QoraiAdsCreativeAdModelBasedPredictorSegmentScoringTest,
     ComputeNonMatchingUntargetedSegmentScore) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      0.0,
      ComputeSegmentScore(
          CreativeAdModelBasedPredictorUntargetedSegmentInputVariableInfo{}));
}

}  // namespace qorai_ads
