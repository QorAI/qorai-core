/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_BITFLYER_BITFLYER_SERVER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_BITFLYER_BITFLYER_SERVER_H_

#include "qorai/components/qorai_rewards/core/engine/endpoint/bitflyer/get_balance/get_balance_bitflyer.h"
#include "qorai/components/qorai_rewards/core/engine/endpoint/bitflyer/post_oauth/post_oauth_bitflyer.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace endpoint {

class BitflyerServer {
 public:
  explicit BitflyerServer(RewardsEngine& engine);
  ~BitflyerServer();

  bitflyer::GetBalance& get_balance() { return get_balance_; }

  bitflyer::PostOauth& post_oauth() { return post_oauth_; }

 private:
  bitflyer::GetBalance get_balance_;
  bitflyer::PostOauth post_oauth_;
};

}  // namespace endpoint
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_BITFLYER_BITFLYER_SERVER_H_
