/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/weight/creative_new_tab_page_ad_model_based_predictor_weights_builder.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/weight/creative_ad_model_based_predictor_weights_info.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsCreativeNewTabPageAdModelBasedPredictorWeightsBuilderTest
    : public test::TestBase {};

TEST_F(QoraiAdsCreativeNewTabPageAdModelBasedPredictorWeightsBuilderTest,
       BuildCreativeNewTabPageAdModelBasedPredictorWeights) {
  // Act
  const CreativeAdModelBasedPredictorWeightsInfo weights =
      BuildCreativeNewTabPageAdModelBasedPredictorWeights();

  // Assert
  CreativeAdModelBasedPredictorWeightsInfo expected_weights;
  expected_weights.intent_segment.child = 0.0;
  expected_weights.intent_segment.parent = 0.0;
  expected_weights.latent_interest_segment.child = 0.0;
  expected_weights.latent_interest_segment.parent = 0.0;
  expected_weights.interest_segment.child = 0.0;
  expected_weights.interest_segment.parent = 0.0;
  expected_weights.untargeted_segment = 0.0001;
  expected_weights.last_seen_ad = 0.0;
  EXPECT_EQ(expected_weights, weights);
}

}  // namespace qorai_ads
