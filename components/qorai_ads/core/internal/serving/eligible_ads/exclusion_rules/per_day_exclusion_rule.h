/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_PER_DAY_EXCLUSION_RULE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_PER_DAY_EXCLUSION_RULE_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_interface.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_info.h"

namespace qorai_ads {

struct CreativeAdInfo;

class PerDayExclusionRule final
    : public ExclusionRuleInterface<CreativeAdInfo> {
 public:
  explicit PerDayExclusionRule(AdEventList ad_events);

  PerDayExclusionRule(const PerDayExclusionRule&) = delete;
  PerDayExclusionRule& operator=(const PerDayExclusionRule&) = delete;

  ~PerDayExclusionRule() override;

  // ExclusionRuleInterface:
  std::string GetCacheKey(const CreativeAdInfo& creative_ad) const override;
  bool ShouldInclude(const CreativeAdInfo& creative_ad) const override;

 private:
  AdEventList ad_events_;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_PER_DAY_EXCLUSION_RULE_H_
