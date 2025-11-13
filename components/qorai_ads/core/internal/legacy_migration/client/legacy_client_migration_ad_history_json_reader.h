/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CLIENT_LEGACY_CLIENT_MIGRATION_AD_HISTORY_JSON_READER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CLIENT_LEGACY_CLIENT_MIGRATION_AD_HISTORY_JSON_READER_H_

#include <optional>
#include <string>

#include "qorai/components/qorai_ads/core/public/history/ad_history_item_info.h"

namespace qorai_ads::json::reader {

std::optional<AdHistoryList> ReadAdHistory(const std::string& json);

}  // namespace qorai_ads::json::reader

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CLIENT_LEGACY_CLIENT_MIGRATION_AD_HISTORY_JSON_READER_H_
