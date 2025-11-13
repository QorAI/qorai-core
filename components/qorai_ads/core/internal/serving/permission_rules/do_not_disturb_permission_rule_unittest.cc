/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/do_not_disturb_permission_rule.h"

#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsDoNotDisturbPermissionRuleTest : public test::TestBase {};

TEST_F(QoraiAdsDoNotDisturbPermissionRuleTest,
       ShouldAllowWhileBrowserIsInactiveBetween6amAnd9pmOnAndroid) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kAndroid);

  NotifyBrowserDidResignActive();
  NotifyBrowserDidEnterBackground();

  AdvanceClockToLocalMidnight();

  // Act & Assert
  {
    // Verify 5:59 AM
    AdvanceClockBy(base::Hours(5) + base::Minutes(59));
    EXPECT_FALSE(HasDoNotDisturbPermission());
  }

  {
    // Verify 6:00 AM
    AdvanceClockBy(base::Minutes(1));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 8:59 PM
    AdvanceClockBy(base::Hours(14) + base::Minutes(59));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 9:00 PM
    AdvanceClockBy(base::Minutes(1));
    EXPECT_FALSE(HasDoNotDisturbPermission());
  }
}

TEST_F(QoraiAdsDoNotDisturbPermissionRuleTest,
       ShouldAllowWhileBrowserIsActiveOnAndroid) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kAndroid);

  NotifyBrowserDidBecomeActive();
  NotifyBrowserDidEnterForeground();

  AdvanceClockToLocalMidnight();

  // Act & Assert
  {
    // Verify 5:59 AM
    AdvanceClockBy(base::Hours(5) + base::Minutes(59));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 6:00 AM
    AdvanceClockBy(base::Minutes(1));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 8:59 PM
    AdvanceClockBy(base::Hours(14) + base::Minutes(59));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 9:00 PM
    AdvanceClockBy(base::Minutes(1));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }
}

TEST_F(QoraiAdsDoNotDisturbPermissionRuleTest, ShouldAlwaysAllowOnIOS) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kIOS);

  NotifyBrowserDidBecomeActive();
  NotifyBrowserDidEnterForeground();

  AdvanceClockToLocalMidnight();

  // Act & Assert
  {
    // Verify 00:00 AM
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 12:00 PM
    AdvanceClockBy(base::Hours(12));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }
}

TEST_F(QoraiAdsDoNotDisturbPermissionRuleTest, ShouldAlwaysAllowOnMacOS) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kMacOS);

  NotifyBrowserDidBecomeActive();
  NotifyBrowserDidEnterForeground();

  AdvanceClockToLocalMidnight();

  // Act & Assert
  {
    // Verify 00:00 AM
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 12:00 PM
    AdvanceClockBy(base::Hours(12));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }
}

TEST_F(QoraiAdsDoNotDisturbPermissionRuleTest, ShouldAlwaysAllowOnWindows) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kWindows);

  NotifyBrowserDidBecomeActive();
  NotifyBrowserDidEnterForeground();

  AdvanceClockToLocalMidnight();

  // Act & Assert
  {
    // Verify 00:00 AM
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 12:00 PM
    AdvanceClockBy(base::Hours(12));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }
}

TEST_F(QoraiAdsDoNotDisturbPermissionRuleTest, ShouldAlwaysAllowOnLinux) {
  // Arrange
  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kLinux);

  NotifyBrowserDidBecomeActive();
  NotifyBrowserDidEnterForeground();

  AdvanceClockToLocalMidnight();

  // Act & Assert
  {
    // Verify 00:00 AM
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }

  {
    // Verify 12:00 PM
    AdvanceClockBy(base::Hours(12));
    EXPECT_TRUE(HasDoNotDisturbPermission());
  }
}

}  // namespace qorai_ads
