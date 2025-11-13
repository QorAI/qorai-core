/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_MATCHERS_NUMERICAL_OPERATOR_CONDITION_MATCHER_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_MATCHERS_NUMERICAL_OPERATOR_CONDITION_MATCHER_UTIL_H_

#include <string_view>

namespace qorai_ads {

// Returns true if the condition is a numerical operator.
bool IsNumericalOperator(std::string_view condition);

// Matches a value against a condition using numerical operators. Supports
// equality, greater than, greater than or equal, less than, less than or equal
// and not equal operators.
bool MatchNumericalOperator(std::string_view value, std::string_view condition);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_MATCHERS_NUMERICAL_OPERATOR_CONDITION_MATCHER_UTIL_H_
