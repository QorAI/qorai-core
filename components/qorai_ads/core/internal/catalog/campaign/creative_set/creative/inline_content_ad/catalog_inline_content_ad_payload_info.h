/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_INLINE_CONTENT_AD_CATALOG_INLINE_CONTENT_AD_PAYLOAD_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_INLINE_CONTENT_AD_CATALOG_INLINE_CONTENT_AD_PAYLOAD_INFO_H_

#include <string>

#include "url/gurl.h"

namespace qorai_ads {

struct CatalogInlineContentAdPayloadInfo final {
  CatalogInlineContentAdPayloadInfo();

  CatalogInlineContentAdPayloadInfo(const CatalogInlineContentAdPayloadInfo&);
  CatalogInlineContentAdPayloadInfo& operator=(
      const CatalogInlineContentAdPayloadInfo&);

  CatalogInlineContentAdPayloadInfo(
      CatalogInlineContentAdPayloadInfo&&) noexcept;
  CatalogInlineContentAdPayloadInfo& operator=(
      CatalogInlineContentAdPayloadInfo&&) noexcept;

  ~CatalogInlineContentAdPayloadInfo();

  bool operator==(const CatalogInlineContentAdPayloadInfo&) const = default;

  std::string title;
  std::string description;
  GURL image_url;
  std::string dimensions;
  std::string cta_text;
  GURL target_url;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_INLINE_CONTENT_AD_CATALOG_INLINE_CONTENT_AD_PAYLOAD_INFO_H_
