/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_RESOURCE_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_RESOURCE_INFO_H_

#include <optional>

#include "base/values.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_funnel_info.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_funnel_keyphrase_info.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_segment_keyphrase_info.h"

namespace qorai_ads {

struct PurchaseIntentResourceInfo final {
  PurchaseIntentResourceInfo();

  PurchaseIntentResourceInfo(const PurchaseIntentResourceInfo&) = delete;
  PurchaseIntentResourceInfo& operator=(const PurchaseIntentResourceInfo&) =
      delete;

  PurchaseIntentResourceInfo(PurchaseIntentResourceInfo&&) noexcept;
  PurchaseIntentResourceInfo& operator=(PurchaseIntentResourceInfo&&) noexcept;

  ~PurchaseIntentResourceInfo();

  static std::optional<PurchaseIntentResourceInfo> CreateFromValue(
      base::Value::Dict dict);

  std::optional<int> version;
  PurchaseIntentSegmentKeyphraseList segment_keyphrases;
  PurchaseIntentFunnelKeyphraseList funnel_keyphrases;
  PurchaseIntentFunnelSiteMap funnel_sites;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_RESOURCE_INFO_H_
