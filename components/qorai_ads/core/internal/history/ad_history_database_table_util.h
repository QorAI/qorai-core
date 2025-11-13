/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_DATABASE_TABLE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_DATABASE_TABLE_UTIL_H_

#include "qorai/components/qorai_ads/core/public/history/ad_history_item_info.h"

namespace qorai_ads::database {

void PurgeExpiredAdHistory();

void SaveAdHistory(const AdHistoryList& ad_history);

}  // namespace qorai_ads::database

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_DATABASE_TABLE_UTIL_H_
