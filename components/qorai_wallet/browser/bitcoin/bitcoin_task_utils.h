/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BITCOIN_BITCOIN_TASK_UTILS_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BITCOIN_BITCOIN_TASK_UTILS_H_

#include "qorai/components/qorai_wallet/browser/bitcoin/bitcoin_rpc_responses.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

void UpdateBalance(mojom::BitcoinBalancePtr& balance,
                   const bitcoin_rpc::AddressStats& address_stats);

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BITCOIN_BITCOIN_TASK_UTILS_H_
