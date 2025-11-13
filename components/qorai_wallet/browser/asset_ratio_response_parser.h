/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ASSET_RATIO_RESPONSE_PARSER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ASSET_RATIO_RESPONSE_PARSER_H_

#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "base/values.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

// New API v1 response parser for /api/pricing/v1/getPrices
std::vector<mojom::AssetPricePtr> ParseAssetPrices(
    const base::Value& json_value);

bool ParseAssetPriceHistory(const base::Value& json_value,
                            std::vector<mojom::AssetTimePricePtr>* values);
std::optional<std::vector<mojom::CoinMarketPtr>> ParseCoinMarkets(
    const base::Value& json_value);

std::optional<std::string> ParseStripeBuyURL(const base::Value& json_value);

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ASSET_RATIO_RESPONSE_PARSER_H_
