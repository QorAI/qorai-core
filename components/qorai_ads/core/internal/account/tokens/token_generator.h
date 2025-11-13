/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_H_

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/account/tokens/token_generator_interface.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token.h"

namespace qorai_ads {

class TokenGenerator final : public TokenGeneratorInterface {
 public:
  cbr::TokenList Generate(size_t count) const override;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_H_
