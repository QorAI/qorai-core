/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/diagnostics/entries/last_unidle_time_diagnostic_entry.h"

#include "qorai/components/qorai_ads/core/internal/common/time/time_formatting_util.h"

namespace qorai_ads {

namespace {

constexpr char kName[] = "Last unidle time";
constexpr char kNever[] = "Never";

}  // namespace
LastUnIdleTimeDiagnosticEntry::LastUnIdleTimeDiagnosticEntry(
    base::Time last_unidle_at) {
  last_unidle_at_ = last_unidle_at;
}

DiagnosticEntryType LastUnIdleTimeDiagnosticEntry::GetType() const {
  return DiagnosticEntryType::kLastUnIdleTime;
}

std::string LastUnIdleTimeDiagnosticEntry::GetName() const {
  return kName;
}

std::string LastUnIdleTimeDiagnosticEntry::GetValue() const {
  if (!last_unidle_at_) {
    return kNever;
  }

  return LongFriendlyDateAndTime(*last_unidle_at_,
                                 /*use_sentence_style=*/false);
}

}  // namespace qorai_ads
