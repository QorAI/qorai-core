/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CATALOG_GEO_TARGET_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CATALOG_GEO_TARGET_INFO_H_

#include <string>
#include <vector>

namespace qorai_ads {

struct CatalogGeoTargetInfo final {
  bool operator==(const CatalogGeoTargetInfo&) const = default;

  std::string code;
  std::string name;
};

using CatalogGeoTargetList = std::vector<CatalogGeoTargetInfo>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CATALOG_GEO_TARGET_INFO_H_
