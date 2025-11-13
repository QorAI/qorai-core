/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/prediction/model_based/creative_notification_ad_model_based_predictor_feature.h"

namespace qorai_ads {

BASE_FEATURE(kCreativeNotificationAdModelBasedPredictorFeature,
             "CreativeNotificationAdModelBasedPredictor",
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace qorai_ads
