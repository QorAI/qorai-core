/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_handler_util.h"

#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_feature.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/ad_info.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsAdEventHandlerUtilTest : public test::TestBase {};

TEST_F(QoraiAdsAdEventHandlerUtilTest, HasFiredAdEvent) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_TRUE(HasFiredAdEvent(ad, ad_events,
                              mojom::ConfirmationType::kServedImpression));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest, HasNeverFiredAdEvent) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_FALSE(HasFiredAdEvent(ad, ad_events,
                               mojom::ConfirmationType::kViewedImpression));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest, HasFiredAdEventWithinTimeWindow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_TRUE(HasFiredAdEventWithinTimeWindow(
      ad, ad_events, mojom::ConfirmationType::kServedImpression,
      /*time_window=*/base::Seconds(5)));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest, HasNeverFiredAdEventWithinTimeWindow) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  AdvanceClockBy(base::Seconds(5));

  // Act & Assert
  EXPECT_FALSE(HasFiredAdEventWithinTimeWindow(
      ad, ad_events, mojom::ConfirmationType::kViewedImpression,
      /*time_window=*/base::Seconds(5)));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest, WasAdServed) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_TRUE(WasAdServed(ad, ad_events,
                          mojom::InlineContentAdEventType::kViewedImpression));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest, WasAdServedIfNoPreviousEvents) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  // Act & Assert
  EXPECT_TRUE(WasAdServed(ad, /*ad_events=*/{},
                          mojom::InlineContentAdEventType::kServedImpression));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest, WasAdNeverServed) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kAdEventFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  // Act & Assert
  EXPECT_FALSE(WasAdServed(ad, /*ad_events=*/{},
                           mojom::InlineContentAdEventType::kViewedImpression));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest,
       ShouldDeduplicateViewedAdEventWithinTimeWindow) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_viewed_ad_event_for", "5s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event_1 =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_1);
  const AdEventInfo ad_event_2 =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_2);

  AdvanceClockBy(kDeduplicateViewedAdEventFor.Get());

  // Act & Assert
  EXPECT_TRUE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::InlineContentAdEventType::kViewedImpression));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest,
       ShouldNotDeduplicateViewedAdEventOutOfTimeWindow) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_viewed_ad_event_for", "5s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event_1 =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_1);
  const AdEventInfo ad_event_2 =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_2);

  AdvanceClockBy(kDeduplicateViewedAdEventFor.Get() + base::Seconds(1));

  // Act & Assert
  EXPECT_FALSE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::InlineContentAdEventType::kViewedImpression));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest, ShouldAlwaysDeduplicateViewedAdEvent) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_viewed_ad_event_for", "0s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event_1 =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_1);
  const AdEventInfo ad_event_2 =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_2);

  AdvanceClockTo(test::DistantFuture());

  // Act & Assert
  EXPECT_TRUE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::InlineContentAdEventType::kViewedImpression));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest,
       ShouldNotDeduplicateViewedAdEventIfAdWasNeverViewed) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_viewed_ad_event_for", "5s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_FALSE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::InlineContentAdEventType::kViewedImpression));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest,
       ShouldDeduplicateClickedAdEventWithinTimeWindow) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_clicked_ad_event_for", "5s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event_1 =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_1);
  const AdEventInfo ad_event_2 =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_2);
  const AdEventInfo ad_event_3 = BuildAdEvent(
      ad, mojom::ConfirmationType::kClicked, /*created_at=*/test::Now());
  ad_events.push_back(ad_event_3);

  AdvanceClockBy(kDeduplicateClickedAdEventFor.Get());

  // Act & Assert
  EXPECT_TRUE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::InlineContentAdEventType::kClicked));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest,
       ShouldNotDeduplicateClickedAdEventOutOfTimeWindow) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_clicked_ad_event_for", "5s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event_1 =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_1);
  const AdEventInfo ad_event_2 =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_2);
  const AdEventInfo ad_event_3 = BuildAdEvent(
      ad, mojom::ConfirmationType::kClicked, /*created_at=*/test::Now());
  ad_events.push_back(ad_event_3);

  AdvanceClockBy(kDeduplicateClickedAdEventFor.Get() + base::Seconds(1));

  // Act & Assert
  EXPECT_FALSE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::InlineContentAdEventType::kClicked));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest, ShouldAlwaysDeduplicateClickedAdEvent) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_clicked_ad_event_for", "0s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event_1 =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_1);
  const AdEventInfo ad_event_2 =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_2);
  const AdEventInfo ad_event_3 = BuildAdEvent(
      ad, mojom::ConfirmationType::kClicked, /*created_at=*/test::Now());
  ad_events.push_back(ad_event_3);

  AdvanceClockTo(test::DistantFuture());

  // Act & Assert
  EXPECT_TRUE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::InlineContentAdEventType::kClicked));
}

TEST_F(QoraiAdsAdEventHandlerUtilTest,
       ShouldNotDeduplicateClickedAdEventIfAdWasNeverClicked) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kAdEventFeature, {{"deduplicate_clicked_ad_event_for", "5s"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event_1 =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_1);
  const AdEventInfo ad_event_2 =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_2);

  // Act & Assert
  EXPECT_FALSE(ShouldDeduplicateAdEvent(
      ad, ad_events, mojom::InlineContentAdEventType::kClicked));
}

}  // namespace qorai_ads
