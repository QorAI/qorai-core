/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/total_max_exclusion_rule.h"

#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/creative_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_builder_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsTotalMaxExclusionRuleTest : public test::TestBase {};

TEST_F(QoraiAdsTotalMaxExclusionRuleTest, ShouldIncludeIfThereAreNoAdEvents) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;
  creative_ad.total_max = 2;

  const TotalMaxExclusionRule exclusion_rule(/*ad_events=*/{});

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsTotalMaxExclusionRuleTest, ShouldIncludeIfZero) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;
  creative_ad.total_max = 0;

  const TotalMaxExclusionRule exclusion_rule(/*ad_events=*/{});

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsTotalMaxExclusionRuleTest, ShouldIncludeIfDoesNotExceedCap) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;
  creative_ad.total_max = 2;

  AdEventList ad_events;
  const AdEventInfo ad_event = test::BuildAdEvent(
      creative_ad, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kServedImpression,
      /*created_at=*/test::Now(), /*should_generate_random_uuids=*/true);
  ad_events.push_back(ad_event);

  const TotalMaxExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsTotalMaxExclusionRuleTest,
       ShouldIncludeIfDoesNotExceedCapForNoMatchingCreatives) {
  // Arrange
  CreativeAdInfo creative_ad_1;
  creative_ad_1.creative_set_id = test::kCreativeSetId;
  creative_ad_1.total_max = 2;

  CreativeAdInfo creative_ad_2;
  creative_ad_2.creative_set_id = test::kAnotherCreativeSetId;

  AdEventList ad_events;
  const AdEventInfo ad_event = test::BuildAdEvent(
      creative_ad_2, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kServedImpression, /*created_at=*/test::Now(),
      /*should_generate_random_uuids=*/true);
  ad_events.push_back(ad_event);
  ad_events.push_back(ad_event);

  const TotalMaxExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad_1));
}

TEST_F(QoraiAdsTotalMaxExclusionRuleTest, ShouldExcludeIfExceedsCap) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;
  creative_ad.total_max = 2;

  AdEventList ad_events;
  const AdEventInfo ad_event = test::BuildAdEvent(
      creative_ad, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kServedImpression,
      /*created_at=*/test::Now(), /*should_generate_random_uuids=*/true);
  ad_events.push_back(ad_event);
  ad_events.push_back(ad_event);

  const TotalMaxExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_FALSE(exclusion_rule.ShouldInclude(creative_ad));
}

}  // namespace qorai_ads
