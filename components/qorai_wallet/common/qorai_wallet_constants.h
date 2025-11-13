/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_COMMON_QORAI_WALLET_CONSTANTS_H_
#define QORAI_COMPONENTS_QORAI_WALLET_COMMON_QORAI_WALLET_CONSTANTS_H_

namespace qorai_wallet {

inline constexpr size_t kSolanaKeypairSize = 64;
inline constexpr size_t kSolanaSignatureSize = 64;
inline constexpr size_t kSolanaPrikeySize = 32;
inline constexpr size_t kSolanaPubkeySize = 32;
inline constexpr size_t kSolanaHashSize = 32;
// 1232 = 1280(IPv6 minimum MTU) - 40(size of the IPv6 header) - 8(size of the
// fragment header)
inline constexpr size_t kSolanaMaxTxSize = 1232;

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_COMMON_QORAI_WALLET_CONSTANTS_H_
