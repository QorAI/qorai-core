/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_CONFIRMATION_QUEUE_ITEM_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_CONFIRMATION_QUEUE_ITEM_INFO_H_

#include <optional>
#include <vector>

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/account/confirmations/confirmation_info.h"

namespace qorai_ads {

struct ConfirmationQueueItemInfo final {
  ConfirmationQueueItemInfo();

  ConfirmationQueueItemInfo(const ConfirmationQueueItemInfo&);
  ConfirmationQueueItemInfo& operator=(const ConfirmationQueueItemInfo&);

  ConfirmationQueueItemInfo(ConfirmationQueueItemInfo&&) noexcept;
  ConfirmationQueueItemInfo& operator=(ConfirmationQueueItemInfo&&) noexcept;

  ~ConfirmationQueueItemInfo();

  bool operator==(const ConfirmationQueueItemInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  ConfirmationInfo confirmation;
  std::optional<base::Time> process_at;
  int retry_count = 0;
};

using ConfirmationQueueItemList = std::vector<ConfirmationQueueItemInfo>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_QUEUE_ITEM_CONFIRMATION_QUEUE_ITEM_INFO_H_
