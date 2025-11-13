/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_HASH_VECTORIZER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_HASH_VECTORIZER_H_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace qorai_ads::ml {

class HashVectorizer final {
 public:
  HashVectorizer();
  HashVectorizer(int bucket_count, std::vector<uint32_t> subgrams);

  HashVectorizer(const HashVectorizer&) = delete;
  HashVectorizer& operator=(const HashVectorizer&) = delete;

  ~HashVectorizer();

  std::map<uint32_t, double> GetFrequencies(const std::string& html) const;

  std::vector<uint32_t> GetSubstringSizes() const;

  int GetBucketCount() const;

 private:
  std::vector<uint32_t> substring_sizes_;
  int bucket_count_;
};

}  // namespace qorai_ads::ml

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_TRANSFORMATION_HASH_VECTORIZER_H_
