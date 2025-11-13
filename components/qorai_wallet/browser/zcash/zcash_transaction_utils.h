/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_TRANSACTION_UTILS_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_TRANSACTION_UTILS_H_

#include <vector>

#include "qorai/components/qorai_wallet/browser/zcash/zcash_transaction.h"
#include "qorai/components/qorai_wallet/browser/zcash/zcash_wallet_service.h"
#include "qorai/components/qorai_wallet/common/zcash_utils.h"

namespace qorai_wallet {

struct PickInputsResult {
  std::vector<ZCashTransaction::TxInput> inputs;
  uint64_t fee;
  uint64_t change;

  PickInputsResult(std::vector<ZCashTransaction::TxInput> inputs,
                   uint64_t fee,
                   uint64_t change);
  ~PickInputsResult();
  PickInputsResult(const PickInputsResult& other);
  PickInputsResult& operator=(const PickInputsResult& other) = delete;
  PickInputsResult(PickInputsResult&& other);
  PickInputsResult& operator=(PickInputsResult&& other) = delete;
};

std::optional<PickInputsResult> PickZCashTransparentInputs(
    const ZCashWalletService::UtxoMap& utxo_map,
    uint64_t amount,
    size_t orchard_actions_count);

struct PickOrchardInputsResult {
  std::vector<OrchardNote> inputs;
  uint64_t fee;
  uint64_t change;

  PickOrchardInputsResult(std::vector<OrchardNote> inputs,
                          uint64_t fee,
                          uint64_t change);
  ~PickOrchardInputsResult();
  PickOrchardInputsResult(const PickOrchardInputsResult& other);
  PickOrchardInputsResult& operator=(const PickOrchardInputsResult& other) =
      delete;
  PickOrchardInputsResult(PickOrchardInputsResult&& other);
  PickOrchardInputsResult& operator=(PickOrchardInputsResult&& other) = delete;
};

#if BUILDFLAG(ENABLE_ORCHARD)
std::optional<PickOrchardInputsResult> PickZCashOrchardInputs(
    const std::vector<OrchardNote>& notes,
    uint64_t amount);
#endif  // BUILDFLAG(ENABLE_ORCHARD)

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_TRANSACTION_UTILS_H_
