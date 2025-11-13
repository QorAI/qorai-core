/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/deposits/deposits_database_util.h"

#include "base/functional/bind.h"
#include "qorai/components/qorai_ads/core/internal/account/deposits/deposits_database_table.h"
#include "qorai/components/qorai_ads/core/internal/common/logging_util.h"

namespace qorai_ads::database {

void PurgeExpiredDeposits() {
  const table::Deposits database_table;
  database_table.PurgeExpired(base::BindOnce([](bool success) {
    if (!success) {
      return BLOG(0, "Failed to purge expired deposits");
    }

    BLOG(3, "Successfully purged expired deposits");
  }));
}

}  // namespace qorai_ads::database
