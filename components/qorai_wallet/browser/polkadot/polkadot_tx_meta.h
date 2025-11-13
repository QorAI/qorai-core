/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_POLKADOT_POLKADOT_TX_META_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_POLKADOT_POLKADOT_TX_META_H_

#include "base/time/time.h"
#include "base/values.h"
#include "qorai/components/qorai_wallet/browser/tx_meta.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "url/origin.h"

namespace qorai_wallet {

// Polkadot transaction metadata class
class PolkadotTxMeta : public TxMeta {
 public:
  PolkadotTxMeta();
  ~PolkadotTxMeta() override;

  PolkadotTxMeta(const PolkadotTxMeta&) = delete;
  PolkadotTxMeta& operator=(const PolkadotTxMeta&) = delete;

  // TxMeta
  base::Value::Dict ToValue() const override;
  mojom::TransactionInfoPtr ToTransactionInfo() const override;
  mojom::CoinType GetCoinType() const override;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_POLKADOT_POLKADOT_TX_META_H_
