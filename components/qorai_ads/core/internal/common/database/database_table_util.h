/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_TABLE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_TABLE_UTIL_H_

#include <string>
#include <vector>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads::database {

void CreateTableIndex(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                      const std::string& table_name,
                      const std::vector<std::string>& columns);

void DropTableIndex(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                    const std::string& index_name);

void DropTable(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               const std::string& table_name);

void DeleteTable(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                 const std::string& table_name);

void CopyTableColumns(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                      const std::string& from,
                      const std::string& to,
                      const std::vector<std::string>& from_columns,
                      const std::vector<std::string>& to_columns,
                      bool should_drop);

void CopyTableColumns(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                      const std::string& from,
                      const std::string& to,
                      const std::vector<std::string>& columns,
                      bool should_drop);

void RenameTable(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                 const std::string& from,
                 const std::string& to);

}  // namespace qorai_ads::database

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_TABLE_UTIL_H_
