/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/marked_as_inappropriate_exclusion_rule.h"

#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/ads_core/ads_core_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/creatives/creative_ad_info.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsMarkedAsInappropriateExclusionRuleTest : public test::TestBase {
 protected:
  const MarkedAsInappropriateExclusionRule exclusion_rule_;
};

TEST_F(QoraiAdsMarkedAsInappropriateExclusionRuleTest, ShouldInclude) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(QoraiAdsMarkedAsInappropriateExclusionRuleTest, ShouldExclude) {
  // Arrange
  GetReactions().MarkedAdsAsInappropriateForTesting() = {test::kCreativeSetId};

  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

}  // namespace qorai_ads
