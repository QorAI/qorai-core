/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_ML_ALIAS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_ML_ALIAS_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "qorai/components/qorai_ads/core/internal/ml/transformation/transformation.h"

namespace qorai_ads::ml {

using PredictionMap = std::map</*class*/ std::string, /*prediction*/ double>;
using TransformationPtr = std::unique_ptr<Transformation>;
using TransformationVector = std::vector<TransformationPtr>;

}  // namespace qorai_ads::ml

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_ML_ALIAS_H_
