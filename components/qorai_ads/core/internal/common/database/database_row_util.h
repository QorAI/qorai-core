/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_ROW_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_ROW_UTIL_H_

#include <vector>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"
#include "sql/statement.h"

namespace qorai_ads::database {

[[nodiscard]] mojom::DBRowInfoPtr CreateRow(
    sql::Statement* statement,
    const std::vector<mojom::DBBindColumnType>& mojom_db_bind_column_types);

}  // namespace qorai_ads::database

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_ROW_UTIL_H_
