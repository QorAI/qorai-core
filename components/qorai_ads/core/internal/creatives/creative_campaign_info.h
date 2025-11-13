/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_CAMPAIGN_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_CAMPAIGN_INFO_H_

#include <string>

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-data-view.h"

namespace qorai_ads {

struct CreativeCampaignInfo final {
  mojom::NewTabPageAdMetricType metric_type =
      mojom::NewTabPageAdMetricType::kUndefined;
  base::Time start_at;
  base::Time end_at;
  int daily_cap = 0;
  std::string advertiser_id;
  int priority = 0;
  double pass_through_rate = 0.0;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_CAMPAIGN_INFO_H_
