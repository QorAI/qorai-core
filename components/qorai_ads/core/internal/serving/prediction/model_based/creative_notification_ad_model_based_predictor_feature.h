/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_NOTIFICATION_AD_MODEL_BASED_PREDICTOR_FEATURE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_NOTIFICATION_AD_MODEL_BASED_PREDICTOR_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace qorai_ads {

BASE_DECLARE_FEATURE(kCreativeNotificationAdModelBasedPredictorFeature);

inline constexpr base::FeatureParam<double>
    kNotificationAdChildIntentSegmentPredictorWeight{
        &kCreativeNotificationAdModelBasedPredictorFeature,
        "child_intent_segment_predictor_weight", 1.0};
inline constexpr base::FeatureParam<double>
    kNotificationAdParentIntentSegmentPredictorWeight{
        &kCreativeNotificationAdModelBasedPredictorFeature,
        "parent_intent_segment_predictor_weight", 1.0};

inline constexpr base::FeatureParam<double>
    kNotificationAdChildLatentInterestSegmentPredictorWeight{
        &kCreativeNotificationAdModelBasedPredictorFeature,
        "child_latent_interest_segment_predictor_weight", 1.0};
inline constexpr base::FeatureParam<double>
    kNotificationAdParentLatentInterestSegmentPredictorWeight{
        &kCreativeNotificationAdModelBasedPredictorFeature,
        "parent_latent_interest_segment_predictor_weight", 1.0};

inline constexpr base::FeatureParam<double>
    kNotificationAdChildInterestSegmentPredictorWeight{
        &kCreativeNotificationAdModelBasedPredictorFeature,
        "child_interest_segment_predictor_weight", 1.0};
inline constexpr base::FeatureParam<double>
    kNotificationAdParentInterestSegmentPredictorWeight{
        &kCreativeNotificationAdModelBasedPredictorFeature,
        "parent_interest_segment_predictor_weight", 1.0};

inline constexpr base::FeatureParam<double>
    kNotificationAdUntargetedSegmentPredictorWeight{
        &kCreativeNotificationAdModelBasedPredictorFeature,
        "untargeted_segment_predictor_weight", 0.0001};

inline constexpr base::FeatureParam<double>
    kNotificationAdLastSeenPredictorWeight{
        &kCreativeNotificationAdModelBasedPredictorFeature,
        "last_seen_ad_predictor_weight", 0.0};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_CREATIVE_NOTIFICATION_AD_MODEL_BASED_PREDICTOR_FEATURE_H_
