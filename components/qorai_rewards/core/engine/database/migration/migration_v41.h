/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V41_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V41_H_

namespace qorai_rewards::internal::database::migration {

// Migration 41 removes the publisher prefix list table after storage was moved
// to a separate file.
inline constexpr char v41[] = R"sql(
  DROP TABLE IF EXISTS publisher_prefix_list;
)sql";

}  // namespace qorai_rewards::internal::database::migration

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V41_H_
