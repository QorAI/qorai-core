/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_MANAGER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_MANAGER_H_

#include <memory>

#include "qorai/components/qorai_ads/core/internal/diagnostics/diagnostic_alias.h"
#include "qorai/components/qorai_ads/core/public/ads_callback.h"

namespace qorai_ads {

class DiagnosticManager final {
 public:
  DiagnosticManager();

  DiagnosticManager(const DiagnosticManager&) = delete;
  DiagnosticManager& operator=(const DiagnosticManager&) = delete;

  ~DiagnosticManager();

  static DiagnosticManager& GetInstance();

  void SetEntry(std::unique_ptr<DiagnosticEntryInterface> entry);

  void GetDiagnostics(GetDiagnosticsCallback callback) const;

 private:
  DiagnosticMap diagnostics_;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_MANAGER_H_
