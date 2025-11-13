/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_ALIAS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_ALIAS_H_

#include <string>
#include <vector>

#include "base/functional/callback.h"

namespace qorai_ads {

using SegmentList = std::vector<std::string>;

using BuildSegmentsCallback = base::OnceCallback<void(const SegmentList&)>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SEGMENTS_SEGMENT_ALIAS_H_
