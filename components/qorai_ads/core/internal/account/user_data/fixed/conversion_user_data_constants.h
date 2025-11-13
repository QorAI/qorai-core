/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_CONVERSION_USER_DATA_CONSTANTS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_CONVERSION_USER_DATA_CONSTANTS_H_

namespace qorai_ads {

inline constexpr char kConversionKey[] = "conversion";

inline constexpr char kConversionActionTypeKey[] = "action";

inline constexpr char kVerifiableConversionEnvelopeKey[] = "envelope";
inline constexpr char kVerifiableConversionEnvelopeAlgorithmKey[] = "alg";
inline constexpr char kVerifiableConversionEnvelopeCipherTextKey[] =
    "ciphertext";
inline constexpr char kVerifiableConversionEnvelopeEphemeralPublicKeyKey[] =
    "epk";
inline constexpr char kVerifiableConversionEnvelopeNonceKey[] = "nonce";

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_CONVERSION_USER_DATA_CONSTANTS_H_
