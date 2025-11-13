/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_CATALOG_CREATIVE_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_CATALOG_CREATIVE_INFO_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/catalog/campaign/creative_set/creative/catalog_type_info.h"

namespace qorai_ads {

struct CatalogCreativeInfo {
  bool operator==(const CatalogCreativeInfo&) const = default;

  std::string instance_id;
  CatalogTypeInfo type;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_CATALOG_CREATIVE_INFO_H_
