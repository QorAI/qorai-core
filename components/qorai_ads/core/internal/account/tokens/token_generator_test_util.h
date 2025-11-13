/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_TEST_UTIL_H_

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token.h"

namespace qorai_ads::test {

// Call this function to mock the token generator for testing purposes if code
// paths call `RefillConfirmationTokens::MaybeRefill`, `Confirmations::Confirm`,
// `BuildRewardConfirmation`, or `BuildReward`.
void MockTokenGenerator(size_t count);

cbr::TokenList BuildTokens(size_t count);

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_TOKEN_GENERATOR_TEST_UTIL_H_
