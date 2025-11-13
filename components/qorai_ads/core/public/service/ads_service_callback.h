/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_SERVICE_ADS_SERVICE_CALLBACK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_SERVICE_ADS_SERVICE_CALLBACK_H_

#include <optional>

#include "base/functional/callback.h"
#include "base/values.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

using ClearDataCallback = base::OnceCallback<void(bool success)>;

using GetInternalsCallback =
    base::OnceCallback<void(std::optional<base::Value::Dict> internals)>;

using GetDiagnosticsCallback =
    base::OnceCallback<void(std::optional<base::Value::List> diagnostics)>;

using GetStatementOfAccountsCallback =
    base::OnceCallback<void(mojom::StatementInfoPtr mojom_statement)>;

using PurgeOrphanedAdEventsForTypeCallback =
    base::OnceCallback<void(bool success)>;

// TODO(https://github.com/qorai/qorai-browser/issues/24595): Transition
// GetAdHistory from base::Value to a mojom data structure.
using GetAdHistoryForUICallback =
    base::OnceCallback<void(std::optional<base::Value::List> ad_history)>;

using ToggleReactionCallback = base::OnceCallback<void(bool success)>;

using ShutdownCallback = base::OnceCallback<void(bool success)>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_SERVICE_ADS_SERVICE_CALLBACK_H_
