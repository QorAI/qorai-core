/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V16_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V16_H_

namespace qorai_rewards::internal {
namespace database {
namespace migration {

const char v16[] = R"(
  UPDATE contribution_info SET
  created_at = (
    CASE WHEN datetime(created_at, 'unixepoch') IS NULL
    THEN strftime('%s', datetime(created_at))
    ELSE created_at END
  );
)";

}  // namespace migration
}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V16_H_
