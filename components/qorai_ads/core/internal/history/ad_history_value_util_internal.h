/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_VALUE_UTIL_INTERNAL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_VALUE_UTIL_INTERNAL_H_

#include "base/values.h"

namespace qorai_ads {

struct AdHistoryItemInfo;

void ParseCreatedAt(const base::Value::Dict& dict,
                    AdHistoryItemInfo& ad_history_item);

void ParseAdContent(const base::Value::Dict& dict,
                    AdHistoryItemInfo& ad_history_item);

void ParseSegmentContent(const base::Value::Dict& dict,
                         AdHistoryItemInfo& ad_history_item);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_VALUE_UTIL_INTERNAL_H_
