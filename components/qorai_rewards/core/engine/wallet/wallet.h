/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_WALLET_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_WALLET_H_

#include <stdint.h>

#include <optional>
#include <string>

#include "base/containers/flat_map.h"
#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"
#include "qorai/components/qorai_rewards/core/engine/wallet/wallet_balance.h"
#include "qorai/components/qorai_rewards/core/engine/wallet/wallet_create.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace wallet {

class Wallet {
 public:
  explicit Wallet(RewardsEngine& engine);
  ~Wallet();

  void CreateWalletIfNecessary(std::optional<std::string>&& geo_country,
                               CreateRewardsWalletCallback callback);

  void FetchBalance(FetchBalanceCallback callback);

  mojom::RewardsWalletPtr GetWallet();
  mojom::RewardsWalletPtr GetWallet(bool* corrupted);

  bool SetWallet(mojom::RewardsWalletPtr wallet);

 private:
  const raw_ref<RewardsEngine> engine_;
  WalletCreate create_;
  WalletBalance balance_;
};

}  // namespace wallet
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_WALLET_H_
