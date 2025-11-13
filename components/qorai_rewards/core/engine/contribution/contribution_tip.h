/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CONTRIBUTION_CONTRIBUTION_TIP_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CONTRIBUTION_CONTRIBUTION_TIP_H_

#include <optional>
#include <string>

#include "base/functional/callback_forward.h"
#include "base/memory/raw_ref.h"
#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"

namespace qorai_rewards::internal {

class RewardsEngine;

namespace contribution {

class ContributionTip {
 public:
  explicit ContributionTip(RewardsEngine& engine);

  ~ContributionTip();

  using ProcessCallback = base::OnceCallback<void(std::optional<std::string>)>;

  void Process(const std::string& publisher_id,
               double amount,
               ProcessCallback callback);

 private:
  void OnPublisherDataRead(const std::string& publisher_id,
                           double amount,
                           ProcessCallback callback,
                           mojom::ServerPublisherInfoPtr server_info);

  void OnQueueSaved(const std::string& queue_id,
                    ProcessCallback callback,
                    mojom::Result result);

  void OnPendingTipSaved(mojom::Result result);

  const raw_ref<RewardsEngine> engine_;
  base::WeakPtrFactory<ContributionTip> weak_factory_{this};
};

}  // namespace contribution
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CONTRIBUTION_CONTRIBUTION_TIP_H_
