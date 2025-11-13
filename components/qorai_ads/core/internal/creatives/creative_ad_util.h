/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_AD_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_AD_UTIL_H_

#include <algorithm>
#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/creatives/creative_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/segments/segment_constants.h"

namespace qorai_ads {

template <typename T>
size_t UntargetedCreativeAdCount(const T& creative_ads) {
  return std::ranges::count_if(
      creative_ads, [](const CreativeAdInfo& creative_ad) {
        return creative_ad.segment == kUntargetedSegment;
      });
}

template <typename T>
size_t TargetedCreativeAdCount(const T& creative_ads) {
  return std::ranges::count_if(
      creative_ads, [](const CreativeAdInfo& creative_ad) {
        return creative_ad.segment != kUntargetedSegment;
      });
}

template <typename T>
T DeduplicateCreativeAds(const T& creative_ads) {
  T unique_creative_ads = creative_ads;

  std::sort(unique_creative_ads.begin(), unique_creative_ads.end(),
            [](const CreativeAdInfo& lhs, const CreativeAdInfo& rhs) {
              return lhs.creative_instance_id < rhs.creative_instance_id;
            });

  auto to_remove =
      std::unique(unique_creative_ads.begin(), unique_creative_ads.end(),
                  [](const CreativeAdInfo& lhs, const CreativeAdInfo& rhs) {
                    return lhs.creative_instance_id == rhs.creative_instance_id;
                  });
  unique_creative_ads.erase(to_remove, unique_creative_ads.cend());

  return unique_creative_ads;
}

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_AD_UTIL_H_
