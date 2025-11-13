/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/user_engagement/site_visit/site_visit_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsSiteVisitFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kSiteVisitFeature));
}

TEST(QoraiAdsSiteVisitFeatureTest, PageLandAfter) {
  // Act & Assert
  EXPECT_EQ(base::Seconds(5), kPageLandAfter.Get());
}

TEST(QoraiAdsSiteVisitFeatureTest, PageLandCap) {
  // Act & Assert
  EXPECT_EQ(0U, kPageLandCap.Get());
}

TEST(QoraiAdsSiteVisitFeatureTest, ShouldSuspendAndResumePageLand) {
  // Act & Assert
  EXPECT_TRUE(kShouldSuspendAndResumePageLand.Get());
}

}  // namespace qorai_ads
