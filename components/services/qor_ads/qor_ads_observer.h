/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SERVICES_QOR_ADS_QOR_ADS_OBSERVER_H_
#define QORAI_COMPONENTS_SERVICES_QOR_ADS_QOR_ADS_OBSERVER_H_

#include "qorai/components/qorai_ads/core/public/ads_observer.h"
#include "qorai/components/services/qor_ads/public/interfaces/qor_ads.mojom.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/remote.h"

namespace qor_ads {

class QorAdsObserver : public qorai_ads::AdsObserver {
 public:
  explicit QorAdsObserver(mojo::PendingRemote<mojom::QorAdsObserver>
                              qor_ads_observer_pending_remote);

  QorAdsObserver(const QorAdsObserver&);
  QorAdsObserver& operator=(const QorAdsObserver&);

  QorAdsObserver(QorAdsObserver&&) noexcept;
  QorAdsObserver& operator=(QorAdsObserver&&) noexcept;

  ~QorAdsObserver() override;

  void OnAdRewardsDidChange() override;

  void OnBrowserUpgradeRequiredToServeAds() override;

  void OnIneligibleWalletToServeAds() override;

  void OnRemindUser(
      qorai_ads::mojom::ReminderType mojom_reminder_type) override;

 private:
  mojo::Remote<mojom::QorAdsObserver> qor_ads_observer_remote_;
};

}  // namespace qor_ads

#endif  // QORAI_COMPONENTS_SERVICES_QOR_ADS_QOR_ADS_OBSERVER_H_
