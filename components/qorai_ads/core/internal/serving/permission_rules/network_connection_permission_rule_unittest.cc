/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/network_connection_permission_rule.h"

#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/permission_rule_feature.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsNetworkConnectionPermissionRuleTest : public test::TestBase {};

TEST_F(QoraiAdsNetworkConnectionPermissionRuleTest, ShouldAllow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  // Act & Assert
  EXPECT_TRUE(HasNetworkConnectionPermission());
}

TEST_F(QoraiAdsNetworkConnectionPermissionRuleTest, ShouldNotAllow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  test::MockIsNetworkConnectionAvailable(ads_client_mock_, false);

  // Act & Assert
  EXPECT_FALSE(HasNetworkConnectionPermission());
}

TEST_F(QoraiAdsNetworkConnectionPermissionRuleTest,
       ShouldAllowIfPermissionRuleIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kPermissionRulesFeature,
      {{"should_only_serve_ads_with_valid_internet_connection", "false"}});

  test::MockIsNetworkConnectionAvailable(ads_client_mock_, false);

  // Act & Assert
  EXPECT_TRUE(HasNetworkConnectionPermission());
}

}  // namespace qorai_ads
