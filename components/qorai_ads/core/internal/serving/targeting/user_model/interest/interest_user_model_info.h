/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_INTEREST_INTEREST_USER_MODEL_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_INTEREST_INTEREST_USER_MODEL_INFO_H_

#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"

namespace qorai_ads {

struct InterestUserModelInfo final {
  InterestUserModelInfo();
  explicit InterestUserModelInfo(SegmentList segments);

  InterestUserModelInfo(const InterestUserModelInfo&);
  InterestUserModelInfo& operator=(const InterestUserModelInfo&);

  InterestUserModelInfo(InterestUserModelInfo&&) noexcept;
  InterestUserModelInfo& operator=(InterestUserModelInfo&&) noexcept;

  ~InterestUserModelInfo();

  bool operator==(const InterestUserModelInfo&) const = default;

  SegmentList segments;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_INTEREST_INTEREST_USER_MODEL_INFO_H_
