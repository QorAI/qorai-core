/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_WEIGHT_CREATIVE_AD_MODEL_BASED_PREDICTOR_WEIGHTS_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_WEIGHT_CREATIVE_AD_MODEL_BASED_PREDICTOR_WEIGHTS_INFO_H_

#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/weight/segment/creative_ad_model_based_predictor_segment_weight_info.h"

namespace qorai_ads {

struct CreativeAdModelBasedPredictorWeightsInfo final {
  bool operator==(const CreativeAdModelBasedPredictorWeightsInfo&) const =
      default;

  CreativeAdModelBasedPredictorSegmentWeightInfo intent_segment;
  CreativeAdModelBasedPredictorSegmentWeightInfo latent_interest_segment;
  CreativeAdModelBasedPredictorSegmentWeightInfo interest_segment;

  double untargeted_segment = 0.0;

  double last_seen_ad = 0.0;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_WEIGHT_CREATIVE_AD_MODEL_BASED_PREDICTOR_WEIGHTS_INFO_H_
