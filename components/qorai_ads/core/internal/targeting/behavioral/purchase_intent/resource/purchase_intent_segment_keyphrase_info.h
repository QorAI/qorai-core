/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_SEGMENT_KEYPHRASE_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_SEGMENT_KEYPHRASE_INFO_H_

#include <vector>

#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/keyphrase/purchase_intent_keyphrase_alias.h"

namespace qorai_ads {

struct PurchaseIntentSegmentKeyphraseInfo final {
  PurchaseIntentSegmentKeyphraseInfo();
  PurchaseIntentSegmentKeyphraseInfo(SegmentList segments,
                                     KeywordList keywords);

  PurchaseIntentSegmentKeyphraseInfo(
      const PurchaseIntentSegmentKeyphraseInfo&) = delete;
  PurchaseIntentSegmentKeyphraseInfo& operator=(
      const PurchaseIntentSegmentKeyphraseInfo&) = delete;

  PurchaseIntentSegmentKeyphraseInfo(
      PurchaseIntentSegmentKeyphraseInfo&&) noexcept;
  PurchaseIntentSegmentKeyphraseInfo& operator=(
      PurchaseIntentSegmentKeyphraseInfo&&) noexcept;

  ~PurchaseIntentSegmentKeyphraseInfo();

  SegmentList segments;
  KeywordList keywords;
};

using PurchaseIntentSegmentKeyphraseList =
    std::vector<PurchaseIntentSegmentKeyphraseInfo>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_SEGMENT_KEYPHRASE_INFO_H_
