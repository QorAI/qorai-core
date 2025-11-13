/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_USER_MODEL_SEGMENTS_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_USER_MODEL_SEGMENTS_UTIL_H_

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"

namespace qorai_ads {

struct UserModelInfo;

SegmentList GetTopSegments(const UserModelInfo& user_model,
                           size_t max_count,
                           bool parent_only);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_SEGMENTS_TOP_USER_MODEL_SEGMENTS_UTIL_H_
