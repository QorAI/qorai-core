/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/database/database_table_interface.h"

#include "base/check.h"
#include "qorai/components/qorai_ads/core/internal/legacy_migration/database/database_constants.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

namespace qorai_ads::database {

void TableInterface::Migrate(
    const mojom::DBTransactionInfoPtr& mojom_db_transaction,
    int to_version) {
  CHECK(mojom_db_transaction);

  if (to_version == kVersionNumber) {
    Create(mojom_db_transaction);
  }
}

}  // namespace qorai_ads::database
