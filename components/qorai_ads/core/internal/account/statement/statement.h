/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_H_

#include "base/functional/callback.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

using BuildStatementCallback =
    base::OnceCallback<void(mojom::StatementInfoPtr mojom_statement)>;

void BuildStatement(BuildStatementCallback callback);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_STATEMENT_STATEMENT_H_
