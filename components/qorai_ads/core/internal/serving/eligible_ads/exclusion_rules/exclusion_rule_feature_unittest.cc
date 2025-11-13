/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsExclusionRuleFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kExclusionRulesFeature));
}

TEST(QoraiAdsExclusionRuleFeatureTest,
     ShouldExcludeAdIfDismissedWithinTimeWindow) {
  // Act & Assert
  EXPECT_EQ(base::Hours(0), kShouldExcludeAdIfDismissedWithinTimeWindow.Get());
}

TEST(QoraiAdsExclusionRuleFeatureTest,
     ShouldExcludeAdIfLandedOnPageWithinTimeWindow) {
  // Act & Assert
  EXPECT_EQ(base::Hours(0),
            kShouldExcludeAdIfLandedOnPageWithinTimeWindow.Get());
}

TEST(QoraiAdsExclusionRuleFeatureTest,
     ShouldExcludeAdIfCreativeInstanceExceedsPerHourCap) {
  // Act & Assert
  EXPECT_EQ(1U, kShouldExcludeAdIfCreativeInstanceExceedsPerHourCap.Get());
}

TEST(QoraiAdsExclusionRuleFeatureTest,
     ShouldExcludeAdIfCreativeSetExceedsConversionCap) {
  // Act & Assert
  EXPECT_EQ(0U, kShouldExcludeAdIfCreativeSetExceedsConversionCap.Get());
}

}  // namespace qorai_ads
