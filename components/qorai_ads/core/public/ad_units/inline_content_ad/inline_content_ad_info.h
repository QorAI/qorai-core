/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_INLINE_CONTENT_AD_INLINE_CONTENT_AD_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_INLINE_CONTENT_AD_INLINE_CONTENT_AD_INFO_H_

#include <string>

#include "qorai/components/qorai_ads/core/public/ad_units/ad_info.h"
#include "url/gurl.h"

namespace qorai_ads {

struct InlineContentAdInfo final : AdInfo {
  InlineContentAdInfo();

  InlineContentAdInfo(const InlineContentAdInfo&);
  InlineContentAdInfo& operator=(const InlineContentAdInfo&);

  InlineContentAdInfo(InlineContentAdInfo&&) noexcept;
  InlineContentAdInfo& operator=(InlineContentAdInfo&&) noexcept;

  ~InlineContentAdInfo();

  bool operator==(const InlineContentAdInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  std::string title;
  std::string description;
  GURL image_url;
  std::string dimensions;
  std::string cta_text;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_AD_UNITS_INLINE_CONTENT_AD_INLINE_CONTENT_AD_INFO_H_
