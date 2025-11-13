/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/issuers_permission_rule.h"

#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsIssuersPermissionRuleTest : public test::TestBase {};

TEST_F(QoraiAdsIssuersPermissionRuleTest, ShouldAllowForRewardsUser) {
  // Arrange
  test::BuildAndSetIssuers();

  // Act & Assert
  EXPECT_TRUE(HasIssuersPermission());
}

TEST_F(QoraiAdsIssuersPermissionRuleTest, ShouldAlwaysAllowForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_TRUE(HasIssuersPermission());
}

TEST_F(QoraiAdsIssuersPermissionRuleTest, ShouldNotAllowIfNoIssuers) {
  // Act & Assert
  EXPECT_FALSE(HasIssuersPermission());
}

}  // namespace qorai_ads
