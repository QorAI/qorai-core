/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/services/qor_ads/qor_ads_observer.h"

#include <utility>
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-shared.h"

namespace qor_ads {

QorAdsObserver::QorAdsObserver(mojo::PendingRemote<mojom::QorAdsObserver>
                                   qor_ads_observer_pending_remote) {
  qor_ads_observer_remote_.Bind(std::move(qor_ads_observer_pending_remote));
}

QorAdsObserver::~QorAdsObserver() = default;

void QorAdsObserver::OnAdRewardsDidChange() {
  qor_ads_observer_remote_->OnAdRewardsDidChange();
}

void QorAdsObserver::OnBrowserUpgradeRequiredToServeAds() {
  qor_ads_observer_remote_->OnBrowserUpgradeRequiredToServeAds();
}

void QorAdsObserver::OnIneligibleWalletToServeAds() {
  qor_ads_observer_remote_->OnIneligibleWalletToServeAds();
}

void QorAdsObserver::OnRemindUser(
    qorai_ads::mojom::ReminderType mojom_reminder_type) {
  qor_ads_observer_remote_->OnRemindUser(mojom_reminder_type);
}

}  // namespace qor_ads
