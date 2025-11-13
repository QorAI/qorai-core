/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_EVENT_LOG_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_EVENT_LOG_H_

#include <map>
#include <string>

#include "qorai/components/qorai_rewards/core/engine/database/database_table.h"

namespace qorai_rewards::internal {
namespace database {

class DatabaseEventLog : public DatabaseTable {
 public:
  explicit DatabaseEventLog(RewardsEngine& engine);
  ~DatabaseEventLog() override;

  void Insert(const std::string& key, const std::string& value);

  void InsertRecords(const std::map<std::string, std::string>& records,
                     ResultCallback callback);

  // returns last 2000 records
  void GetLastRecords(GetEventLogsCallback callback);

 private:
  void OnGetAllRecords(GetEventLogsCallback callback,
                       mojom::DBCommandResponsePtr response);
};

}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_EVENT_LOG_H_
