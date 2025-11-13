/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKEN_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKEN_UTIL_H_

#include <cstddef>
#include <optional>

#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"

namespace qorai_ads {

std::optional<PaymentTokenInfo> MaybeGetPaymentToken();

const PaymentTokenList& GetAllPaymentTokens();

void AddPaymentTokens(const PaymentTokenList& payment_tokens);

bool RemovePaymentToken(const PaymentTokenInfo& payment_token);
void RemovePaymentTokens(const PaymentTokenList& payment_tokens);
void RemoveAllPaymentTokens();

bool PaymentTokenExists(const PaymentTokenInfo& payment_token);

bool PaymentTokensIsEmpty();

size_t PaymentTokenCount();

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKEN_UTIL_H_
