/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_CONTRIBUTION_QUEUE_PUBLISHERS_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_CONTRIBUTION_QUEUE_PUBLISHERS_H_

#include <string>
#include <vector>

#include "qorai/components/qorai_rewards/core/engine/database/database_table.h"

namespace qorai_rewards::internal {
namespace database {

class DatabaseContributionQueuePublishers : public DatabaseTable {
 public:
  explicit DatabaseContributionQueuePublishers(RewardsEngine& engine);
  ~DatabaseContributionQueuePublishers() override;

  void InsertOrUpdate(const std::string& id,
                      std::vector<mojom::ContributionQueuePublisherPtr> list,
                      ResultCallback callback);

  void GetRecordsByQueueId(const std::string& queue_id,
                           ContributionQueuePublishersListCallback callback);

 private:
  void OnGetRecordsByQueueId(ContributionQueuePublishersListCallback callback,
                             mojom::DBCommandResponsePtr response);
};

}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_CONTRIBUTION_QUEUE_PUBLISHERS_H_
