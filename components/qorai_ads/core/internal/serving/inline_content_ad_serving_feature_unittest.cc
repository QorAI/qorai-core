/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/inline_content_ad_serving_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsInlineContentAdServingFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kInlineContentAdServingFeature));
}

TEST(QoraiAdsInlineContentAdServingFeatureTest, InlineContentAdServingVersion) {
  // Act & Assert
  EXPECT_EQ(2, kInlineContentAdServingVersion.Get());
}

}  // namespace qorai_ads
