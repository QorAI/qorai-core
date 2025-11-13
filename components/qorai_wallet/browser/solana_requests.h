/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_SOLANA_REQUESTS_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_SOLANA_REQUESTS_H_

#include <optional>
#include <string>
#include <vector>

#include "qorai/components/qorai_wallet/browser/solana_transaction.h"

namespace qorai_wallet {

namespace solana {

std::string getBalance(const std::string& pubkey);
std::string getTokenAccountBalance(const std::string& pubkey);
std::string sendTransaction(
    const std::string& signed_tx,
    std::optional<SolanaTransaction::SendOptions> options);
std::string getLatestBlockhash();
std::string getSignatureStatuses(const std::vector<std::string>& tx_signatures);
std::string getAccountInfo(const std::string& pubkey);
std::string getFeeForMessage(const std::string& message);
std::string getBlockHeight();
std::string getTokenAccountsByOwner(const std::string& pubkey,
                                    const std::string& encoding,
                                    const std::string& program_id);
std::string isBlockhashValid(const std::string& blockhash,
                             const std::optional<std::string>& commitment);
std::string simulateTransaction(const std::string& unsigned_tx);
std::string getRecentPrioritizationFees();

}  // namespace solana

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_SOLANA_REQUESTS_H_
