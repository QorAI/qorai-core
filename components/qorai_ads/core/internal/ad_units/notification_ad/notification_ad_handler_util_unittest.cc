/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/ad_units/notification_ad/notification_ad_handler_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsNotificationAdUtilTest : public test::TestBase {};

TEST_F(QoraiAdsNotificationAdUtilTest, CanServeIfUserIsActive) {
  // Act & Assert
  EXPECT_TRUE(CanServeIfUserIsActive());
}

TEST_F(QoraiAdsNotificationAdUtilTest, CannotServeIfUserIsActive) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kAndroid);

  // Act & Assert
  EXPECT_FALSE(CanServeIfUserIsActive());
}

TEST_F(QoraiAdsNotificationAdUtilTest, ShouldServe) {
  // Act & Assert
  EXPECT_TRUE(ShouldServe());
}

TEST_F(QoraiAdsNotificationAdUtilTest,
       ShouldNotServeIfOptedOutOfNotificationAds) {
  // Arrange
  test::OptOutOfNotificationAds();

  // Act & Assert
  EXPECT_FALSE(ShouldServe());
}

TEST_F(QoraiAdsNotificationAdUtilTest, CanServeAtRegularIntervals) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kAndroid);

  // Act & Assert
  EXPECT_TRUE(CanServeAtRegularIntervals());
}

TEST_F(QoraiAdsNotificationAdUtilTest, CannotServeAtRegularIntervals) {
  // Act & Assert
  EXPECT_FALSE(CanServeAtRegularIntervals());
}

}  // namespace qorai_ads
