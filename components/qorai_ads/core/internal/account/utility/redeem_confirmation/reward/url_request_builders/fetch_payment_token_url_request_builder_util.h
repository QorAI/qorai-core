/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REWARD_URL_REQUEST_BUILDERS_FETCH_PAYMENT_TOKEN_URL_REQUEST_BUILDER_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REWARD_URL_REQUEST_BUILDERS_FETCH_PAYMENT_TOKEN_URL_REQUEST_BUILDER_UTIL_H_

#include <string>

namespace qorai_ads {

std::string BuildFetchPaymentTokenUrlPath(const std::string& transaction_id);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REWARD_URL_REQUEST_BUILDERS_FETCH_PAYMENT_TOKEN_URL_REQUEST_BUILDER_UTIL_H_
