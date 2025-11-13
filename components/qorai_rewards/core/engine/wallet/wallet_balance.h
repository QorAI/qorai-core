/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_WALLET_BALANCE_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_WALLET_BALANCE_H_

#include <string>
#include <vector>

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards_engine_internal.mojom.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace wallet {

class WalletBalance {
 public:
  explicit WalletBalance(RewardsEngine& engine);
  ~WalletBalance();

  void Fetch(FetchBalanceCallback callback);

 private:
  void OnFetchExternalWalletBalance(const std::string& wallet_type,
                                    mojom::BalancePtr balance_ptr,
                                    FetchBalanceCallback callback,
                                    mojom::Result result,
                                    double balance);

  const raw_ref<RewardsEngine> engine_;
};

}  // namespace wallet
}  // namespace qorai_rewards::internal
#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_WALLET_BALANCE_H_
