/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_BLINDED_TOKEN_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_BLINDED_TOKEN_UTIL_H_

#include <vector>

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token.h"
#include "qorai/components/challenge_bypass_ristretto/blinded_token.h"

namespace qorai_ads::cbr {

BlindedTokenList BlindTokens(const TokenList& tokens);

std::vector<challenge_bypass_ristretto::BlindedToken> ToRawBlindedTokens(
    const BlindedTokenList& blinded_tokens);

}  // namespace qorai_ads::cbr

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_BLINDED_TOKEN_UTIL_H_
