/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V39_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V39_H_

namespace qorai_rewards::internal::database::migration {

// Migration 39 adds a `web3_url` field to the publisher banner table in order
// to support P2P creator contributions.
inline constexpr char v39[] = R"sql(
  ALTER TABLE server_publisher_banner ADD COLUMN web3_url TEXT;
)sql";

}  // namespace qorai_rewards::internal::database::migration

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V39_H_
