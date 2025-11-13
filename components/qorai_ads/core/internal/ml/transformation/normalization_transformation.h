/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_NORMALIZATION_TRANSFORMATION_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_NORMALIZATION_TRANSFORMATION_H_

#include <memory>

#include "qorai/components/qorai_ads/core/internal/ml/transformation/transformation.h"

namespace qorai_ads::ml {

class NormalizationTransformation final : public Transformation {
 public:
  NormalizationTransformation();

  std::unique_ptr<Data> Apply(
      const std::unique_ptr<Data>& input_data) const override;
};

}  // namespace qorai_ads::ml

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_NORMALIZATION_TRANSFORMATION_H_
