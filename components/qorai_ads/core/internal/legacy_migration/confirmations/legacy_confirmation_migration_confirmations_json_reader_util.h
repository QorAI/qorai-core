/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_CONFIRMATIONS_JSON_READER_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_CONFIRMATIONS_JSON_READER_UTIL_H_

#include <optional>

#include "base/values.h"
#include "qorai/components/qorai_ads/core/internal/account/confirmations/confirmation_info.h"

namespace qorai_ads::json::reader {

std::optional<ConfirmationList> ParseConfirmations(
    const base::Value::Dict& dict);

}  // namespace qorai_ads::json::reader

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_CONFIRMATIONS_JSON_READER_UTIL_H_
