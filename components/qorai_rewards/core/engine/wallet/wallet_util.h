/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_WALLET_UTIL_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_WALLET_UTIL_H_

#include <set>
#include <string>
#include <variant>

#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace wallet {

mojom::ExternalWalletPtr GetWallet(RewardsEngine& engine,
                                   const std::string& wallet_type);

mojom::ExternalWalletPtr GetWalletIf(RewardsEngine& engine,
                                     const std::string& wallet_type,
                                     const std::set<mojom::WalletStatus>&);

bool SetWallet(RewardsEngine& engine, mojom::ExternalWalletPtr);

mojom::ExternalWalletPtr TransitionWallet(
    RewardsEngine& engine,
    std::variant<mojom::ExternalWalletPtr, std::string> wallet_info,
    mojom::WalletStatus to);

mojom::ExternalWalletPtr MaybeCreateWallet(RewardsEngine& engine,
                                           const std::string& wallet_type);

bool LogOutWallet(RewardsEngine& engine, const std::string& wallet_type);

}  // namespace wallet
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_WALLET_UTIL_H_
