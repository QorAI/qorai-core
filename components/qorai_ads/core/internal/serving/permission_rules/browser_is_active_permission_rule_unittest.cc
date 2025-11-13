/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/browser_is_active_permission_rule.h"

#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/permission_rule_feature.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsBrowserIsActivePermissionRuleTest : public test::TestBase {};

TEST_F(QoraiAdsBrowserIsActivePermissionRuleTest, ShouldAllow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  NotifyBrowserDidBecomeActive();
  NotifyBrowserDidEnterForeground();

  // Act & Assert
  EXPECT_TRUE(HasBrowserIsActivePermission());
}

TEST_F(QoraiAdsBrowserIsActivePermissionRuleTest, ShouldNotAllow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  NotifyBrowserDidResignActive();
  NotifyBrowserDidEnterBackground();

  // Act & Assert
  EXPECT_FALSE(HasBrowserIsActivePermission());
}

TEST_F(QoraiAdsBrowserIsActivePermissionRuleTest,
       ShouldAllowIfPermissionRuleIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kPermissionRulesFeature,
      {{"should_only_serve_ads_if_browser_is_active", "false"}});

  NotifyBrowserDidResignActive();
  NotifyBrowserDidEnterBackground();

  // Act & Assert
  EXPECT_TRUE(HasBrowserIsActivePermission());
}

TEST_F(QoraiAdsBrowserIsActivePermissionRuleTest,
       ShouldNotAllowIfWindowIsActiveAndBrowserIsBackgrounded) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  NotifyBrowserDidBecomeActive();
  NotifyBrowserDidEnterBackground();

  // Act & Assert
  EXPECT_FALSE(HasBrowserIsActivePermission());
}

TEST_F(QoraiAdsBrowserIsActivePermissionRuleTest,
       ShouldNotAllowIfWindowIsInactiveAndBrowserIsForegrounded) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  NotifyBrowserDidResignActive();
  NotifyBrowserDidEnterForeground();

  // Act & Assert
  EXPECT_FALSE(HasBrowserIsActivePermission());
}

TEST_F(QoraiAdsBrowserIsActivePermissionRuleTest,
       ShouldNotAllowIfWindowIsInactiveAndBrowserIsBackgrounded) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  NotifyBrowserDidResignActive();
  NotifyBrowserDidEnterBackground();

  // Act & Assert
  EXPECT_FALSE(HasBrowserIsActivePermission());
}

}  // namespace qorai_ads
