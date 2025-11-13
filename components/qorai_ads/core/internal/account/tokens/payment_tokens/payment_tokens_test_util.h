/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKENS_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKENS_TEST_UTIL_H_

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

class PaymentTokens;

namespace test {

PaymentTokens& GetPaymentTokens();
PaymentTokenList SetPaymentTokens(size_t count);

PaymentTokenInfo BuildPaymentToken(
    mojom::ConfirmationType mojom_confirmation_type,
    mojom::AdType mojom_ad_type);
PaymentTokenInfo BuildPaymentToken();
PaymentTokenList BuildPaymentTokens(size_t count);

}  // namespace test

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKENS_TEST_UTIL_H_
