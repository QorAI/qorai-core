/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_ANTI_TARGETING_EXCLUSION_RULE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_ANTI_TARGETING_EXCLUSION_RULE_UTIL_H_

#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/anti_targeting/resource/anti_targeting_resource_info.h"
#include "qorai/components/qorai_ads/core/public/history/site_history.h"

namespace qorai_ads {

bool HasVisitedAntiTargetedSites(const SiteHistoryList& site_history,
                                 const AntiTargetingSiteList& sites);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_ANTI_TARGETING_EXCLUSION_RULE_UTIL_H_
