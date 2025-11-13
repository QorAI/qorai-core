/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_MELD_INTEGRATION_RESPONSE_PARSER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_MELD_INTEGRATION_RESPONSE_PARSER_H_

#include <optional>
#include <string>
#include <vector>

#include "base/types/expected.h"
#include "base/values.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/common/meld_integration.mojom.h"

namespace qorai_wallet {
std::optional<std::vector<std::string>> ParseMeldErrorResponse(
    const base::Value& json_value);
std::optional<std::vector<mojom::MeldServiceProviderPtr>> ParseServiceProviders(
    const base::Value& json_value);
base::expected<std::vector<mojom::MeldCryptoQuotePtr>, std::string>
ParseCryptoQuotes(const base::Value& json_value);
std::optional<std::vector<mojom::MeldPaymentMethodPtr>> ParsePaymentMethods(
    const base::Value& json_value);
std::optional<std::vector<mojom::MeldFiatCurrencyPtr>> ParseFiatCurrencies(
    const base::Value& json_value);
std::optional<std::vector<mojom::MeldCryptoCurrencyPtr>> ParseCryptoCurrencies(
    const base::Value& json_value);
std::optional<std::vector<mojom::MeldCountryPtr>> ParseCountries(
    const base::Value& json_value);
mojom::MeldCryptoWidgetPtr ParseCryptoWidgetCreate(
    const base::Value& json_value);
}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_MELD_INTEGRATION_RESPONSE_PARSER_H_
