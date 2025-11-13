/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_TEST_HELPER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_TEST_HELPER_H_

#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_processor.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_resource.h"

namespace qorai_ads::test {

class PurchaseIntentHelper final {
 public:
  PurchaseIntentHelper();

  PurchaseIntentHelper(const PurchaseIntentHelper&) = delete;
  PurchaseIntentHelper& operator=(const PurchaseIntentHelper&) = delete;

  ~PurchaseIntentHelper();

  void Mock();

  static SegmentList Expectation();

 private:
  PurchaseIntentResource resource_;
  PurchaseIntentProcessor processor_;
};

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_TEST_HELPER_H_
