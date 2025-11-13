/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_EXCLUSION_RULES_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_EXCLUSION_RULES_H_

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rules_base.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "qorai/components/qorai_ads/core/public/history/site_history.h"

namespace qorai_ads {

class AntiTargetingResource;
class SubdivisionTargeting;

class NewTabPageAdExclusionRules final : public ExclusionRulesBase {
 public:
  NewTabPageAdExclusionRules(
      const AdEventList& ad_events,
      const SubdivisionTargeting& subdivision_targeting,
      const AntiTargetingResource& anti_targeting_resource,
      const SiteHistoryList& site_history);

  NewTabPageAdExclusionRules(const NewTabPageAdExclusionRules&) = delete;
  NewTabPageAdExclusionRules& operator=(const NewTabPageAdExclusionRules&) =
      delete;

  ~NewTabPageAdExclusionRules() override;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_NEW_TAB_PAGE_ADS_NEW_TAB_PAGE_AD_EXCLUSION_RULES_H_
