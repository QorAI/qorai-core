/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_TABLE_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_TABLE_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards_database.mojom.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards_engine_internal.mojom.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace database {

using ContributionPublisherInfoPair =
    std::pair<std::string, mojom::PublisherInfoPtr>;

using ServerPublisherLinksCallback =
    base::OnceCallback<void(const std::map<std::string, std::string>& links)>;

using ServerPublisherAmountsCallback =
    base::OnceCallback<void(const std::vector<double>& amounts)>;

using ContributionQueuePublishersListCallback =
    base::OnceCallback<void(std::vector<mojom::ContributionQueuePublisherPtr>)>;

using ContributionPublisherListCallback =
    base::OnceCallback<void(std::vector<mojom::ContributionPublisherPtr>)>;

using ContributionPublisherPairListCallback =
    base::OnceCallback<void(std::vector<ContributionPublisherInfoPair>)>;

class DatabaseTable {
 public:
  explicit DatabaseTable(RewardsEngine& engine);
  virtual ~DatabaseTable();

 protected:
  const raw_ref<RewardsEngine> engine_;
};

}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_DATABASE_TABLE_H_
