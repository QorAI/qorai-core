/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_RECONCILED_TRANSACTIONS_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_RECONCILED_TRANSACTIONS_UTIL_H_

#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_info.h"

namespace base {
class Time;
}  // namespace base

namespace qorai_ads {

bool DidReconcileTransaction(const TransactionInfo& transaction);
bool DidReconcileTransactionsPreviousMonth(const TransactionList& transactions);
bool DidReconcileTransactionsThisMonth(const TransactionList& transactions);
bool DidReconcileTransactionWithinDateRange(const TransactionInfo& transaction,
                                            base::Time from_time,
                                            base::Time to_time);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_RECONCILED_TRANSACTIONS_UTIL_H_
