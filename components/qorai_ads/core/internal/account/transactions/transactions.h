/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTIONS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTIONS_H_

#include <string>

#include "base/functional/callback.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_info.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace base {
class Time;
}  // namespace base

namespace qorai_ads {

using AddTransactionCallback =
    base::OnceCallback<void(bool success, const TransactionInfo& transaction)>;

using GetTransactionsCallback =
    base::OnceCallback<void(bool success, const TransactionList& transactions)>;

TransactionInfo BuildTransaction(
    const std::string& creative_instance_id,
    const std::string& segment,
    double value,
    mojom::AdType mojom_ad_type,
    mojom::ConfirmationType mojom_confirmation_type);

TransactionInfo AddTransaction(const std::string& creative_instance_id,
                               const std::string& segment,
                               double value,
                               mojom::AdType mojom_ad_type,
                               mojom::ConfirmationType mojom_confirmation_type,
                               AddTransactionCallback callback);

void GetTransactionsForDateRange(base::Time from_time,
                                 base::Time to_time,
                                 GetTransactionsCallback callback);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTIONS_H_
