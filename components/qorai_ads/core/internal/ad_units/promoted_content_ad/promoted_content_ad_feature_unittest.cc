/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/ad_units/promoted_content_ad/promoted_content_ad_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsPromotedContentAdFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kPromotedContentAdFeature));
}

TEST(QoraiAdsPromotedContentAdFeatureTest, MaximumPromotedContentAdsPerHour) {
  // Act & Assert
  EXPECT_EQ(4U, kMaximumPromotedContentAdsPerHour.Get());
}

TEST(QoraiAdsPromotedContentAdFeatureTest, MaximumPromotedContentAdsPerDay) {
  // Act & Assert
  EXPECT_EQ(20U, kMaximumPromotedContentAdsPerDay.Get());
}

}  // namespace qorai_ads
