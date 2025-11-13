/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/pacing/pacing.h"

#include <vector>

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/creatives/notification_ads/creative_notification_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/pacing/pacing_random_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

namespace {

std::vector<double> GetPacingRandomNumbers() {
  return {0.0, 0.5, 0.99};
}

}  // namespace

class QoraiAdsPacingTest : public test::TestBase {};
TEST_F(QoraiAdsPacingTest, PaceCreativeAdsWithMinPassThroughRate) {
  // Arrange
  CreativeNotificationAdList creative_ads;
  CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  creative_ad.pass_through_rate = 0.0;
  creative_ads.push_back(creative_ad);

  // Act & Assert
  for (const double random_number : GetPacingRandomNumbers()) {
    const ScopedPacingRandomNumberSetterForTesting scoped_setter(random_number);
    PaceCreativeAds(creative_ads);
    EXPECT_THAT(creative_ads, ::testing::IsEmpty());
  }
}

TEST_F(QoraiAdsPacingTest, DoNotPaceCreativeAdsWithMaxPassThroughRate) {
  // Arrange
  CreativeNotificationAdList creative_ads;
  CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  creative_ad.pass_through_rate = 1.0;
  creative_ads.push_back(creative_ad);

  // Act & Assert
  const CreativeNotificationAdList expected_creative_ads = {creative_ad};
  for (const double random_number : GetPacingRandomNumbers()) {
    const ScopedPacingRandomNumberSetterForTesting scoped_setter(random_number);
    PaceCreativeAds(creative_ads);
    EXPECT_EQ(expected_creative_ads, creative_ads);
  }
}

TEST_F(QoraiAdsPacingTest,
       PaceCreativeAdIfPacingIsGreaterThanOrEqualToPassThroughRate) {
  // Arrange
  CreativeNotificationAdList creative_ads;
  CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  creative_ad.pass_through_rate = 0.5;
  creative_ads.push_back(creative_ad);

  const ScopedPacingRandomNumberSetterForTesting scoped_setter(0.7);

  // Act
  PaceCreativeAds(creative_ads);

  // Assert
  EXPECT_THAT(creative_ads, ::testing::IsEmpty());
}

TEST_F(QoraiAdsPacingTest,
       DoNotPaceCreativeAdWhenPacingIsLessThanPassThroughRate) {
  // Arrange
  CreativeNotificationAdList creative_ads;

  CreativeNotificationAdInfo creative_ad_1 =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  creative_ad_1.pass_through_rate = 0.1;
  creative_ads.push_back(creative_ad_1);

  CreativeNotificationAdInfo creative_ad_2 =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  creative_ad_2.pass_through_rate = 0.5;
  creative_ads.push_back(creative_ad_2);

  const ScopedPacingRandomNumberSetterForTesting scoped_setter(0.3);

  // Act
  PaceCreativeAds(creative_ads);

  // Assert
  const CreativeNotificationAdList expected_creative_ads = {creative_ad_2};
  EXPECT_EQ(expected_creative_ads, creative_ads);
}

}  // namespace qorai_ads
