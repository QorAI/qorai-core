/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_REQUEST_SIGNED_TOKENS_REQUEST_SIGNED_TOKENS_URL_REQUEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_REQUEST_SIGNED_TOKENS_REQUEST_SIGNED_TOKENS_URL_REQUEST_UTIL_H_

#include <optional>
#include <string>

#include "base/values.h"

namespace qorai_ads {

std::optional<bool> ParseIsEligible(const base::Value::Dict& dict);

std::optional<std::string> ParseNonce(const base::Value::Dict& dict);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_REQUEST_SIGNED_TOKENS_REQUEST_SIGNED_TOKENS_URL_REQUEST_UTIL_H_
