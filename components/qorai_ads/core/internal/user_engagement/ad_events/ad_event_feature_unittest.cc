/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsAdEventFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kAdEventFeature));
}

TEST(QoraiAdsAdEventFeatureTest, DeduplicateViewedAdEventFor) {
  // Act & Assert
  EXPECT_EQ(base::Seconds(0), kDeduplicateViewedAdEventFor.Get());
}

TEST(QoraiAdsAdEventFeatureTest, DeduplicateClickedAdEventFor) {
  // Act & Assert
  EXPECT_EQ(base::Seconds(1), kDeduplicateClickedAdEventFor.Get());
}

}  // namespace qorai_ads
