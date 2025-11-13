/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_MAPPED_TOKENS_TRANSFORMATION_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_MAPPED_TOKENS_TRANSFORMATION_H_

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_ads/core/internal/ml/transformation/transformation.h"

namespace qorai_ads {

namespace neural_text_classification::flat {
struct MappedTokenTransformation;
}  // namespace neural_text_classification::flat

namespace ml {

class MappedTokensTransformation final : public Transformation {
 public:
  explicit MappedTokensTransformation(
      const neural_text_classification::flat::MappedTokenTransformation&
          mapped_token_transformation);

  ~MappedTokensTransformation() override;

  std::optional<std::map<uint32_t, double>> GetCategoryFrequencies(
      const std::vector<std::string>& words) const;

  std::unique_ptr<Data> Apply(
      const std::unique_ptr<Data>& input_data) const override;

 private:
  const raw_ref<
      const neural_text_classification::flat::MappedTokenTransformation>
      mapped_token_transformation_;
};

}  // namespace ml

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_MAPPED_TOKENS_TRANSFORMATION_H_
