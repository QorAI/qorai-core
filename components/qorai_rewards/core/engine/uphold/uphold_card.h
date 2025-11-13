/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UPHOLD_UPHOLD_CARD_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UPHOLD_UPHOLD_CARD_H_

#include <string>

#include "base/functional/callback_forward.h"
#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_rewards/core/engine/endpoint/uphold/uphold_server.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace uphold {

inline constexpr char kCardName[] = "Qorai Browser";

using CreateCardCallback =
    base::OnceCallback<void(mojom::Result, std::string&& id)>;

class UpholdCard {
 public:
  explicit UpholdCard(RewardsEngine& engine);

  ~UpholdCard();

  void CreateQORCardIfNecessary(const std::string& access_token,
                                CreateCardCallback) const;

 private:
  void OnGetQORCardId(CreateCardCallback,
                      const std::string& access_token,
                      mojom::Result,
                      std::string&& id) const;

  void OnCreateQORCard(CreateCardCallback,
                       const std::string& access_token,
                       mojom::Result,
                       std::string&& id) const;

  void OnUpdateQORCardSettings(CreateCardCallback,
                               std::string&& id,
                               mojom::Result) const;

  const raw_ref<RewardsEngine> engine_;
  endpoint::UpholdServer uphold_server_;
};

}  // namespace uphold
}  // namespace qorai_rewards::internal
#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UPHOLD_UPHOLD_CARD_H_
