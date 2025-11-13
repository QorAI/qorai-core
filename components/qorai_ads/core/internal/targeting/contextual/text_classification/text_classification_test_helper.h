/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEXT_CLASSIFICATION_TEST_HELPER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEXT_CLASSIFICATION_TEST_HELPER_H_

#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"
#include "qorai/components/qorai_ads/core/internal/targeting/contextual/text_classification/resource/text_classification_resource.h"
#include "qorai/components/qorai_ads/core/internal/targeting/contextual/text_classification/text_classification_processor.h"

namespace qorai_ads::test {

class TextClassificationHelper final {
 public:
  TextClassificationHelper();

  TextClassificationHelper(const TextClassificationHelper&) = delete;
  TextClassificationHelper& operator=(const TextClassificationHelper&) = delete;

  ~TextClassificationHelper();

  void Mock();

  static SegmentList Expectation();

 private:
  TextClassificationResource resource_;
  TextClassificationProcessor processor_;
};

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEXT_CLASSIFICATION_TEST_HELPER_H_
