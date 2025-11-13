/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CATALOG_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CATALOG_INFO_H_

#include <string>

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/catalog/campaign/catalog_campaign_info.h"

namespace qorai_ads {

struct CatalogInfo final {
  CatalogInfo();

  CatalogInfo(const CatalogInfo&);
  CatalogInfo& operator=(const CatalogInfo&);

  CatalogInfo(CatalogInfo&&) noexcept;
  CatalogInfo& operator=(CatalogInfo&&) noexcept;

  ~CatalogInfo();

  bool operator==(const CatalogInfo&) const = default;

  std::string id;
  int version = 0;
  base::TimeDelta ping;
  CatalogCampaignList campaigns;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CATALOG_INFO_H_
