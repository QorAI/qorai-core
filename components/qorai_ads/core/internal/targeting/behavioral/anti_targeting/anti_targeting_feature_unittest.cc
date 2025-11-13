/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/anti_targeting/anti_targeting_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsAntiTargetingFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kAntiTargetingFeature));
}

TEST(QoraiAdsAntiTargetingFeatureTest, AntiTargetingResourceVersion) {
  // Act & Assert
  EXPECT_EQ(1, kAntiTargetingResourceVersion.Get());
}

}  // namespace qorai_ads
