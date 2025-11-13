/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/history/ad_history_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsAdHistoryFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kAdHistoryFeature));
}

TEST(QoraiAdsAdHistoryFeatureTest, AdHistoryRetentionPeriod) {
  // Act & Assert
  EXPECT_EQ(base::Days(30), kAdHistoryRetentionPeriod.Get());
}

}  // namespace qorai_ads
