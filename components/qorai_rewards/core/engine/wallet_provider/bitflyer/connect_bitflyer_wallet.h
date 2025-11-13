/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_BITFLYER_CONNECT_BITFLYER_WALLET_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_BITFLYER_CONNECT_BITFLYER_WALLET_H_

#include <string>

#include "base/containers/flat_map.h"
#include "qorai/components/qorai_rewards/core/engine/endpoint/bitflyer/bitflyer_server.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"
#include "qorai/components/qorai_rewards/core/engine/wallet_provider/connect_external_wallet.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace bitflyer {

class ConnectBitFlyerWallet : public wallet_provider::ConnectExternalWallet {
 public:
  explicit ConnectBitFlyerWallet(RewardsEngine& engine);

  ~ConnectBitFlyerWallet() override;

 private:
  const char* WalletType() const override;

  std::string GetOAuthLoginURL() const override;

  void Authorize(ConnectExternalWalletCallback callback) override;

  void OnAuthorize(ConnectExternalWalletCallback,
                   mojom::Result,
                   std::string&& token,
                   std::string&& address,
                   std::string&& linking_info) const;

  endpoint::BitflyerServer bitflyer_server_;
};

}  // namespace bitflyer
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_BITFLYER_CONNECT_BITFLYER_WALLET_H_
