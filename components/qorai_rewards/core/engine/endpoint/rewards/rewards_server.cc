/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */
#include "qorai/components/qorai_rewards/core/engine/endpoint/rewards/rewards_server.h"

#include "qorai/components/qorai_rewards/core/engine/rewards_engine.h"

namespace qorai_rewards::internal::endpoint {

RewardsServer::RewardsServer(RewardsEngine& engine)
    : get_prefix_list_(engine) {}

RewardsServer::~RewardsServer() = default;

}  // namespace qorai_rewards::internal::endpoint
