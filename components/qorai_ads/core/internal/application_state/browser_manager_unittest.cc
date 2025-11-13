/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/application_state/browser_manager.h"

#include "qorai/components/qorai_ads/core/internal/application_state/browser_manager_observer_mock.h"
#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsBrowserManagerTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    BrowserManager::GetInstance().AddObserver(&browser_manager_observer_mock_);
  }

  void TearDown() override {
    BrowserManager::GetInstance().RemoveObserver(
        &browser_manager_observer_mock_);

    test::TestBase::TearDown();
  }

  BrowserManagerObserverMock browser_manager_observer_mock_;
};

TEST_F(QoraiAdsBrowserManagerTest, OnNotifyBrowserDidBecomeActive) {
  // Arrange
  EXPECT_CALL(browser_manager_observer_mock_, OnBrowserDidBecomeActive);

  // Act
  NotifyBrowserDidBecomeActive();

  // Assert
  EXPECT_TRUE(BrowserManager::GetInstance().IsActive());
}

TEST_F(QoraiAdsBrowserManagerTest, OnNotifyBrowserDidResignActive) {
  // Arrange
  NotifyBrowserDidBecomeActive();

  EXPECT_CALL(browser_manager_observer_mock_, OnBrowserDidResignActive);

  // Act
  NotifyBrowserDidResignActive();

  // Assert
  EXPECT_FALSE(BrowserManager::GetInstance().IsActive());
}

TEST_F(QoraiAdsBrowserManagerTest, OnNotifyBrowserDidEnterForeground) {
  // Arrange
  EXPECT_CALL(browser_manager_observer_mock_, OnBrowserDidEnterForeground);

  // Act
  NotifyBrowserDidEnterForeground();

  // Assert
  EXPECT_TRUE(BrowserManager::GetInstance().IsInForeground());
}

TEST_F(QoraiAdsBrowserManagerTest, OnNotifyBrowserDidEnterBackground) {
  // Arrange
  NotifyBrowserDidEnterForeground();

  EXPECT_CALL(browser_manager_observer_mock_, OnBrowserDidEnterBackground);

  // Act
  NotifyBrowserDidEnterBackground();

  // Assert
  EXPECT_FALSE(BrowserManager::GetInstance().IsInForeground());
}

TEST_F(QoraiAdsBrowserManagerTest,
       OnNotifyDidInitializeAdsWhenBrowserIsActive) {
  // Act
  NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(BrowserManager::GetInstance().IsInForeground());
}

TEST_F(QoraiAdsBrowserManagerTest,
       OnNotifyDidInitializeAdsWhenBrowserIsInactive) {
  // Arrange
  test::MockIsBrowserActive(ads_client_mock_, false);

  // Act
  NotifyDidInitializeAds();

  // Assert
  EXPECT_FALSE(BrowserManager::GetInstance().IsInForeground());
}

}  // namespace qorai_ads
