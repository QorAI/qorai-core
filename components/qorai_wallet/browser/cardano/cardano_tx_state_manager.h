/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_CARDANO_CARDANO_TX_STATE_MANAGER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_CARDANO_CARDANO_TX_STATE_MANAGER_H_

#include <memory>
#include <string>

#include "qorai/components/qorai_wallet/browser/tx_state_manager.h"

namespace base {
class Value;
}  // namespace base

namespace qorai_wallet {

class TxMeta;
class CardanoTxMeta;
class TxStorageDelegate;

class CardanoTxStateManager : public TxStateManager {
 public:
  CardanoTxStateManager(TxStorageDelegate& delegate,
                        AccountResolverDelegate& account_resolver_delegate);
  ~CardanoTxStateManager() override;
  CardanoTxStateManager(const CardanoTxStateManager&) = delete;
  CardanoTxStateManager operator=(const CardanoTxStateManager&) = delete;

  std::unique_ptr<CardanoTxMeta> GetCardanoTx(const std::string& id);
  std::unique_ptr<CardanoTxMeta> ValueToCardanoTxMeta(
      const base::Value::Dict& value);

 private:
  mojom::CoinType GetCoinType() const override;

  std::unique_ptr<TxMeta> ValueToTxMeta(
      const base::Value::Dict& value) override;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_CARDANO_CARDANO_TX_STATE_MANAGER_H_
