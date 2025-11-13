/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_MODEL_PURCHASE_INTENT_MODEL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_MODEL_PURCHASE_INTENT_MODEL_H_

#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"

namespace qorai_ads {

struct PurchaseIntentSignalInfo;

void BuyPurchaseIntentSignal(
    const PurchaseIntentSignalInfo& purchase_intent_signal);

SegmentList GetPurchaseIntentSegments();

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_MODEL_PURCHASE_INTENT_MODEL_H_
