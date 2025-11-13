/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_wallet/browser/polkadot/polkadot_tx_state_manager.h"

#include "base/notimplemented.h"
#include "qorai/components/qorai_wallet/browser/polkadot/polkadot_tx_meta.h"
#include "qorai/components/qorai_wallet/browser/tx_state_manager.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

PolkadotTxStateManager::PolkadotTxStateManager(
    TxStorageDelegate& delegate,
    AccountResolverDelegate& account_resolver_delegate)
    : TxStateManager(delegate, account_resolver_delegate) {}

PolkadotTxStateManager::~PolkadotTxStateManager() = default;

mojom::CoinType PolkadotTxStateManager::GetCoinType() const {
  return mojom::CoinType::DOT;
}

std::unique_ptr<TxMeta> PolkadotTxStateManager::ValueToTxMeta(
    const base::Value::Dict& value) {
  return nullptr;
}

}  // namespace qorai_wallet
