/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_ML_PREDICTION_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_ML_PREDICTION_UTIL_H_

#include "qorai/components/qorai_ads/core/internal/ml/ml_alias.h"

namespace qorai_ads::ml {

PredictionMap Softmax(const PredictionMap& predictions);

}  // namespace qorai_ads::ml

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_ML_PREDICTION_UTIL_H_
