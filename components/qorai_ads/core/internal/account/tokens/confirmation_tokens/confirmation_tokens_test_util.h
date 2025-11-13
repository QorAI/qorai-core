/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_TEST_UTIL_H_

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"

namespace qorai_ads {

class ConfirmationTokens;

namespace test {

// Call this function to refill confirmation tokens for testing purposes if
// code paths call `Confirmations::Confirm`, `MaybeGetConfirmationToken`, or
// `BuildReward`. If code paths call `RefillConfirmationTokens::MaybeRefill`,
// call `MockTokenGenerator` instead and do not call this function.
ConfirmationTokenList RefillConfirmationTokens(size_t count);

ConfirmationTokenInfo BuildConfirmationToken();
ConfirmationTokenList BuildConfirmationTokens(size_t count);

}  // namespace test

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_TEST_UTIL_H_
