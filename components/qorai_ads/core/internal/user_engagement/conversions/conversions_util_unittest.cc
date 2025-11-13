/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversions_util.h"

#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/ad_info.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsConversionsUtilTest : public test::TestBase {};

TEST_F(QoraiAdsConversionsUtilTest, IsAllowedToConvertInlineContentAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kInlineContentAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_TRUE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest,
       IsNotAllowedToConvertInlineContentAdEventIfOptedOutOfQoraiNewsAds) {
  // Arrange
  test::OptOutOfQoraiNewsAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kInlineContentAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_FALSE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest,
       IsAllowedToConvertInlineContentAdEventForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kInlineContentAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_TRUE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest, IsAllowedToConvertPromotedContentAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kPromotedContentAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_TRUE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest,
       IsNotAllowedToConvertPromotedContentAdEventIfOptedOutOfQoraiNewsAds) {
  // Arrange
  test::OptOutOfQoraiNewsAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kPromotedContentAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_FALSE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest,
       IsAllowedToConvertPromotedContentAdEventForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kPromotedContentAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_TRUE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest, IsAllowedToConvertNewTabPageAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kNewTabPageAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_TRUE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest,
       IsNotAllowedToConvertNewTabPageAdEventIfOptedOutOfNewTabPageAds) {
  // Arrange
  test::OptOutOfNewTabPageAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kNewTabPageAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_FALSE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest,
       IsNotAllowedToConvertNewTabPageAdEventForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kNewTabPageAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_FALSE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest, IsAllowedToConvertNotificationAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_TRUE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest,
       IsNotAllowedToConvertNotificationAdEventIfOptedOutOfNotificationAds) {
  // Arrange
  test::OptOutOfNotificationAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_FALSE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest,
       IsNotAllowedToConvertNotificationAdEventForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_FALSE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest, IsAllowedToConvertSearchResultAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_TRUE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest,
       IsNotAllowedToConvertSearchResultAdEventIfOptedOutOfSearchResultAds) {
  // Arrange
  test::OptOutOfSearchResultAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_FALSE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest,
       IsAllowedToConvertSearchResultAdEventForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kClicked,
                   /*created_at=*/test::Now());

  // Act & Assert
  EXPECT_TRUE(IsAllowedToConvertAdEvent(ad_event));
}

TEST_F(QoraiAdsConversionsUtilTest, DidAdEventOccurWithinObservationWindow) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_TRUE(DidAdEventOccurWithinObservationWindow(
      ad_event, /*observation_window=*/base::Days(1)));
}

TEST_F(QoraiAdsConversionsUtilTest, DidAdEventOccurOutsideObservationWindow) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());

  AdvanceClockBy(base::Days(1) + base::Milliseconds(1));

  // Act & Assert
  EXPECT_FALSE(DidAdEventOccurWithinObservationWindow(
      ad_event, /*observation_window=*/base::Days(1)));
}

}  // namespace qorai_ads
