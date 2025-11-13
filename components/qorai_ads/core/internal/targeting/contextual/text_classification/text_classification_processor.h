/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEXT_CLASSIFICATION_PROCESSOR_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEXT_CLASSIFICATION_PROCESSOR_H_

#include <cstdint>
#include <string>
#include <vector>

#include "base/memory/raw_ref.h"
#include "base/memory/weak_ptr.h"
#include "base/types/optional_ref.h"
#include "qorai/components/qorai_ads/core/internal/tabs/tab_manager_observer.h"
#include "qorai/components/qorai_ads/core/internal/targeting/contextual/text_classification/model/text_classification_alias.h"

class GURL;

namespace qorai_ads {

class TextClassificationResource;

class TextClassificationProcessor final : public TabManagerObserver {
 public:
  explicit TextClassificationProcessor(TextClassificationResource& resource);

  TextClassificationProcessor(const TextClassificationProcessor&) = delete;
  TextClassificationProcessor& operator=(const TextClassificationProcessor&) =
      delete;

  ~TextClassificationProcessor() override;

  void Process(const std::string& text);

 private:
  void ClassifyPageCallback(
      uint64_t trace_id,
      base::optional_ref<const TextClassificationProbabilityMap> probabilities);

  // TabManagerObserver:
  void OnTextContentDidChange(int32_t tab_id,
                              const std::vector<GURL>& redirect_chain,
                              const std::string& text) override;

  const raw_ref<TextClassificationResource> resource_;

  base::WeakPtrFactory<TextClassificationProcessor> weak_factory_{this};
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEXT_CLASSIFICATION_PROCESSOR_H_
