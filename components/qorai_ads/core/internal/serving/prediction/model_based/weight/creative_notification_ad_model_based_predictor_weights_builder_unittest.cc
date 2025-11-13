/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/weight/creative_notification_ad_model_based_predictor_weights_builder.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/weight/creative_ad_model_based_predictor_weights_info.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsCreativeNotificationAdModelBasedPredictorWeightsBuilderTest
    : public test::TestBase {};

TEST_F(QoraiAdsCreativeNotificationAdModelBasedPredictorWeightsBuilderTest,
       BuildCreativeNotificationAdModelBasedPredictorWeights) {
  // Act
  const CreativeAdModelBasedPredictorWeightsInfo weights =
      BuildCreativeNotificationAdModelBasedPredictorWeights();

  // Assert
  CreativeAdModelBasedPredictorWeightsInfo expected_weights;
  expected_weights.intent_segment.child = 1.0;
  expected_weights.intent_segment.parent = 1.0;
  expected_weights.latent_interest_segment.child = 1.0;
  expected_weights.latent_interest_segment.parent = 1.0;
  expected_weights.interest_segment.child = 1.0;
  expected_weights.interest_segment.parent = 1.0;
  expected_weights.untargeted_segment = 0.0001;
  expected_weights.last_seen_ad = 0.0;
  EXPECT_EQ(expected_weights, weights);
}

}  // namespace qorai_ads
