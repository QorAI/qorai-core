/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ADS_OBSERVER_MOCK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ADS_OBSERVER_MOCK_H_

#include "qorai/components/qorai_ads/core/public/ads_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_ads {

class AdsObserverMock : public AdsObserver {
 public:
  AdsObserverMock();

  AdsObserverMock(const AdsObserverMock&) = delete;
  AdsObserverMock& operator=(const AdsObserverMock&) = delete;

  ~AdsObserverMock() override;

  MOCK_METHOD(void, OnAdRewardsDidChange, ());

  MOCK_METHOD(void, OnBrowserUpgradeRequiredToServeAds, ());

  MOCK_METHOD(void, OnIneligibleWalletToServeAds, ());

  MOCK_METHOD(void, OnRemindUser, (mojom::ReminderType));
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ADS_OBSERVER_MOCK_H_
