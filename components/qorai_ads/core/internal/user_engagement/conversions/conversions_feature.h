/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_FEATURE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_FEATURE_H_

#include <string>

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace qorai_ads {

BASE_DECLARE_FEATURE(kConversionsFeature);

inline constexpr base::FeatureParam<int> kConversionResourceVersion{
    &kConversionsFeature, "resource_version", 1};

inline constexpr base::FeatureParam<std::string>
    kHtmlMetaTagConversionIdPattern{
        &kConversionsFeature, "html_meta_tag_id_pattern",
        R"~(<meta.*name="ad-conversion-id".*content="([-a-zA-Z0-9]*)".*>)~"};

// Set to 0 to never cap creative set conversions.
inline constexpr base::FeatureParam<size_t> kCreativeSetConversionCap{
    &kConversionsFeature, "creative_set_conversion_cap", 0};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_FEATURE_H_
