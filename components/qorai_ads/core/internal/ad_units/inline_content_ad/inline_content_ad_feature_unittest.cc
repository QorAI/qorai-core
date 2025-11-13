/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/ad_units/inline_content_ad/inline_content_ad_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsInlineContentAdFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kInlineContentAdFeature));
}

TEST(QoraiAdsInlineContentAdFeatureTest, MaximumInlineContentAdsPerHour) {
  // Act & Assert
  EXPECT_EQ(6U, kMaximumInlineContentAdsPerHour.Get());
}

TEST(QoraiAdsInlineContentAdFeatureTest, MaximumInlineContentAdsPerDay) {
  // Act & Assert
  EXPECT_EQ(20U, kMaximumInlineContentAdsPerDay.Get());
}

}  // namespace qorai_ads
