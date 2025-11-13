/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V31_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V31_H_

namespace qorai_rewards::internal {
namespace database {
namespace migration {

// Migration 31 adds a contribution processor field to the pending_contribution
// table so that we do not attempt to retry contributions in publisher/user
// wallet mismatch scenarios.
const char v31[] = R"(
  ALTER TABLE pending_contribution ADD processor INTEGER DEFAULT 0 NOT NULL;
)";

}  // namespace migration
}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V31_H_
