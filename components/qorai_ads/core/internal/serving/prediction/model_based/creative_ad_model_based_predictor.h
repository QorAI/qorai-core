/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_H_

#include <optional>
#include <vector>

#include "base/check.h"
#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/creative_ad_model_based_predictor_info.h"
#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/creative_ad_model_based_predictor_util.h"
#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/sampling/creative_ad_model_based_predictor_sampling.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_info.h"

namespace qorai_ads {

struct UserModelInfo;

template <typename T>
std::optional<T> MaybePredictCreativeAd(const std::vector<T>& creative_ads,
                                        const UserModelInfo& user_model,
                                        const AdEventList& ad_events) {
  CHECK(!creative_ads.empty());

  const CreativeAdModelBasedPredictorList<T> creative_ad_predictors =
      ComputeCreativeAdModelBasedPredictors(creative_ads, user_model,
                                            ad_events);

  return MaybeSampleCreativeAd(creative_ad_predictors);
}

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_AD_MODEL_BASED_PREDICTOR_H_
