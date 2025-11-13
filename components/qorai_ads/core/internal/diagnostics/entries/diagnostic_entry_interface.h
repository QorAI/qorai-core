/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DIAGNOSTICS_ENTRIES_DIAGNOSTIC_ENTRY_INTERFACE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DIAGNOSTICS_ENTRIES_DIAGNOSTIC_ENTRY_INTERFACE_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/diagnostics/diagnostic_entry_types.h"

namespace qorai_ads {

class DiagnosticEntryInterface {
 public:
  virtual ~DiagnosticEntryInterface() = default;

  // Returns the type of the diagnostic entry, which categorizes the entry for
  // diagnostic purposes.
  virtual DiagnosticEntryType GetType() const = 0;

  // Returns the name of the diagnostic entry, providing a human-readable
  // identifier for this entry.
  virtual std::string GetName() const = 0;

  // Returns the value associated with this diagnostic entry, representing
  // relevant diagnostic data.
  virtual std::string GetValue() const = 0;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DIAGNOSTICS_ENTRIES_DIAGNOSTIC_ENTRY_INTERFACE_H_
