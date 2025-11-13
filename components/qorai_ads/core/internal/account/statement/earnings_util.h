/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_EARNINGS_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_EARNINGS_UTIL_H_

#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_info.h"

namespace qorai_ads {

double GetUnreconciledEarnings(const TransactionList& transactions);
double GetReconciledEarningsForThisMonth(const TransactionList& transactions);
double GetReconciledEarningsForPreviousMonth(
    const TransactionList& transactions);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_EARNINGS_UTIL_H_
