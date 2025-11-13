/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_FUNNEL_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_FUNNEL_INFO_H_

#include <map>
#include <string>

#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"

namespace qorai_ads {

struct PurchaseIntentFunnelInfo final {
  PurchaseIntentFunnelInfo();
  PurchaseIntentFunnelInfo(SegmentList segments, int weight);

  PurchaseIntentFunnelInfo(const PurchaseIntentFunnelInfo&);
  PurchaseIntentFunnelInfo& operator=(const PurchaseIntentFunnelInfo&);

  PurchaseIntentFunnelInfo(PurchaseIntentFunnelInfo&&) noexcept;
  PurchaseIntentFunnelInfo& operator=(PurchaseIntentFunnelInfo&&) noexcept;

  ~PurchaseIntentFunnelInfo();

  bool operator==(const PurchaseIntentFunnelInfo&) const = default;

  SegmentList segments;
  int weight = 0;
};

using PurchaseIntentFunnelSiteMap =
    std::map</*url*/ std::string, PurchaseIntentFunnelInfo>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_FUNNEL_INFO_H_
