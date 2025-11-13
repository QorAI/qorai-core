/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/user_attention/user_idle_detection/user_idle_detection_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsUserIdleDetectionFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kUserIdleDetectionFeature));
}

TEST(QoraiAdsUserIdleDetectionFeatureTest, UserIdleDetectionThreshold) {
  // Act & Assert
  EXPECT_EQ(base::Seconds(5), kUserIdleDetectionThreshold.Get());
}

TEST(QoraiAdsUserIdleDetectionFeatureTest, MaximumUserIdleDetectionTime) {
  // Act & Assert
  EXPECT_EQ(base::Seconds(0), kMaximumUserIdleDetectionTime.Get());
}

TEST(QoraiAdsUserIdleDetectionFeatureTest, ShouldDetectScreenWasLocked) {
  // Act & Assert
  EXPECT_FALSE(kShouldDetectScreenWasLocked.Get());
}

}  // namespace qorai_ads
