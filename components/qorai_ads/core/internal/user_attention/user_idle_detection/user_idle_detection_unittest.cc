/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsUserIdleDetectionTest : public test::TestBase {};

TEST_F(QoraiAdsUserIdleDetectionTest, RewardsUserDidBecomeActive) {
  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log).Times(::testing::AnyNumber());
  EXPECT_CALL(ads_client_mock_, Log(::testing::_, ::testing::_, ::testing::_,
                                    "User is active after 10 s"));
  NotifyUserDidBecomeActive(/*idle_time=*/base::Seconds(10),
                            /*screen_was_locked=*/false);
}

TEST_F(QoraiAdsUserIdleDetectionTest, NonRewardsUserDidBecomeActive) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log).Times(0);
  NotifyUserDidBecomeActive(/*idle_time=*/base::Seconds(10),
                            /*screen_was_locked=*/false);
}

TEST_F(QoraiAdsUserIdleDetectionTest,
       RewardsUserDidBecomeActiveWhileScreenWasLocked) {
  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log).Times(::testing::AnyNumber());
  EXPECT_CALL(ads_client_mock_, Log(::testing::_, ::testing::_, ::testing::_,
                                    "User is active after 10 s"));
  EXPECT_CALL(ads_client_mock_,
              Log(::testing::_, ::testing::_, ::testing::_,
                  "Screen was locked before the user become active"));
  NotifyUserDidBecomeActive(/*idle_time=*/base::Seconds(10),
                            /*screen_was_locked=*/true);
}

TEST_F(QoraiAdsUserIdleDetectionTest,
       NonRewardsUserDidBecomeActiveWhileScreenWasLocked) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log).Times(0);
  NotifyUserDidBecomeActive(/*idle_time=*/base::Seconds(10),
                            /*screen_was_locked=*/true);
}

TEST_F(QoraiAdsUserIdleDetectionTest, RewardsUserDidBecomeIdle) {
  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log);
  NotifyUserDidBecomeIdle();
}

TEST_F(QoraiAdsUserIdleDetectionTest, NonRewardsUserDidBecomeIdle) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log).Times(0);
  NotifyUserDidBecomeIdle();
}

}  // namespace qorai_ads
