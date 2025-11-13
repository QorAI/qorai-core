/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_ADS_RECEIVED_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_ADS_RECEIVED_UTIL_H_

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_info.h"

namespace base {
class Time;
}  // namespace base

namespace qorai_ads {

size_t GetAdsReceivedForDateRange(const TransactionList& transactions,
                                  base::Time from_time,
                                  base::Time to_time);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_ADS_RECEIVED_UTIL_H_
