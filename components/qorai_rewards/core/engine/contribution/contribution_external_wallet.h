/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CONTRIBUTION_CONTRIBUTION_EXTERNAL_WALLET_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CONTRIBUTION_CONTRIBUTION_EXTERNAL_WALLET_H_

#include <map>
#include <string>

#include "base/memory/raw_ref.h"
#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace contribution {

class ContributionExternalWallet {
 public:
  explicit ContributionExternalWallet(RewardsEngine& engine);

  ~ContributionExternalWallet();

  void Process(const std::string& contribution_id, ResultCallback callback);

  void Retry(mojom::ContributionInfoPtr contribution, ResultCallback callback);

 private:
  void ContributionInfo(ResultCallback callback,
                        mojom::ContributionInfoPtr contribution);

  void OnServerPublisherInfo(const std::string& contribution_id,
                             double amount,
                             mojom::RewardsType type,
                             mojom::ContributionProcessor processor,
                             bool single_publisher,
                             ResultCallback callback,
                             mojom::ServerPublisherInfoPtr info);

  void Completed(bool single_publisher,
                 ResultCallback callback,
                 mojom::Result result);

  const raw_ref<RewardsEngine> engine_;
  base::WeakPtrFactory<ContributionExternalWallet> weak_factory_{this};
};

}  // namespace contribution
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CONTRIBUTION_CONTRIBUTION_EXTERNAL_WALLET_H_
