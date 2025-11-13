/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BIP39_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BIP39_H_

#include <array>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "base/containers/span.h"

// Utility functions for BIP39 mnemonics support.
// https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki
namespace qorai_wallet::bip39 {

inline constexpr uint32_t kSeedSize = 64;
inline constexpr uint32_t kDefaultEntropySize = 16;
inline constexpr uint32_t kLegacyEthEntropySize = 32;

// Generate mnemonic from entropy bytes following BIP39.
// If |entropy.size()| is not in 16, 20, 24, 28, 32 range or
// allocation failure, the std::nullopt will be returned.
std::optional<std::string> GenerateMnemonic(base::span<const uint8_t> entropy);

// Generate 64 bytes seed from mnemonic following BIP39.
std::optional<std::vector<uint8_t>> MnemonicToSeed(
    std::string_view mnemonic,
    std::string_view passphrase = "");

// This is mainly used for restoring legacy qorai crypto wallet
std::optional<std::vector<uint8_t>> MnemonicToEntropy(
    std::string_view mnemonic);

// Generate a seed in a manner compatible with Polkadot.
// See the implementation of this function for more details.
std::optional<std::array<uint8_t, kSeedSize>> MnemonicToEntropyToSeed(
    std::string_view mnemonic,
    std::string_view password = "");

bool IsValidMnemonic(std::string_view mnemonic);

}  // namespace qorai_wallet::bip39

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BIP39_H_
