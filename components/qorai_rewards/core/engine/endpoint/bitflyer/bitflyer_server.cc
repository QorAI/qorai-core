/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_rewards/core/engine/endpoint/bitflyer/bitflyer_server.h"

#include "qorai/components/qorai_rewards/core/engine/rewards_engine.h"

namespace qorai_rewards::internal::endpoint {

BitflyerServer::BitflyerServer(RewardsEngine& engine)
    : get_balance_(engine), post_oauth_(engine) {}

BitflyerServer::~BitflyerServer() = default;

}  // namespace qorai_rewards::internal::endpoint
