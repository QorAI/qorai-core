/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/ad_units/notification_ad/notification_ad_info.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/creatives/notification_ads/creative_notification_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/notification_ads/notification_ad_builder.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsNotificationAdInfoTest : public test::TestBase {};

TEST_F(QoraiAdsNotificationAdInfoTest, IsValid) {
  // Arrange
  const CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  const NotificationAdInfo ad = BuildNotificationAd(creative_ad);

  // Act & Assert
  EXPECT_TRUE(ad.IsValid());
}

TEST_F(QoraiAdsNotificationAdInfoTest, IsInvalid) {
  // Arrange
  const NotificationAdInfo ad;

  // Act & Assert
  EXPECT_FALSE(ad.IsValid());
}

}  // namespace qorai_ads
