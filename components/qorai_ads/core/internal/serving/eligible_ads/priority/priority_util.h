/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PRIORITY_PRIORITY_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PRIORITY_PRIORITY_UTIL_H_

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/common/logging_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/creative_ad_util.h"

namespace qorai_ads {

template <typename T>
void LogNumberOfUntargetedCreativeAdsForBucket(const T& creative_ads,
                                               int priority,
                                               size_t bucket) {
  const size_t count = UntargetedCreativeAdCount(creative_ads);
  if (count > 0) {
    BLOG(3, count << " untargeted ads with a priority of " << priority
                  << " in bucket " << bucket);
  }
}

template <typename T>
void LogNumberOfTargetedCreativeAdsForBucket(const T& creative_ads,
                                             int priority,
                                             size_t bucket) {
  const size_t count = TargetedCreativeAdCount(creative_ads);
  if (count > 0) {
    BLOG(3, count << " targeted ads with a priority of " << priority
                  << " in bucket " << bucket);
  }
}

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PRIORITY_PRIORITY_UTIL_H_
