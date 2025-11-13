/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_INITIALIZE_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_INITIALIZE_H_

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_rewards/core/engine/database/database_migration.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace database {

class DatabaseInitialize {
 public:
  explicit DatabaseInitialize(RewardsEngine& engine);
  ~DatabaseInitialize();

  void Start(ResultCallback callback);

 private:
  void OnInitialize(ResultCallback callback,
                    mojom::DBCommandResponsePtr response);

  const raw_ref<RewardsEngine> engine_;
  DatabaseMigration migration_;
};

}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_INITIALIZE_H_
