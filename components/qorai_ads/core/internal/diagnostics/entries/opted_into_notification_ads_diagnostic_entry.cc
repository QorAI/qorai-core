/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/diagnostics/entries/opted_into_notification_ads_diagnostic_entry.h"

#include "qorai/components/qorai_ads/core/internal/common/strings/string_conversions_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings.h"

namespace qorai_ads {

namespace {
constexpr char kName[] = "Opted into notification ads";
}  // namespace

DiagnosticEntryType OptedInToNotificationAdsDiagnosticEntry::GetType() const {
  return DiagnosticEntryType::kOptedInToNotificationAds;
}

std::string OptedInToNotificationAdsDiagnosticEntry::GetName() const {
  return kName;
}

std::string OptedInToNotificationAdsDiagnosticEntry::GetValue() const {
  return BoolToString(UserHasOptedInToNotificationAds());
}

}  // namespace qorai_ads
