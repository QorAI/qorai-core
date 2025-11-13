/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TYPES_VERIFIABLE_CONVERSION_ID_PATTERN_PARSERS_VERIFIABLE_CONVERSION_ID_URL_REDIRECTS_PARSER_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TYPES_VERIFIABLE_CONVERSION_ID_PATTERN_PARSERS_VERIFIABLE_CONVERSION_ID_URL_REDIRECTS_PARSER_UTIL_H_

#include <optional>
#include <string>
#include <vector>

class GURL;

namespace qorai_ads {

struct ConversionResourceIdPatternInfo;

std::optional<std::string> MaybeParseVerifableConversionIdFromUrlRedirects(
    const std::vector<GURL>& redirect_chain,
    const ConversionResourceIdPatternInfo& resource_id_pattern);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TYPES_VERIFIABLE_CONVERSION_ID_PATTERN_PARSERS_VERIFIABLE_CONVERSION_ID_URL_REDIRECTS_PARSER_UTIL_H_
