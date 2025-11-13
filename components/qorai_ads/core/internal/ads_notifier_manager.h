/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ADS_NOTIFIER_MANAGER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ADS_NOTIFIER_MANAGER_H_

#include <memory>
#include <vector>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

class AdsObserver;

class AdsNotifierManager final {
 public:
  AdsNotifierManager();

  AdsNotifierManager(const AdsNotifierManager& other) = delete;
  AdsNotifierManager& operator=(const AdsNotifierManager& other) = delete;

  ~AdsNotifierManager();

  static AdsNotifierManager& GetInstance();

  void AddObserver(std::unique_ptr<AdsObserver> ads_observer);

  void NotifyAdRewardsDidChange() const;

  void NotifyBrowserUpgradeRequiredToServeAds() const;

  void NotifyIneligibleWalletToServeAds() const;

  void NotifyRemindUser(mojom::ReminderType mojom_reminder_type) const;

 private:
  std::vector<std::unique_ptr<AdsObserver>> observers_;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ADS_NOTIFIER_MANAGER_H_
