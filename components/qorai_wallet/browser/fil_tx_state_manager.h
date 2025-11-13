/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_FIL_TX_STATE_MANAGER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_FIL_TX_STATE_MANAGER_H_

#include <memory>
#include <string>

#include "qorai/components/qorai_wallet/browser/tx_state_manager.h"

namespace base {
class Value;
}  // namespace base

namespace qorai_wallet {

class TxMeta;
class TxStorageDelegate;
class FilTxMeta;

class FilTxStateManager : public TxStateManager {
 public:
  FilTxStateManager(TxStorageDelegate& delegate,
                    AccountResolverDelegate& account_resolver_delegate);
  ~FilTxStateManager() override;
  FilTxStateManager(const FilTxStateManager&) = delete;
  FilTxStateManager operator=(const FilTxStateManager&) = delete;

  std::unique_ptr<FilTxMeta> GetFilTx(const std::string& id);
  std::unique_ptr<FilTxMeta> ValueToFilTxMeta(const base::Value::Dict& value);

 private:
  mojom::CoinType GetCoinType() const override;

  std::unique_ptr<TxMeta> ValueToTxMeta(
      const base::Value::Dict& value) override;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_FIL_TX_STATE_MANAGER_H_
