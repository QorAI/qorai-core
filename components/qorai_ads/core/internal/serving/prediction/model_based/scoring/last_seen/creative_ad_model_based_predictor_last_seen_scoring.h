/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_SCORING_LAST_SEEN_CREATIVE_AD_MODEL_BASED_PREDICTOR_LAST_SEEN_SCORING_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_SCORING_LAST_SEEN_CREATIVE_AD_MODEL_BASED_PREDICTOR_LAST_SEEN_SCORING_H_

namespace qorai_ads {

struct CreativeAdModelBasedPredictorLastSeenInputVariableInfo;

// The score computed by this function is used in the prediction model to
// determine which ad to serve to the user. The higher the score, the more
// likely the ad will be served.
double ComputeLastSeenScore(
    const CreativeAdModelBasedPredictorLastSeenInputVariableInfo&
        last_seen_input_variable);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_SCORING_LAST_SEEN_CREATIVE_AD_MODEL_BASED_PREDICTOR_LAST_SEEN_SCORING_H_
