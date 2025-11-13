/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_SIMULATION_RESPONSE_PARSER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_SIMULATION_RESPONSE_PARSER_H_

#include <optional>
#include <string>

#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

namespace evm {

mojom::EVMSimulationResponsePtr ParseSimulationResponse(
    const base::Value& json_value,
    const std::string& user_account);

}  // namespace evm

namespace solana {

mojom::SolanaSimulationResponsePtr ParseSimulationResponse(
    const base::Value& json_value,
    const std::string& user_account);

}  // namespace solana

std::optional<std::string> ParseSimulationErrorResponse(
    const base::Value& json_value);

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_SIMULATION_RESPONSE_PARSER_H_
