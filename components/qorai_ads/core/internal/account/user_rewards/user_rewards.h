/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_REWARDS_USER_REWARDS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_REWARDS_USER_REWARDS_H_

#include <cstddef>
#include <string>

#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_delegate.h"
#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transactions_database_table.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens_delegate.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/refill_confirmation_tokens/refill_confirmation_tokens.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/refill_confirmation_tokens/refill_confirmation_tokens_delegate.h"
#include "qorai/components/qorai_ads/core/internal/account/wallet/wallet_info.h"
#include "qorai/components/qorai_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace qorai_ads {

struct IssuersInfo;

class UserRewards final : public AdsClientNotifierObserver,
                          public IssuersDelegate,
                          public RedeemPaymentTokensDelegate,
                          public RefillConfirmationTokensDelegate {
 public:
  explicit UserRewards(WalletInfo wallet);

  UserRewards(const UserRewards&) = delete;
  UserRewards& operator=(const UserRewards&) = delete;

  ~UserRewards() override;

  void FetchIssuers();

  void MaybeRefillConfirmationTokens();

  void MaybeRedeemPaymentTokens();

 private:
  // AdsClientNotifierObserver:
  void OnNotifyDidSolveAdaptiveCaptcha() override;

  // IssuersDelegate:
  void OnDidFetchIssuers(const IssuersInfo& issuers) override;

  // RedeemPaymentTokensDelegate:
  void OnDidRedeemPaymentTokens(
      const PaymentTokenList& payment_tokens) override;

  // RefillConfirmationTokensDelegate:
  void OnWillRefillConfirmationTokens(size_t count) override;
  void OnDidRefillConfirmationTokens() override;
  void OnFailedToRefillConfirmationTokens() override;
  void OnWillRetryRefillingConfirmationTokens(base::Time retry_at) override;
  void OnDidRetryRefillingConfirmationTokens() override;
  void OnCaptchaRequiredToRefillConfirmationTokens(
      const std::string& captcha_id) override;

  Issuers issuers_;
  RefillConfirmationTokens refill_confirmation_tokens_;
  RedeemPaymentTokens redeem_payment_tokens_;

  WalletInfo wallet_;

  const database::table::Transactions transactions_database_table_;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_REWARDS_USER_REWARDS_H_
