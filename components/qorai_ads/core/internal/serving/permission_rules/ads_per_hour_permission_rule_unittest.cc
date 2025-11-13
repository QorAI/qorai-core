/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/ads_per_hour_permission_rule.h"

#include <vector>

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsAdsPerHourPermissionRuleTest : public test::TestBase {};

TEST_F(QoraiAdsAdsPerHourPermissionRuleTest, ShouldAllowIfNoHistory) {
  // Arrange
  const std::vector<base::Time> history;

  // Act & Assert
  EXPECT_TRUE(HasAdsPerHourPermission(history, /*cap=*/1));
}

TEST_F(QoraiAdsAdsPerHourPermissionRuleTest, ShouldAllowIfDoesNotExceedCap) {
  // Arrange
  const std::vector<base::Time> history = {test::Now()};

  // Act & Assert
  EXPECT_TRUE(HasAdsPerHourPermission(history, /*cap=*/2));
}

TEST_F(QoraiAdsAdsPerHourPermissionRuleTest,
       ShouldAllowIfDoesNotExceedCapAfter1Hour) {
  // Arrange
  const std::vector<base::Time> history = {test::Now()};

  AdvanceClockBy(base::Hours(1));

  // Act & Assert
  EXPECT_TRUE(HasAdsPerHourPermission(history, /*cap=*/1));
}

TEST_F(QoraiAdsAdsPerHourPermissionRuleTest,
       ShouldNotAllowIfExceedsCapWithin1Hour) {
  // Arrange
  const std::vector<base::Time> history = {test::Now()};

  AdvanceClockBy(base::Hours(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_FALSE(HasAdsPerHourPermission(history, /*cap=*/1));
}

}  // namespace qorai_ads
