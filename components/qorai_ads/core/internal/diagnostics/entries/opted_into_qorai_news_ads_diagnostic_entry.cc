/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/diagnostics/entries/opted_into_qorai_news_ads_diagnostic_entry.h"

#include "qorai/components/qorai_ads/core/internal/common/strings/string_conversions_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings.h"

namespace qorai_ads {

namespace {
constexpr char kName[] = "Opted into Qorai News ads";
}  // namespace

DiagnosticEntryType OptedInToQoraiNewsAdsDiagnosticEntry::GetType() const {
  return DiagnosticEntryType::kOptedInToQoraiNewsAds;
}

std::string OptedInToQoraiNewsAdsDiagnosticEntry::GetName() const {
  return kName;
}

std::string OptedInToQoraiNewsAdsDiagnosticEntry::GetValue() const {
  return BoolToString(UserHasOptedInToQoraiNewsAds());
}

}  // namespace qorai_ads
