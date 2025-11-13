/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"

namespace qorai_ads {

TokenIssuerInfo::TokenIssuerInfo() = default;

TokenIssuerInfo::TokenIssuerInfo(const TokenIssuerInfo& other) = default;

TokenIssuerInfo& TokenIssuerInfo::operator=(const TokenIssuerInfo& other) =
    default;

TokenIssuerInfo::TokenIssuerInfo(TokenIssuerInfo&& other) noexcept = default;

TokenIssuerInfo& TokenIssuerInfo::operator=(TokenIssuerInfo&& other) noexcept =
    default;

TokenIssuerInfo::~TokenIssuerInfo() = default;

}  // namespace qorai_ads
