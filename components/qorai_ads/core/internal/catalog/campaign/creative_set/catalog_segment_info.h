/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CATALOG_SEGMENT_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CATALOG_SEGMENT_INFO_H_

#include <string>
#include <vector>

namespace qorai_ads {

struct CatalogSegmentInfo final {
  bool operator==(const CatalogSegmentInfo&) const = default;

  std::string code;
  std::string name;
};

using CatalogSegmentList = std::vector<CatalogSegmentInfo>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CATALOG_SEGMENT_INFO_H_
