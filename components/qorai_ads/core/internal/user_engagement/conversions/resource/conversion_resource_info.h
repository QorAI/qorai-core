/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_RESOURCE_CONVERSION_RESOURCE_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_RESOURCE_CONVERSION_RESOURCE_INFO_H_

#include <optional>

#include "base/values.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/resource/conversion_resource_id_pattern_info.h"

namespace qorai_ads {

struct ConversionResourceInfo final {
  ConversionResourceInfo();

  ConversionResourceInfo(const ConversionResourceInfo&) = delete;
  ConversionResourceInfo& operator=(const ConversionResourceInfo&) = delete;

  ConversionResourceInfo(ConversionResourceInfo&& other) noexcept;
  ConversionResourceInfo& operator=(ConversionResourceInfo&& other) noexcept;

  ~ConversionResourceInfo();

  static std::optional<ConversionResourceInfo> CreateFromValue(
      base::Value::Dict dict);

  std::optional<int> version;
  ConversionResourceIdPatternMap id_patterns;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_RESOURCE_CONVERSION_RESOURCE_INFO_H_
