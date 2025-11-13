/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_ZEBPAY_CONNECT_ZEBPAY_WALLET_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_ZEBPAY_CONNECT_ZEBPAY_WALLET_H_

#include <string>

#include "qorai/components/qorai_rewards/core/engine/endpoints/zebpay/post_oauth_zebpay.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"
#include "qorai/components/qorai_rewards/core/engine/wallet_provider/connect_external_wallet.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace zebpay {

class ConnectZebPayWallet : public wallet_provider::ConnectExternalWallet {
 public:
  explicit ConnectZebPayWallet(RewardsEngine& engine);

  ~ConnectZebPayWallet() override;

 private:
  const char* WalletType() const override;

  std::string GetOAuthLoginURL() const override;

  void Authorize(ConnectExternalWalletCallback callback) override;

  void OnAuthorize(ConnectExternalWalletCallback callback,
                   endpoints::PostOAuthZebPay::Result&& result) const;
};

}  // namespace zebpay
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_ZEBPAY_CONNECT_ZEBPAY_WALLET_H_
