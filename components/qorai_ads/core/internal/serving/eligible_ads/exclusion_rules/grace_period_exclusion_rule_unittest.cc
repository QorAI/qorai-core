/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/grace_period_exclusion_rule.h"

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/common/test/local_state_pref_value_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/creatives/creative_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/global_state/global_state.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_builder_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

namespace {
constexpr base::TimeDelta kGracePeriod = base::Days(3);
}  // namespace

class QoraiAdsGracePeriodExclusionRuleTest : public test::TestBase {
 protected:
  void SetUpMocks() override {
    test::SetLocalStateTimePrefValue(prefs::kFirstRunAt, base::Time::Now());
    test::SetProfileTimeDeltaPrefValue(prefs::kGracePeriod, kGracePeriod);
  }

  const GracePeriodExclusionRule exclusion_rule_;
};

TEST_F(QoraiAdsGracePeriodExclusionRuleTest,
       ShouldIncludeIfWithinGracePeriodWhenDebugIsEnabled) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->Flags().should_debug = true;

  FastForwardClockBy(kGracePeriod - base::Milliseconds(1));

  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kDisabled;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsGracePeriodExclusionRuleTest,
       ShouldIncludeIfOutsideGracePeriodWhenDebugIsEnabled) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->Flags().should_debug = true;

  FastForwardClockBy(kGracePeriod);

  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kDisabled;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsGracePeriodExclusionRuleTest,
       ShouldIncludeIfWithinGracePeriodForDisabledMetrics) {
  // Arrange
  FastForwardClockBy(kGracePeriod - base::Milliseconds(1));

  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kDisabled;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsGracePeriodExclusionRuleTest,
       ShouldIncludeIfOutsideGracePeriodForDisabledMetrics) {
  // Arrange
  FastForwardClockBy(kGracePeriod);

  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kDisabled;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsGracePeriodExclusionRuleTest,
       ShouldExcludeIfWithinGracePeriodForConfirmationMetrics) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kConfirmation;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsGracePeriodExclusionRuleTest,
       ShouldExcludeIfWithinGracePeriodOnTheCuspForConfirmationMetrics) {
  // Arrange
  FastForwardClockBy(kGracePeriod - base::Milliseconds(1));

  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kConfirmation;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsGracePeriodExclusionRuleTest,
       ShouldIncludeIfOutsideGracePeriodForConfirmationMetrics) {
  // Arrange
  FastForwardClockBy(kGracePeriod);

  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kConfirmation;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

}  // namespace qorai_ads
