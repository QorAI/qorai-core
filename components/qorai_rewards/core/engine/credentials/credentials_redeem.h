/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CREDENTIALS_CREDENTIALS_REDEEM_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CREDENTIALS_CREDENTIALS_REDEEM_H_

#include <string>
#include <vector>

#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards_engine_internal.mojom.h"

namespace qorai_rewards::internal {
namespace credential {

struct CredentialsRedeem {
  CredentialsRedeem();
  CredentialsRedeem(const CredentialsRedeem& info);
  ~CredentialsRedeem();

  std::string publisher_key;
  mojom::RewardsType type;
  mojom::ContributionProcessor processor;
  std::vector<mojom::UnblindedToken> token_list;
  std::string order_id;
  std::string contribution_id;
};

}  // namespace credential
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CREDENTIALS_CREDENTIALS_REDEEM_H_
