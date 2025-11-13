/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/rotating_hash_user_data.h"

#include <optional>
#include <string>

#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_info.h"
#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/rotating_hash_user_data_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings.h"

namespace qorai_ads {

namespace {
constexpr char kRotatingHashKey[] = "rotatingHash";
}  // namespace

base::Value::Dict BuildRotatingHashUserData(
    const TransactionInfo& transaction) {
  if (!UserHasJoinedQoraiRewards()) {
    return {};
  }

  std::optional<std::string> rotating_hash = BuildRotatingHash(transaction);
  if (!rotating_hash) {
    // Invalid rotating hash.
    return {};
  }

  return base::Value::Dict().Set(kRotatingHashKey, *rotating_hash);
}

}  // namespace qorai_ads
