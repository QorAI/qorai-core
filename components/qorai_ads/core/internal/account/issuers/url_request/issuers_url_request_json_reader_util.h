/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_URL_REQUEST_ISSUERS_URL_REQUEST_JSON_READER_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_URL_REQUEST_ISSUERS_URL_REQUEST_JSON_READER_UTIL_H_

#include <optional>

#include "base/values.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"

namespace qorai_ads::json::reader {

std::optional<int> ParsePing(const base::Value::Dict& dict);
std::optional<TokenIssuerList> ParseTokenIssuers(const base::Value::Dict& dict);

}  // namespace qorai_ads::json::reader

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_URL_REQUEST_ISSUERS_URL_REQUEST_JSON_READER_UTIL_H_
