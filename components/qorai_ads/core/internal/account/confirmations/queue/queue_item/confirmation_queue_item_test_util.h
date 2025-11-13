/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_CONFIRMATION_QUEUE_ITEM_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_CONFIRMATION_QUEUE_ITEM_TEST_UTIL_H_

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_info.h"

namespace qorai_ads {

struct ConfirmationInfo;

namespace test {

ConfirmationQueueItemList BuildConfirmationQueueItems(
    const ConfirmationInfo& confirmation,
    size_t count);

void SaveConfirmationQueueItems(
    const ConfirmationQueueItemList& confirmation_queue_items);

void BuildAndSaveConfirmationQueueItems(const ConfirmationInfo& confirmation,
                                        size_t count);

}  // namespace test

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_CONFIRMATION_QUEUE_ITEM_TEST_UTIL_H_
