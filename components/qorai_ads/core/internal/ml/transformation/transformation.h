/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_TRANSFORMATION_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_TRANSFORMATION_H_

#include <memory>

#include "qorai/components/qorai_ads/core/internal/ml/transformation/transformation_types.h"

namespace qorai_ads::ml {

class Data;

class Transformation {
 public:
  explicit Transformation(TransformationType type);

  virtual ~Transformation();

  TransformationType GetType() const;

  virtual std::unique_ptr<Data> Apply(
      const std::unique_ptr<Data>& input_data) const = 0;

 protected:
  const TransformationType type_;
};

}  // namespace qorai_ads::ml

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_TRANSFORMATION_H_
