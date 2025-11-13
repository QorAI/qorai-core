/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_ADS_OBSERVER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_ADS_OBSERVER_H_

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

class AdsObserver {
 public:
  virtual ~AdsObserver() = default;

  // Invoked when ad rewards have changed.
  virtual void OnAdRewardsDidChange() = 0;

  // Invoked when a browser upgrade is required to serve ads.
  virtual void OnBrowserUpgradeRequiredToServeAds() = 0;

  // Invoked when a wallet is deemed ineligible to serve ads.
  virtual void OnIneligibleWalletToServeAds() = 0;

  // Invoked to remind the user of what to do and what not to do.
  virtual void OnRemindUser(mojom::ReminderType mojom_reminder_type) = 0;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_ADS_OBSERVER_H_
