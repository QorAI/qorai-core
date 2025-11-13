/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ZEBPAY_ZEBPAY_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ZEBPAY_ZEBPAY_H_

#include <string>

#include "base/functional/callback_forward.h"
#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_rewards/core/engine/endpoints/zebpay/get_balance_zebpay.h"
#include "qorai/components/qorai_rewards/core/engine/wallet_provider/wallet_provider.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace zebpay {

class ZebPay final : public wallet_provider::WalletProvider {
 public:
  explicit ZebPay(RewardsEngine& engine);

  const char* WalletType() const override;

  void AssignWalletLinks(mojom::ExternalWallet& external_wallet) override;

  void FetchBalance(
      base::OnceCallback<void(mojom::Result, double)> callback) override;

  std::string GetFeeAddress() const override;

 private:
  void OnFetchBalance(base::OnceCallback<void(mojom::Result, double)> callback,
                      endpoints::GetBalanceZebPay::Result&& result);

  const raw_ref<RewardsEngine> engine_;
};

}  // namespace zebpay
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ZEBPAY_ZEBPAY_H_
