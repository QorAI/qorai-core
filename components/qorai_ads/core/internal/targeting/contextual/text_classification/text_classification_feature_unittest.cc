/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/targeting/contextual/text_classification/text_classification_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsTextClassificationFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kTextClassificationFeature));
}

TEST(QoraiAdsTextClassificationFeatureTest, TextClassificationResourceVersion) {
  // Act & Assert
  EXPECT_EQ(1, kTextClassificationResourceVersion.Get());
}

TEST(QoraiAdsTextClassificationFeatureTest,
     TextClassificationPageProbabilitiesHistorySize) {
  // Act & Assert
  EXPECT_EQ(15U, kTextClassificationPageProbabilitiesHistorySize.Get());
}

}  // namespace qorai_ads
