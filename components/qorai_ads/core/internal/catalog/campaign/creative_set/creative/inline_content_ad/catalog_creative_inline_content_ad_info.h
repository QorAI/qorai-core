/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_INLINE_CONTENT_AD_CATALOG_CREATIVE_INLINE_CONTENT_AD_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_INLINE_CONTENT_AD_CATALOG_CREATIVE_INLINE_CONTENT_AD_INFO_H_

#include <vector>

#include "qorai/components/qorai_ads/core/internal/catalog/campaign/creative_set/creative/catalog_creative_info.h"
#include "qorai/components/qorai_ads/core/internal/catalog/campaign/creative_set/creative/inline_content_ad/catalog_inline_content_ad_payload_info.h"

namespace qorai_ads {

struct CatalogCreativeInlineContentAdInfo final : CatalogCreativeInfo {
  bool operator==(const CatalogCreativeInlineContentAdInfo&) const = default;

  CatalogInlineContentAdPayloadInfo payload;
};

using CatalogCreativeInlineContentAdList =
    std::vector<CatalogCreativeInlineContentAdInfo>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_INLINE_CONTENT_AD_CATALOG_CREATIVE_INLINE_CONTENT_AD_INFO_H_
