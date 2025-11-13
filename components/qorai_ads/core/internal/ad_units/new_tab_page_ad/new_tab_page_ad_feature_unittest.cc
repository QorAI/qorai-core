/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsNewTabPageAdFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kNewTabPageAdFeature));
}

TEST(QoraiAdsNewTabPageAdFeatureTest,
     ShouldFrequencyCapNewTabPageAdsForNonRewards) {
  // Act & Assert
  EXPECT_TRUE(kShouldFrequencyCapNewTabPageAdsForNonRewards.Get());
}

TEST(QoraiAdsNewTabPageAdFeatureTest, MaximumNewTabPageAdsPerHour) {
  // Act & Assert
  EXPECT_EQ(4U, kMaximumNewTabPageAdsPerHour.Get());
}

TEST(QoraiAdsNewTabPageAdFeatureTest, MaximumNewTabPageAdsPerDay) {
  // Act & Assert
  EXPECT_EQ(20U, kMaximumNewTabPageAdsPerDay.Get());
}

TEST(QoraiAdsNewTabPageAdFeatureTest, NewTabPageAdMinimumWaitTime) {
  // Act & Assert
  EXPECT_EQ(base::Minutes(1), kNewTabPageAdMinimumWaitTime.Get());
}

}  // namespace qorai_ads
