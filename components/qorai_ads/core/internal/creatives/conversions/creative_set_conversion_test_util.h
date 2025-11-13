/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_TEST_UTIL_H_

#include <optional>
#include <string>

namespace base {
class TimeDelta;
}  // namespace base

namespace qorai_ads {

struct CreativeSetConversionInfo;

namespace test {

CreativeSetConversionInfo BuildCreativeSetConversion(
    const std::string& creative_set_id,
    const std::string& url_pattern,
    base::TimeDelta observation_window);
void BuildAndSaveCreativeSetConversion(const std::string& creative_set_id,
                                       const std::string& url_pattern,
                                       base::TimeDelta observation_window);

CreativeSetConversionInfo BuildVerifiableCreativeSetConversion(
    const std::string& creative_set_id,
    const std::string& url_pattern,
    base::TimeDelta observation_window,
    std::optional<std::string> verifiable_advertiser_public_key_base64);
void BuildAndSaveVerifiableCreativeSetConversion(
    const std::string& creative_set_id,
    const std::string& url_pattern,
    base::TimeDelta observation_window,
    std::optional<std::string> verifiable_advertiser_public_key_base64);

}  // namespace test

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_TEST_UTIL_H_
