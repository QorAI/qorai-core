/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_MANAGER_OBSERVER_MOCK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_MANAGER_OBSERVER_MOCK_H_

#include "qorai/components/qorai_ads/core/internal/history/ad_history_manager_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_ads {

struct AdHistoryItemInfo;

class AdHistoryManagerObserverMock : public AdHistoryManagerObserver {
 public:
  AdHistoryManagerObserverMock();

  AdHistoryManagerObserverMock(const AdHistoryManagerObserverMock&) = delete;
  AdHistoryManagerObserverMock& operator=(const AdHistoryManagerObserverMock&) =
      delete;

  ~AdHistoryManagerObserverMock() override;

  MOCK_METHOD(void, OnDidAddAdHistoryItem, (const AdHistoryItemInfo&));
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_MANAGER_OBSERVER_MOCK_H_
