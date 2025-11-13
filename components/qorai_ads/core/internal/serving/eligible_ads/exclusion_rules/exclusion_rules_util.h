/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULES_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULES_UTIL_H_

#include "base/check.h"
#include "base/trace_event/trace_event.h"
#include "qorai/components/qorai_ads/core/internal/creatives/creative_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rules_base.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/ad_info.h"
#include "qorai/components/qorai_ads/core/public/ads_constants.h"

namespace qorai_ads {

template <typename T>
bool CanCapLastServedCreativeAd(T& creative_ads) {
  return creative_ads.size() != 1;
}

template <typename T>
void ApplyExclusionRules(T& creative_ads,
                         const AdInfo& last_served_ad,
                         ExclusionRulesBase* exclusion_rules) {
  CHECK(exclusion_rules);

  TRACE_EVENT(kTraceEventCategory, "ExclusionRules::ApplyExclusionRules",
              "creative_ads", creative_ads.size());

  if (creative_ads.empty()) {
    return;
  }

  const bool can_cap_last_served_creative_ad =
      CanCapLastServedCreativeAd(creative_ads);

  std::erase_if(creative_ads, [exclusion_rules, &last_served_ad,
                               &can_cap_last_served_creative_ad](
                                  const CreativeAdInfo& creative_ad) {
    return exclusion_rules->ShouldExcludeCreativeAd(creative_ad) ||
           (last_served_ad.type != mojom::AdType::kNewTabPageAd &&
            can_cap_last_served_creative_ad &&
            creative_ad.creative_instance_id ==
                last_served_ad.creative_instance_id);
  });
}

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULES_UTIL_H_
