/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTIONS_DATABASE_TABLE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTIONS_DATABASE_TABLE_H_

#include <string>

#include "base/functional/callback.h"
#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_info.h"
#include "qorai/components/qorai_ads/core/internal/database/database_table_interface.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"
#include "qorai/components/qorai_ads/core/public/ads_callback.h"

namespace base {
class Time;
}  // namespace base

namespace qorai_ads::database::table {

using GetTransactionsCallback =
    base::OnceCallback<void(bool success, const TransactionList& transactions)>;

class Transactions final : public TableInterface {
 public:
  void Save(const TransactionList& transactions, ResultCallback callback);

  void GetForDateRange(base::Time from_time,
                       base::Time to_time,
                       GetTransactionsCallback callback) const;

  void Reconcile(const PaymentTokenList& payment_tokens,
                 ResultCallback callback) const;

  void PurgeExpired(ResultCallback callback) const;

  std::string GetTableName() const override;

  void Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) override;
  void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               int to_version) override;

 private:
  void Insert(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
              const TransactionList& transactions);

  std::string BuildInsertSql(const mojom::DBActionInfoPtr& mojom_db_action,
                             const TransactionList& transactions) const;
};

}  // namespace qorai_ads::database::table

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTIONS_DATABASE_TABLE_H_
