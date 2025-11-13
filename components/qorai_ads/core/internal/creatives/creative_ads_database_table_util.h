/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_ADS_DATABASE_TABLE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_ADS_DATABASE_TABLE_UTIL_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/serving/targeting/condition_matcher/condition_matcher_util.h"

namespace qorai_ads::database::table {

std::string ConditionMatchersToString(
    const ConditionMatcherMap& condition_matchers);

ConditionMatcherMap StringToConditionMatchers(const std::string& value);

}  // namespace qorai_ads::database::table

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_ADS_DATABASE_TABLE_UTIL_H_
