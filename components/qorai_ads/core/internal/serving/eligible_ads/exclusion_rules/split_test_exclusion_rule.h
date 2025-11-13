/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_SPLIT_TEST_EXCLUSION_RULE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_SPLIT_TEST_EXCLUSION_RULE_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_interface.h"

namespace qorai_ads {

struct CreativeAdInfo;

class SplitTestExclusionRule : public ExclusionRuleInterface<CreativeAdInfo> {
 public:
  // ExclusionRuleInterface:
  std::string GetCacheKey(const CreativeAdInfo& creative_ad) const override;
  bool ShouldInclude(const CreativeAdInfo& creative_ad) const override;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_SPLIT_TEST_EXCLUSION_RULE_H_
