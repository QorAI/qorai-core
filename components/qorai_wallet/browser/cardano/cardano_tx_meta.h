/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_CARDANO_CARDANO_TX_META_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_CARDANO_CARDANO_TX_META_H_

#include <memory>
#include <utility>

#include "qorai/components/qorai_wallet/browser/tx_meta.h"

namespace base {
class Value;
}  // namespace base

namespace qorai_wallet {

class CardanoTransaction;

class CardanoTxMeta : public TxMeta {
 public:
  CardanoTxMeta();
  CardanoTxMeta(const mojom::AccountIdPtr& from,
                std::unique_ptr<CardanoTransaction> tx);
  ~CardanoTxMeta() override;
  CardanoTxMeta(const CardanoTxMeta&) = delete;
  CardanoTxMeta operator=(const CardanoTxMeta&) = delete;
  bool operator==(const CardanoTxMeta& other) const;

  // TxMeta
  base::Value::Dict ToValue() const override;
  mojom::TransactionInfoPtr ToTransactionInfo() const override;
  mojom::CoinType GetCoinType() const override;

  CardanoTransaction* tx() const { return tx_.get(); }
  void set_tx(std::unique_ptr<CardanoTransaction> tx) { tx_ = std::move(tx); }

 private:
  std::unique_ptr<CardanoTransaction> tx_;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_CARDANO_CARDANO_TX_META_H_
