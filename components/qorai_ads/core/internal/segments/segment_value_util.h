/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_VALUE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_VALUE_UTIL_H_

#include "base/values.h"
#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"

namespace qorai_ads {

base::Value::List SegmentsToValue(const SegmentList& segments);
SegmentList SegmentsFromValue(const base::Value::List& list);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_VALUE_UTIL_H_
