/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TOKEN_ISSUERS_TOKEN_ISSUER_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TOKEN_ISSUERS_TOKEN_ISSUER_UTIL_H_

#include <optional>

#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_types.h"

namespace qorai_ads {

struct IssuersInfo;
struct TokenIssuerInfo;

namespace cbr {
class PublicKey;
}  // namespace cbr

bool TokenIssuerExistsForType(TokenIssuerType token_issuer_type);

std::optional<TokenIssuerInfo> GetTokenIssuerForType(
    const IssuersInfo& issuers,
    TokenIssuerType token_issuer_type);

bool TokenIssuerPublicKeyExistsForType(TokenIssuerType token_issuer_type,
                                       const cbr::PublicKey& public_key);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TOKEN_ISSUERS_TOKEN_ISSUER_UTIL_H_
