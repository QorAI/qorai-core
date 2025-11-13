/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_INLINE_CONTENT_ADS_CREATIVE_INLINE_CONTENT_AD_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_INLINE_CONTENT_ADS_CREATIVE_INLINE_CONTENT_AD_INFO_H_

#include <string>
#include <vector>

#include "qorai/components/qorai_ads/core/internal/creatives/creative_ad_info.h"
#include "url/gurl.h"

namespace qorai_ads {

struct CreativeInlineContentAdInfo final : CreativeAdInfo {
  CreativeInlineContentAdInfo();
  explicit CreativeInlineContentAdInfo(const CreativeAdInfo& creative_ad);

  CreativeInlineContentAdInfo(const CreativeInlineContentAdInfo&);
  CreativeInlineContentAdInfo& operator=(const CreativeInlineContentAdInfo&);

  CreativeInlineContentAdInfo(CreativeInlineContentAdInfo&&) noexcept;
  CreativeInlineContentAdInfo& operator=(
      CreativeInlineContentAdInfo&&) noexcept;

  ~CreativeInlineContentAdInfo();

  bool operator==(const CreativeInlineContentAdInfo&) const = default;

  std::string title;
  std::string description;
  GURL image_url;
  std::string dimensions;
  std::string cta_text;
};

using CreativeInlineContentAdList = std::vector<CreativeInlineContentAdInfo>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_INLINE_CONTENT_ADS_CREATIVE_INLINE_CONTENT_AD_INFO_H_
