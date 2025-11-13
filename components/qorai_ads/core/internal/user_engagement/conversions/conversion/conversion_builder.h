/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSION_CONVERSION_BUILDER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSION_CONVERSION_BUILDER_H_

#include <optional>

namespace qorai_ads {

struct AdEventInfo;
struct ConversionInfo;
struct VerifiableConversionInfo;

ConversionInfo BuildConversion(
    const AdEventInfo& ad_event,
    std::optional<VerifiableConversionInfo> verifiable_conversion);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSION_CONVERSION_BUILDER_H_
