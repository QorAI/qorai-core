/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V3_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V3_H_

namespace qorai_rewards::internal {
namespace database {
namespace migration {

const char v3[] = R"(
  PRAGMA foreign_keys = off;
    DROP TABLE IF EXISTS pending_contribution;
  PRAGMA foreign_keys = on;

  CREATE TABLE pending_contribution (
    publisher_id LONGVARCHAR NOT NULL,
    amount DOUBLE DEFAULT 0 NOT NULL,
    added_date INTEGER DEFAULT 0 NOT NULL,
    viewing_id LONGVARCHAR NOT NULL,
    category INTEGER NOT NULL,
    CONSTRAINT fk_pending_contribution_publisher_id
      FOREIGN KEY (publisher_id)
      REFERENCES publisher_info (publisher_id)
      ON DELETE CASCADE
  );

  CREATE INDEX pending_contribution_publisher_id_index
    ON pending_contribution (publisher_id);
)";

}  // namespace migration
}  // namespace database
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_DATABASE_MIGRATION_MIGRATION_V3_H_
