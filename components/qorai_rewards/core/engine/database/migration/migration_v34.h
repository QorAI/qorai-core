/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V34_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V34_H_

namespace qorai_rewards::internal {
namespace database {
namespace migration {

// Migration 34 adds a "claimable_until" field to the promotion database so that
// a "days to claim" countdown can be displayed to the user.
const char v34[] = R"(
  ALTER TABLE promotion ADD COLUMN claimable_until INTEGER;
)";

}  // namespace migration
}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V34_H_
