/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_TRANSACTION_CALLBACK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_TRANSACTION_CALLBACK_H_

#include "base/functional/callback_forward.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

using RunDBTransactionCallback = base::OnceCallback<void(
    mojom::DBTransactionResultInfoPtr mojom_db_transaction_result)>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_TRANSACTION_CALLBACK_H_
