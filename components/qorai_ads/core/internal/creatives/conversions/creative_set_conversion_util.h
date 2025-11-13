/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_UTIL_H_

#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "qorai/components/qorai_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_info.h"

class GURL;

namespace qorai_ads {

using CreativeSetConversionBucketMap =
    std::map</*creative_set_id*/ std::string, CreativeSetConversionList>;

using CreativeSetConversionCountMap = std::map</*creative_set_id*/ std::string,
                                               /*count*/ size_t>;

CreativeSetConversionList GetMatchingCreativeSetConversions(
    const CreativeSetConversionList& creative_set_conversions,
    const std::vector<GURL>& redirect_chain);

CreativeSetConversionCountMap GetCreativeSetConversionCounts(
    const AdEventList& ad_events);

CreativeSetConversionBucketMap SortCreativeSetConversionsIntoBuckets(
    const CreativeSetConversionList& creative_set_conversions);

void FilterCreativeSetConversionBucketsThatExceedTheCap(
    const std::map<std::string, size_t>& creative_set_conversion_counts,
    size_t creative_set_conversion_cap,
    CreativeSetConversionBucketMap& creative_set_conversion_buckets);

CreativeSetConversionList GetCreativeSetConversionsWithinObservationWindow(
    const CreativeSetConversionList& creative_set_conversions,
    const AdEventInfo& ad_event);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_UTIL_H_
