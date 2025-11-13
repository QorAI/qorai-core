/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_INFO_H_

#include <vector>

#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/input_variable/creative_ad_model_based_predictor_input_variable_info.h"

namespace qorai_ads {

template <typename T>
struct CreativeAdModelBasedPredictorInfo final {
  bool operator==(const CreativeAdModelBasedPredictorInfo<T>&) const = default;

  T creative_ad;
  CreativeAdModelBasedPredictorInputVariableInfo input_variable;
  double score = 0.0;
};

template <typename T>
using CreativeAdModelBasedPredictorList =
    std::vector<CreativeAdModelBasedPredictorInfo<T>>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_INFO_H_
