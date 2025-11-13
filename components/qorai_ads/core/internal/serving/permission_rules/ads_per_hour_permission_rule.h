/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_ADS_PER_HOUR_PERMISSION_RULE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_ADS_PER_HOUR_PERMISSION_RULE_H_

#include <cstddef>
#include <vector>

namespace base {
class Time;
}  // namespace base

namespace qorai_ads {

bool HasAdsPerHourPermission(const std::vector<base::Time>& history,
                             size_t cap);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_ADS_PER_HOUR_PERMISSION_RULE_H_
