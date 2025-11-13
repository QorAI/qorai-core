/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_ANTI_TARGETING_EXCLUSION_RULE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_ANTI_TARGETING_EXCLUSION_RULE_H_

#include <string>

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_interface.h"
#include "qorai/components/qorai_ads/core/public/history/site_history.h"

namespace qorai_ads {

class AntiTargetingResource;
struct CreativeAdInfo;

class AntiTargetingExclusionRule final
    : public ExclusionRuleInterface<CreativeAdInfo> {
 public:
  AntiTargetingExclusionRule(const AntiTargetingResource& resource,
                             SiteHistoryList site_history);

  AntiTargetingExclusionRule(const AntiTargetingExclusionRule&) = delete;
  AntiTargetingExclusionRule& operator=(const AntiTargetingExclusionRule&) =
      delete;

  ~AntiTargetingExclusionRule() override;

  // ExclusionRuleInterface:
  std::string GetCacheKey(const CreativeAdInfo& creative_ad) const override;
  bool ShouldInclude(const CreativeAdInfo& creative_ad) const override;

 private:
  bool DoesRespectCap(const CreativeAdInfo& creative_ad) const;

  const raw_ref<const AntiTargetingResource> resource_;

  SiteHistoryList site_history_;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_ANTI_TARGETING_EXCLUSION_RULE_H_
