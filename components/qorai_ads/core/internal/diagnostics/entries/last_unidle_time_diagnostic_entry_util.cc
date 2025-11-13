/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/diagnostics/entries/last_unidle_time_diagnostic_entry_util.h"

#include <memory>
#include <utility>

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/diagnostics/diagnostic_manager.h"
#include "qorai/components/qorai_ads/core/internal/diagnostics/entries/last_unidle_time_diagnostic_entry.h"

namespace qorai_ads {

void SetLastUnIdleTimeDiagnosticEntry(base::Time last_unidle_at) {
  auto last_unidle_time_diagnostic_entry =
      std::make_unique<LastUnIdleTimeDiagnosticEntry>(last_unidle_at);

  DiagnosticManager::GetInstance().SetEntry(
      std::move(last_unidle_time_diagnostic_entry));
}

}  // namespace qorai_ads
