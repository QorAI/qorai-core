/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_wallet/browser/polkadot/polkadot_tx_meta.h"

#include "base/notimplemented.h"
#include "base/values.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

PolkadotTxMeta::PolkadotTxMeta() = default;

PolkadotTxMeta::~PolkadotTxMeta() = default;

base::Value::Dict PolkadotTxMeta::ToValue() const {
  NOTIMPLEMENTED_LOG_ONCE();

  base::Value::Dict dict;
  return dict;
}

mojom::TransactionInfoPtr PolkadotTxMeta::ToTransactionInfo() const {
  NOTIMPLEMENTED_LOG_ONCE();

  auto tx_info = mojom::TransactionInfo::New();
  return tx_info;
}

mojom::CoinType PolkadotTxMeta::GetCoinType() const {
  NOTIMPLEMENTED_LOG_ONCE();

  return mojom::CoinType::DOT;
}

}  // namespace qorai_wallet
