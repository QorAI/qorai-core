/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/legacy_migration/database/database_raze.h"

#include <utility>

#include "base/location.h"
#include "qorai/components/qorai_ads/core/internal/common/database/database_transaction_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

namespace qorai_ads::database {

void Raze(ResultCallback callback) {
  mojom::DBTransactionInfoPtr mojom_db_transaction =
      mojom::DBTransactionInfo::New();
  Raze(mojom_db_transaction);

  RunTransaction(FROM_HERE, std::move(mojom_db_transaction),
                 std::move(callback));
}

}  // namespace qorai_ads::database
