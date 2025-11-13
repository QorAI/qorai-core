/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TYPES_VERIFIABLE_CONVERSION_ENVELOPE_VERIFIABLE_CONVERSION_ENVELOPE_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TYPES_VERIFIABLE_CONVERSION_ENVELOPE_VERIFIABLE_CONVERSION_ENVELOPE_INFO_H_

#include <string>

namespace qorai_ads {

struct VerifiableConversionEnvelopeInfo final {
  VerifiableConversionEnvelopeInfo();

  VerifiableConversionEnvelopeInfo(const VerifiableConversionEnvelopeInfo&);
  VerifiableConversionEnvelopeInfo& operator=(
      const VerifiableConversionEnvelopeInfo&);

  VerifiableConversionEnvelopeInfo(VerifiableConversionEnvelopeInfo&&) noexcept;
  VerifiableConversionEnvelopeInfo& operator=(
      VerifiableConversionEnvelopeInfo&&) noexcept;

  ~VerifiableConversionEnvelopeInfo();

  bool operator==(const VerifiableConversionEnvelopeInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  std::string algorithm;
  std::string ciphertext_base64;
  std::string ephemeral_key_pair_public_key_base64;
  std::string nonce_base64;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TYPES_VERIFIABLE_CONVERSION_ENVELOPE_VERIFIABLE_CONVERSION_ENVELOPE_INFO_H_
