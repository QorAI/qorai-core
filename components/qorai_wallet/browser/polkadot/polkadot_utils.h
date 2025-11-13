/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_POLKADOT_POLKADOT_UTILS_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_POLKADOT_POLKADOT_UTILS_H_

namespace qorai_wallet {

// See definition for "path": ["sp_core", "crypto", "AccountId32"]
// https://raw.githubusercontent.com/polkadot-js/api/refs/heads/master/packages/types-support/src/metadata/v16/substrate-types.json
inline constexpr const size_t kPolkadotSubstrateAccountIdSize = 32;

inline constexpr const size_t kPolkadotBlockHashSize = 32;

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_POLKADOT_POLKADOT_UTILS_H_
