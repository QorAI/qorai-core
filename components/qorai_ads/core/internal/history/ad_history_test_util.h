/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_TEST_UTIL_H_

#include <vector>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"
#include "qorai/components/qorai_ads/core/public/history/ad_history_item_info.h"

namespace qorai_ads::test {

AdHistoryItemInfo BuildAdHistoryItem(
    mojom::AdType mojom_ad_type,
    mojom::ConfirmationType mojom_confirmation_type,
    bool should_generate_random_uuids);

AdHistoryList BuildAdHistory(
    mojom::AdType mojom_ad_type,
    const std::vector<mojom::ConfirmationType>& mojom_confirmation_types,
    bool should_generate_random_uuids);

AdHistoryList BuildAdHistoryForSamePlacement(
    mojom::AdType mojom_ad_type,
    const std::vector<mojom::ConfirmationType>& mojom_confirmation_types,
    bool should_generate_random_uuids);

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_TEST_UTIL_H_
