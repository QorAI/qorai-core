/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_REWARDS_DATABASE_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_REWARDS_DATABASE_H_

#include <memory>

#include "base/files/file_path.h"
#include "base/memory/memory_pressure_listener.h"
#include "base/sequence_checker.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards_database.mojom.h"
#include "sql/database.h"
#include "sql/init_status.h"
#include "sql/meta_table.h"

namespace qorai_rewards::internal {

class RewardsDatabase : public mojom::RewardsDatabase {
 public:
  explicit RewardsDatabase(const base::FilePath& path);

  RewardsDatabase(const RewardsDatabase&) = delete;
  RewardsDatabase& operator=(const RewardsDatabase&) = delete;

  ~RewardsDatabase() override;

  mojom::DBCommandResponsePtr RunTransaction(
      mojom::DBTransactionPtr transaction);

  sql::Database* GetInternalDatabaseForTesting() { return &db_; }

  // mojom::RewardsDatabase:
  void RunDBTransaction(mojom::DBTransactionPtr transaction,
                        RunDBTransactionCallback callback) override;

 private:
  mojom::DBCommandResponse::Status Initialize(
      int32_t version,
      int32_t compatible_version,
      mojom::DBCommandResponse* command_response);

  mojom::DBCommandResponse::Status Execute(mojom::DBCommand* command);

  mojom::DBCommandResponse::Status Run(mojom::DBCommand* command);

  mojom::DBCommandResponse::Status Read(
      mojom::DBCommand* command,
      mojom::DBCommandResponse* command_response);

  mojom::DBCommandResponse::Status Migrate(int32_t version,
                                           int32_t compatible_version);

  bool ShouldCreateTables();

  int GetTablesCount();

  void OnMemoryPressure(
      base::MemoryPressureListener::MemoryPressureLevel memory_pressure_level);

  const base::FilePath db_path_;
  sql::Database db_;
  sql::MetaTable meta_table_;
  bool initialized_ = false;

  std::unique_ptr<base::MemoryPressureListener> memory_pressure_listener_;

  SEQUENCE_CHECKER(sequence_checker_);
};

}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_REWARDS_DATABASE_H_
