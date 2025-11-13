/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TOKEN_ISSUERS_TOKEN_ISSUER_VALUE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TOKEN_ISSUERS_TOKEN_ISSUER_VALUE_UTIL_H_

#include <optional>

#include "base/values.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"

namespace qorai_ads {

base::Value::List TokenIssuersToValue(const TokenIssuerList& token_issuers);
std::optional<TokenIssuerList> TokenIssuersFromValue(
    const base::Value::List& list);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TOKEN_ISSUERS_TOKEN_ISSUER_VALUE_UTIL_H_
