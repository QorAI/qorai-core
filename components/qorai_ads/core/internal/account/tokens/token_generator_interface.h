/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_INTERFACE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_INTERFACE_H_

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token.h"

namespace qorai_ads {

class TokenGeneratorInterface {
 public:
  virtual ~TokenGeneratorInterface() = default;

  // Generates a list of cryptographic tokens that can be redeemed for purposes
  // such as privacy-preserving ad interactions.
  virtual cbr::TokenList Generate(size_t count) const = 0;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_INTERFACE_H_
