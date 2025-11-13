/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_DATABASE_TABLE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_DATABASE_TABLE_H_

#include <map>
#include <optional>
#include <string>

#include "base/functional/callback.h"
#include "qorai/components/qorai_ads/core/internal/database/database_table_interface.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"
#include "qorai/components/qorai_ads/core/public/ads_callback.h"

namespace qorai_ads {

struct CreativeDepositInfo;
struct DepositInfo;

namespace database::table {

using GetDepositsCallback =
    base::OnceCallback<void(bool success, std::optional<DepositInfo> deposit)>;

class Deposits final : public TableInterface {
 public:
  void Save(const DepositInfo& deposit, ResultCallback callback);

  void Insert(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
              const std::map</*creative_instance_id*/ std::string,
                             CreativeDepositInfo>& deposits);
  void Insert(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
              const DepositInfo& deposit);

  void GetForCreativeInstanceId(const std::string& creative_instance_id,
                                GetDepositsCallback callback) const;

  void PurgeExpired(ResultCallback callback) const;

  std::string GetTableName() const override;

  void Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) override;
  void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               int to_version) override;

 private:
  std::string BuildInsertSql(
      const mojom::DBActionInfoPtr& mojom_db_action,
      const std::map</*creative_instance_id*/ std::string, CreativeDepositInfo>&
          deposits) const;
  std::string BuildInsertSql(const mojom::DBActionInfoPtr& mojom_db_action,
                             const DepositInfo& deposit) const;
};

}  // namespace database::table

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_DATABASE_TABLE_H_
