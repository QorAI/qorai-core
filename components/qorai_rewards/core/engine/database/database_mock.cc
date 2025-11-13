/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_rewards/core/engine/database/database_mock.h"

namespace qorai_rewards::internal::database {

MockDatabase::MockDatabase(RewardsEngine& engine) : Database(engine) {}

MockDatabase::~MockDatabase() = default;

}  // namespace qorai_rewards::internal::database
