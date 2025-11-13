/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V40_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V40_H_

namespace qorai_rewards::internal::database::migration {

// Migration 40 removes the pending contributions table.
inline constexpr char v40[] = R"sql(
  DROP TABLE IF EXISTS pending_contribution;
  DROP TABLE IF EXISTS processed_publisher;
)sql";

}  // namespace qorai_rewards::internal::database::migration

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V40_H_
