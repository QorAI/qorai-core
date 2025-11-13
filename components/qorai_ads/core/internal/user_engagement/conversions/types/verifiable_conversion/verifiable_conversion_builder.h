/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TYPES_VERIFIABLE_CONVERSION_VERIFIABLE_CONVERSION_BUILDER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TYPES_VERIFIABLE_CONVERSION_VERIFIABLE_CONVERSION_BUILDER_H_

#include <optional>
#include <string>
#include <vector>

#include "qorai/components/qorai_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/resource/conversion_resource_id_pattern_info.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/types/verifiable_conversion/verifiable_conversion_info.h"

class GURL;

namespace qorai_ads {

struct CreativeSetConversionInfo;
struct VerifiableConversionInfo;

std::optional<VerifiableConversionInfo> MaybeBuildVerifiableConversion(
    const std::vector<GURL>& redirect_chain,
    const std::string& html,
    const ConversionResourceIdPatternMap& resource_id_patterns,
    const CreativeSetConversionInfo& creative_set_conversion);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TYPES_VERIFIABLE_CONVERSION_VERIFIABLE_CONVERSION_BUILDER_H_
