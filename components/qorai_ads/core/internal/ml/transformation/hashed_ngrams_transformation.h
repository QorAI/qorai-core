/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_HASHED_NGRAMS_TRANSFORMATION_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_HASHED_NGRAMS_TRANSFORMATION_H_

#include <stdint.h>

#include <memory>
#include <string>
#include <vector>

#include "qorai/components/qorai_ads/core/internal/ml/transformation/transformation.h"

namespace qorai_ads::ml {

class HashVectorizer;

class HashedNGramsTransformation final : public Transformation {
 public:
  HashedNGramsTransformation();
  HashedNGramsTransformation(int bucket_count, std::vector<uint32_t> subgrams);

  HashedNGramsTransformation(
      HashedNGramsTransformation&& hashed_ngrams) noexcept;
  HashedNGramsTransformation& operator=(
      HashedNGramsTransformation&& hashed_ngrams) = delete;

  ~HashedNGramsTransformation() override;

  explicit HashedNGramsTransformation(const std::string& parameters);

  std::unique_ptr<Data> Apply(
      const std::unique_ptr<Data>& input_data) const override;

 private:
  std::unique_ptr<HashVectorizer> hash_vectorizer_;
};

}  // namespace qorai_ads::ml

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_HASHED_NGRAMS_TRANSFORMATION_H_
