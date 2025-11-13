/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_POLKADOT_POLKADOT_TX_STATE_MANAGER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_POLKADOT_POLKADOT_TX_STATE_MANAGER_H_

#include <memory>
#include <string>
#include <vector>

#include "qorai/components/qorai_wallet/browser/polkadot/polkadot_tx_meta.h"
#include "qorai/components/qorai_wallet/browser/tx_state_manager.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

class TxStorageDelegate;
class AccountResolverDelegate;

class PolkadotTxStateManager : public TxStateManager {
 public:
  explicit PolkadotTxStateManager(
      TxStorageDelegate& delegate,
      AccountResolverDelegate& account_resolver_delegate);
  ~PolkadotTxStateManager() override;

  PolkadotTxStateManager(const PolkadotTxStateManager&) = delete;
  PolkadotTxStateManager& operator=(const PolkadotTxStateManager&) = delete;

 protected:
  // TxStateManager
  mojom::CoinType GetCoinType() const override;
  std::unique_ptr<TxMeta> ValueToTxMeta(
      const base::Value::Dict& value) override;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_POLKADOT_POLKADOT_TX_STATE_MANAGER_H_
