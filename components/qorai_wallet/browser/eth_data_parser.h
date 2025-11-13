/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ETH_DATA_PARSER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ETH_DATA_PARSER_H_

#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

std::optional<std::tuple<mojom::TransactionType,    // tx_type
                         std::vector<std::string>,  // tx_params
                         std::vector<std::string>,  // tx_args
                         mojom::SwapInfoPtr>>       // swap_info
GetTransactionInfoFromData(const std::vector<uint8_t>& data);

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ETH_DATA_PARSER_H_
