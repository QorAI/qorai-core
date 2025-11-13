/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_DATA_TEXT_DATA_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_DATA_TEXT_DATA_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/ml/data/data.h"

namespace qorai_ads::ml {

class TextData final : public Data {
 public:
  TextData();
  explicit TextData(std::string text);

  const std::string& GetText() const;

 private:
  std::string text_;
};

}  // namespace qorai_ads::ml

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_DATA_TEXT_DATA_H_
