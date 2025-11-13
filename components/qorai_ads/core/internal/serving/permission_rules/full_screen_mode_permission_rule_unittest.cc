/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/full_screen_mode_permission_rule.h"

#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/permission_rule_feature.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsFullScreenModePermissionRuleTest : public test::TestBase {};

TEST_F(QoraiAdsFullScreenModePermissionRuleTest, ShouldAllow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  EXPECT_TRUE(HasFullScreenModePermission());
}

TEST_F(QoraiAdsFullScreenModePermissionRuleTest, ShouldAlwaysAllowOnAndroid) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kAndroid);

  test::MockIsBrowserInFullScreenMode(ads_client_mock_, true);

  // Act & Assert
  EXPECT_TRUE(HasFullScreenModePermission());
}

TEST_F(QoraiAdsFullScreenModePermissionRuleTest, ShouldAlwaysAllowOnIOS) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  test::MockPlatformHelper(platform_helper_mock_, PlatformType::kIOS);

  test::MockIsBrowserInFullScreenMode(ads_client_mock_, true);

  // Act & Assert
  EXPECT_TRUE(HasFullScreenModePermission());
}

TEST_F(QoraiAdsFullScreenModePermissionRuleTest, ShouldNotAllow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  test::MockIsBrowserInFullScreenMode(ads_client_mock_, true);

  // Act & Assert
  EXPECT_FALSE(HasFullScreenModePermission());
}

TEST_F(QoraiAdsFullScreenModePermissionRuleTest,
       ShouldAllowIfPermissionRuleIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kPermissionRulesFeature,
      {{"should_only_serve_ads_in_windowed_mode", "false"}});

  test::MockIsBrowserInFullScreenMode(ads_client_mock_, true);

  // Act & Assert
  EXPECT_TRUE(HasFullScreenModePermission());
}

}  // namespace qorai_ads
