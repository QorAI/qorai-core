/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/permission_rule_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsPermissionRuleFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kPermissionRulesFeature));
}

TEST(QoraiAdsPermissionRuleFeatureTest, ShouldOnlyServeAdsInWindowedMode) {
  // Act & Assert
  EXPECT_TRUE(kShouldOnlyServeAdsInWindowedMode.Get());
}

TEST(QoraiAdsPermissionRuleFeatureTest,
     ShouldOnlyServeAdsWithValidInternetConnection) {
  // Act & Assert
  EXPECT_TRUE(kShouldOnlyServeAdsWithValidInternetConnection.Get());
}

TEST(QoraiAdsPermissionRuleFeatureTest, ShouldOnlyServeAdsIfMediaIsNotPlaying) {
  // Act & Assert
  EXPECT_TRUE(kShouldOnlyServeAdsIfMediaIsNotPlaying.Get());
}

TEST(QoraiAdsPermissionRuleFeatureTest, ShouldOnlyServeAdsIfBrowserIsActive) {
  // Act & Assert
  EXPECT_TRUE(kShouldOnlyServeAdsIfBrowserIsActive.Get());
}

TEST(QoraiAdsPermissionRuleFeatureTest, DoNotDisturbFromHour) {
  // Act & Assert
  EXPECT_EQ(21, kDoNotDisturbFromHour.Get());
}

TEST(QoraiAdsPermissionRuleFeatureTest, DoNotDisturbToHour) {
  // Act & Assert
  EXPECT_EQ(6, kDoNotDisturbToHour.Get());
}

}  // namespace qorai_ads
