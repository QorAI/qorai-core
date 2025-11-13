/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/notification_ad_serving_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsNotificationAdServingUtilTest : public test::TestBase {};

TEST_F(QoraiAdsNotificationAdServingUtilTest,
       ShouldServeAdsAtRegularIntervalsOnIOS) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kIOS);

  // Act & Assert
  EXPECT_TRUE(ShouldServeAdsAtRegularIntervals());
}

TEST_F(QoraiAdsNotificationAdServingUtilTest,
       ShouldServeAdsAtRegularIntervalsOnAndroid) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kAndroid);

  // Act & Assert
  EXPECT_TRUE(ShouldServeAdsAtRegularIntervals());
}

TEST_F(QoraiAdsNotificationAdServingUtilTest,
       ShouldNotServeAdsAtRegularIntervalsOnMacOS) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kMacOS);

  // Act & Assert
  EXPECT_FALSE(ShouldServeAdsAtRegularIntervals());
}

TEST_F(QoraiAdsNotificationAdServingUtilTest,
       ShouldNotServeAdsAtRegularIntervalsOnWindows) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kWindows);

  // Act & Assert
  EXPECT_FALSE(ShouldServeAdsAtRegularIntervals());
}

TEST_F(QoraiAdsNotificationAdServingUtilTest,
       ShouldNotServeAdsAtRegularIntervalsOnLinux) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kLinux);

  // Act & Assert
  EXPECT_FALSE(ShouldServeAdsAtRegularIntervals());
}

TEST_F(QoraiAdsNotificationAdServingUtilTest, SetServeAdAt) {
  // Act
  SetServeAdAt(test::DistantFuture());

  // Assert
  EXPECT_EQ(test::DistantFuture(), ServeAdAt());
}

TEST_F(QoraiAdsNotificationAdServingUtilTest,
       CalculateDelayBeforeServingTheFirstAd) {
  // Act & Assert
  EXPECT_EQ(base::Minutes(2), CalculateDelayBeforeServingAnAd());
}

TEST_F(QoraiAdsNotificationAdServingUtilTest,
       CalculateDelayBeforeServingAPastDueAd) {
  // Arrange
  SetServeAdAt(test::DistantPast());

  // Act & Assert
  EXPECT_EQ(base::Minutes(1), CalculateDelayBeforeServingAnAd());
}

TEST_F(QoraiAdsNotificationAdServingUtilTest, CalculateDelayBeforeServingAnAd) {
  // Arrange
  SetServeAdAt(test::DistantFuture());

  // Act & Assert
  EXPECT_EQ(test::DistantFuture() - test::Now(),
            CalculateDelayBeforeServingAnAd());
}

TEST_F(QoraiAdsNotificationAdServingUtilTest,
       CalculateMinimumDelayBeforeServingAnAd) {
  // Arrange
  SetServeAdAt(test::Now());

  AdvanceClockBy(base::Milliseconds(1));

  // Act & Assert
  EXPECT_EQ(base::Minutes(1), CalculateDelayBeforeServingAnAd());
}

}  // namespace qorai_ads
