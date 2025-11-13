/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/notification_ad_serving_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsNotificationAdServingFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kNotificationAdServingFeature));
}

TEST(QoraiAdsNotificationAdServingFeatureTest, NotificationAdServingVersion) {
  // Act & Assert
  EXPECT_EQ(2, kNotificationAdServingVersion.Get());
}

TEST(QoraiAdsNotificationAdServingFeatureTest, ServeFirstNotificationAdAfter) {
  // Act & Assert
  EXPECT_EQ(base::Minutes(2), kServeFirstNotificationAdAfter.Get());
}

TEST(QoraiAdsNotificationAdServingFeatureTest,
     MinimumDelayBeforeServingNotificationAd) {
  // Act & Assert
  EXPECT_EQ(base::Minutes(1), kMinimumDelayBeforeServingNotificationAd.Get());
}

TEST(QoraiAdsNotificationAdServingFeatureTest,
     RetryServingNotificationAdAfter) {
  // Act & Assert
  EXPECT_EQ(base::Minutes(2), kRetryServingNotificationAdAfter.Get());
}

}  // namespace qorai_ads
