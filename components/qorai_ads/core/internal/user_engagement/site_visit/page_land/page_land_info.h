/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_PAGE_LAND_PAGE_LAND_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_PAGE_LAND_PAGE_LAND_INFO_H_

#include <optional>

#include "base/timer/timer.h"
#include "qorai/components/qorai_ads/core/public/ad_units/ad_info.h"

namespace qorai_ads {

struct PageLandInfo {
  AdInfo ad;
  base::RetainingOneShotTimer timer;
  std::optional<base::TimeDelta> remaining_time;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_PAGE_LAND_PAGE_LAND_INFO_H_
