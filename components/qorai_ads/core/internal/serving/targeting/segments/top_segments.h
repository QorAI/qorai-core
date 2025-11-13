/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_SEGMENTS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_SEGMENTS_H_

#include <cstddef>
#include <optional>
#include <string>

#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"

namespace qorai_ads {

SegmentList GetTopSegments(const SegmentList& segments,
                           size_t max_count,
                           bool parent_only);

std::optional<std::string> GetTopSegment(const SegmentList& segments,
                                         bool parent_only);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_SEGMENTS_H_
