/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_REMINDERS_REMINDERS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_REMINDERS_REMINDERS_H_

#include <optional>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/timer/timer.h"
#include "qorai/components/qorai_ads/core/internal/history/ad_history_manager_observer.h"
#include "qorai/components/qorai_ads/core/public/history/ad_history_item_info.h"

namespace qorai_ads {

class Reminders final : public AdHistoryManagerObserver {
 public:
  Reminders();

  Reminders(const Reminders&) = delete;
  Reminders& operator=(const Reminders&) = delete;

  ~Reminders() override;

 private:
  void MaybeShowReminders(const AdHistoryItemInfo& ad_history_item);

  bool CanShowUserClickTheSameAdMultipleTimesReminder(
      const AdHistoryItemInfo& ad_history_item);
  void MaybeShowUserClickTheSameAdMultipleTimesReminderAfterDelay(
      const AdHistoryItemInfo& ad_history_item);
  void MaybeShowUserClickTheSameAdMultipleTimesReminder(
      const AdHistoryItemInfo& ad_history_item);
  void MaybeShowUserClickTheSameAdMultipleTimesReminderCallback(
      const std::string& creative_instance_id,
      std::optional<AdHistoryList> ad_history);

  // AdHistoryManagerObserver:
  void OnDidAddAdHistoryItem(const AdHistoryItemInfo& ad_history_item) override;

  base::OneShotTimer timer_;

  base::WeakPtrFactory<Reminders> weak_factory_{this};
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_REMINDERS_REMINDERS_H_
