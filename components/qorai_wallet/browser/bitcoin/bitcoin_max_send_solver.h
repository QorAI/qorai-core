/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BITCOIN_BITCOIN_MAX_SEND_SOLVER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BITCOIN_BITCOIN_MAX_SEND_SOLVER_H_

#include <string>
#include <vector>

#include "base/types/expected.h"
#include "qorai/components/qorai_wallet/browser/bitcoin/bitcoin_transaction.h"

namespace qorai_wallet {

// Coin selection algorithm which spends all available utxos. No change output
// is created. Receiver gets everything except fee.
class BitcoinMaxSendSolver {
 public:
  BitcoinMaxSendSolver(
      BitcoinTransaction base_transaction,
      double fee_rate,
      const std::vector<BitcoinTransaction::TxInputGroup>& input_groups);
  ~BitcoinMaxSendSolver();

  base::expected<BitcoinTransaction, std::string> Solve();

 private:
  BitcoinTransaction base_transaction_;
  double fee_rate_ = 0;
  std::vector<BitcoinTransaction::TxInputGroup> input_groups_;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BITCOIN_BITCOIN_MAX_SEND_SOLVER_H_
