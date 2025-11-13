/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/created_at_timestamp_user_data.h"

#include "base/check.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_info.h"
#include "qorai/components/qorai_ads/core/internal/common/time/time_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings.h"

namespace qorai_ads {

namespace {
constexpr char kCreatedAtTimestampKey[] = "createdAtTimestamp";
}  // namespace

base::Value::Dict BuildCreatedAtTimestampUserData(
    const TransactionInfo& transaction) {
  CHECK(transaction.IsValid());

  if (!UserHasJoinedQoraiRewards()) {
    return {};
  }

  return base::Value::Dict().Set(
      kCreatedAtTimestampKey,
      TimeToPrivacyPreservingIso8601(*transaction.created_at));
}

}  // namespace qorai_ads
