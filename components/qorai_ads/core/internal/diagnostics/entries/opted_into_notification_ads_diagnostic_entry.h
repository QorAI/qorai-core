/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DIAGNOSTICS_ENTRIES_OPTED_INTO_NOTIFICATION_ADS_DIAGNOSTIC_ENTRY_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DIAGNOSTICS_ENTRIES_OPTED_INTO_NOTIFICATION_ADS_DIAGNOSTIC_ENTRY_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/diagnostics/entries/diagnostic_entry_interface.h"

namespace qorai_ads {

class OptedInToNotificationAdsDiagnosticEntry final
    : public DiagnosticEntryInterface {
 public:
  // DiagnosticEntryInterface:
  DiagnosticEntryType GetType() const override;
  std::string GetName() const override;
  std::string GetValue() const override;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DIAGNOSTICS_ENTRIES_OPTED_INTO_NOTIFICATION_ADS_DIAGNOSTIC_ENTRY_H_
