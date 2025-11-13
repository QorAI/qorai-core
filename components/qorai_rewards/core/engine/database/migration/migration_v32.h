/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V32_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V32_H_

namespace qorai_rewards::internal {
namespace database {
namespace migration {

// Migration 32 archives additional data associated with "BAP" (a deprecated
// Japan-specific presentation of QOR).
const char v32[] = R"sql(
  CREATE TABLE balance_report_info_bap AS SELECT * from balance_report_info;
  DELETE FROM balance_report_info;
)sql";

}  // namespace migration
}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V32_H_
