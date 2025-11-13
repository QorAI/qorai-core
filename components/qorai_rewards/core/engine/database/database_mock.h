/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_MOCK_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_MOCK_H_

#include <string>
#include <vector>

#include "qorai/components/qorai_rewards/core/engine/database/database.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_rewards::internal {
namespace database {

class MockDatabase : public Database {
 public:
  explicit MockDatabase(RewardsEngine& engine);

  ~MockDatabase() override;

  MOCK_METHOD2(GetContributionInfo,
               void(const std::string& contribution_id,
                    GetContributionInfoCallback callback));

  MOCK_METHOD2(GetSpendableUnblindedTokensByBatchTypes,
               void(const std::vector<mojom::CredsBatchType>& batch_types,
                    GetUnblindedTokenListCallback callback));
};

}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_MOCK_H_
