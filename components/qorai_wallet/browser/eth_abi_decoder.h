/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ETH_ABI_DECODER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ETH_ABI_DECODER_H_

#include <optional>
#include <string>
#include <vector>

#include "base/values.h"
#include "qorai/components/qorai_wallet/common/eth_abi_utils.h"

namespace qorai_wallet {

std::optional<std::vector<std::string>> UniswapEncodedPathDecode(
    const std::string& encoded_path);

std::optional<base::Value::List> ABIDecode(const eth_abi::Type& type,
                                           base::span<const uint8_t> input);

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ETH_ABI_DECODER_H_
