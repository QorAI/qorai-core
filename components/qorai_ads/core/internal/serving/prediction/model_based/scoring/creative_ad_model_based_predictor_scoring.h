/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_SCORING_CREATIVE_AD_MODEL_BASED_PREDICTOR_SCORING_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_SCORING_CREATIVE_AD_MODEL_BASED_PREDICTOR_SCORING_H_

namespace qorai_ads {

struct CreativeAdModelBasedPredictorInputVariableInfo;

double ComputeCreativeAdModelBasedPredictorScore(
    const CreativeAdModelBasedPredictorInputVariableInfo& input_variable);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_SCORING_CREATIVE_AD_MODEL_BASED_PREDICTOR_SCORING_H_
