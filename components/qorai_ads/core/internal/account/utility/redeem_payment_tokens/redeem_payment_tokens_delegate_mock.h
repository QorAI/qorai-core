/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_REDEEM_PAYMENT_TOKENS_DELEGATE_MOCK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_REDEEM_PAYMENT_TOKENS_DELEGATE_MOCK_H_

#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_ads {

class RedeemPaymentTokensDelegateMock : public RedeemPaymentTokensDelegate {
 public:
  RedeemPaymentTokensDelegateMock();

  RedeemPaymentTokensDelegateMock(const RedeemPaymentTokensDelegateMock&) =
      delete;
  RedeemPaymentTokensDelegateMock& operator=(
      const RedeemPaymentTokensDelegateMock&) = delete;

  ~RedeemPaymentTokensDelegateMock() override;

  MOCK_METHOD(void, OnDidRedeemPaymentTokens, (const PaymentTokenList&));
  MOCK_METHOD(void, OnFailedToRedeemPaymentTokens, ());
  MOCK_METHOD(void, OnDidScheduleNextPaymentTokenRedemption, (base::Time));
  MOCK_METHOD(void, OnWillRetryRedeemingPaymentTokens, (base::Time));
  MOCK_METHOD(void, OnDidRetryRedeemingPaymentTokens, ());
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_REDEEM_PAYMENT_TOKENS_DELEGATE_MOCK_H_
