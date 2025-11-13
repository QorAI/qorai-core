/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_MANAGER_OBSERVER_MOCK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_MANAGER_OBSERVER_MOCK_H_

#include "qorai/components/qorai_ads/core/internal/application_state/browser_manager_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace qorai_ads {

class BrowserManagerObserverMock : public BrowserManagerObserver {
 public:
  BrowserManagerObserverMock();

  BrowserManagerObserverMock(const BrowserManagerObserverMock&) = delete;
  BrowserManagerObserverMock& operator=(const BrowserManagerObserverMock&) =
      delete;

  ~BrowserManagerObserverMock() override;

  MOCK_METHOD(void, OnBrowserDidBecomeActive, ());
  MOCK_METHOD(void, OnBrowserDidResignActive, ());

  MOCK_METHOD(void, OnBrowserDidEnterForeground, ());
  MOCK_METHOD(void, OnBrowserDidEnterBackground, ());
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_MANAGER_OBSERVER_MOCK_H_
