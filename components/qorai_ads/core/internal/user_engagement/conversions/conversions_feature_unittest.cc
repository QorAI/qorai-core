/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversions_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsConversionsFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kConversionsFeature));
}

TEST(QoraiAdsConversionsFeatureTest, ConversionResourceVersion) {
  // Act & Assert
  EXPECT_EQ(1, kConversionResourceVersion.Get());
}

TEST(QoraiAdsConversionsFeatureTest, HtmlMetaTagConversionIdPattern) {
  // Act & Assert
  EXPECT_EQ(R"~(<meta.*name="ad-conversion-id".*content="([-a-zA-Z0-9]*)".*>)~",
            kHtmlMetaTagConversionIdPattern.Get());
}

}  // namespace qorai_ads
