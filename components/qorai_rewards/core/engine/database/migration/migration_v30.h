/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V30_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V30_H_

namespace qorai_rewards::internal {
namespace database {
namespace migration {

// On migration away from "BAP" (a Japan-specific presentation of QOR), copy
// the data in the unblinded_tokens table to an archive table and clear the
// unblinded_tokens table.
const char v30[] = R"(
  CREATE TABLE unblinded_tokens_bap AS SELECT * from unblinded_tokens;
  DELETE FROM unblinded_tokens;
)";

}  // namespace migration
}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V30_H_
