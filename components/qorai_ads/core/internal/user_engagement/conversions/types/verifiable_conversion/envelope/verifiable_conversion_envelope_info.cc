/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/types/verifiable_conversion/envelope/verifiable_conversion_envelope_info.h"

namespace qorai_ads {

VerifiableConversionEnvelopeInfo::VerifiableConversionEnvelopeInfo() = default;

VerifiableConversionEnvelopeInfo::VerifiableConversionEnvelopeInfo(
    const VerifiableConversionEnvelopeInfo& other) = default;

VerifiableConversionEnvelopeInfo& VerifiableConversionEnvelopeInfo::operator=(
    const VerifiableConversionEnvelopeInfo& other) = default;

VerifiableConversionEnvelopeInfo::VerifiableConversionEnvelopeInfo(
    VerifiableConversionEnvelopeInfo&& other) noexcept = default;

VerifiableConversionEnvelopeInfo& VerifiableConversionEnvelopeInfo::operator=(
    VerifiableConversionEnvelopeInfo&& other) noexcept = default;

VerifiableConversionEnvelopeInfo::~VerifiableConversionEnvelopeInfo() = default;

bool VerifiableConversionEnvelopeInfo::IsValid() const {
  return !algorithm.empty() && !ciphertext_base64.empty() &&
         !ephemeral_key_pair_public_key_base64.empty() && !nonce_base64.empty();
}

}  // namespace qorai_ads
