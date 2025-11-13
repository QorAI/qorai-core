/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TYPES_VERIFIABLE_CONVERSION_VERIFIABLE_CONVERSION_TEST_CONSTANTS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TYPES_VERIFIABLE_CONVERSION_VERIFIABLE_CONVERSION_TEST_CONSTANTS_H_

namespace qorai_ads::test {

inline constexpr char kVerifiableConversionId[] = "smartbrownfoxes42";
inline constexpr char kInvalidVerifiableConversionId[] = "smart brown foxes 16";

inline constexpr char kVerifiableConversionAdvertiserPublicKeyBase64[] =
    "ofIveUY/bM7qlL9eIkAv/xbjDItFs1xRTTYKRZZsPHI=";
inline constexpr char kInvalidVerifiableConversionAdvertiserPublicKeyBase64[] =
    "INVALID";
inline constexpr char kVerifiableConversionAdvertiserSecretKeyBase64[] =
    "Ete7+aKfrX25gt0eN4kBV1LqeF9YmB1go8OqnGXUGG4=";

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TYPES_VERIFIABLE_CONVERSION_VERIFIABLE_CONVERSION_TEST_CONSTANTS_H_
