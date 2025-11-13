/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/minimum_wait_time_permission_rule.h"

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/common/logging_util.h"
#include "qorai/components/qorai_ads/core/internal/common/time/time_constraint_util.h"
#include "qorai/components/qorai_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_feature.h"

namespace qorai_ads {

bool HasMinimumWaitTimePermission(const std::vector<base::Time>& history,
                                  base::TimeDelta time_constraint) {
  if (!DoesHistoryRespectRollingTimeConstraint(history, time_constraint,
                                               /*cap=*/1)) {
    BLOG(2, "Ad cannot be shown as minimum wait time has not passed");
    return false;
  }

  return true;
}

}  // namespace qorai_ads
