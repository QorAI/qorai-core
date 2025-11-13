/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/eligible_ads_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsEligibleAdFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kEligibleAdFeature));
}

TEST(QoraiAdsEligibleAdFeatureTest, SiteHistoryMaxCount) {
  // Act & Assert
  EXPECT_EQ(5'000, kSiteHistoryMaxCount.Get());
}

TEST(QoraiAdsEligibleAdFeatureTest, SiteHistoryRecentDayRange) {
  // Act & Assert
  EXPECT_EQ(180, kSiteHistoryRecentDayRange.Get());
}

}  // namespace qorai_ads
