/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/notification_ads/can_show_notifications_permission_rule.h"

#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsCanShowNotificationsPermissionRuleTest : public test::TestBase {};

TEST_F(QoraiAdsCanShowNotificationsPermissionRuleTest, ShouldAllow) {
  // Act & Assert
  EXPECT_TRUE(HasCanShowNotificationsPermission());
}

TEST_F(QoraiAdsCanShowNotificationsPermissionRuleTest, ShouldNotAllow) {
  // Arrange
  test::MockCanShowNotificationAds(ads_client_mock_, false);

  // Act & Assert
  EXPECT_FALSE(HasCanShowNotificationsPermission());
}

}  // namespace qorai_ads
