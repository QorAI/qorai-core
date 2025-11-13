/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_CONFIRMATION_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_CONFIRMATION_UTIL_H_

#include <optional>
#include <string>

#include "base/values.h"

namespace qorai_ads {

struct ConfirmationInfo;
struct TransactionInfo;

std::optional<std::string> BuildRewardCredential(
    const ConfirmationInfo& confirmation);

std::optional<ConfirmationInfo> BuildRewardConfirmation(
    const TransactionInfo& transaction,
    base::Value::Dict user_data);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_CONFIRMATION_UTIL_H_
