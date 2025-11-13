/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/ads_per_day_permission_rule.h"

#include <vector>

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsAdsPerDayPermissionRuleTest : public test::TestBase {};

TEST_F(QoraiAdsAdsPerDayPermissionRuleTest, ShouldAllowIfNoHistory) {
  // Arrange
  const std::vector<base::Time> history;

  // Act & Assert
  EXPECT_TRUE(HasAdsPerDayPermission(history, /*cap=*/1));
}

TEST_F(QoraiAdsAdsPerDayPermissionRuleTest, ShouldAllowIfDoesNotExceedCap) {
  // Arrange
  const std::vector<base::Time> history = {test::Now()};

  // Act & Assert
  EXPECT_TRUE(HasAdsPerDayPermission(history, /*cap=*/2));
}

TEST_F(QoraiAdsAdsPerDayPermissionRuleTest,
       ShouldAllowIfDoesNotExceedCapAfter1Day) {
  // Arrange
  const std::vector<base::Time> history = {test::Now()};

  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_TRUE(HasAdsPerDayPermission(history, /*cap=*/1));
}

TEST_F(QoraiAdsAdsPerDayPermissionRuleTest,
       ShouldNotAllowIfExceedsCapWithin1Day) {
  // Arrange
  const std::vector<base::Time> history = {test::Now()};

  AdvanceClockBy(base::Days(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_FALSE(HasAdsPerDayPermission(history, /*cap=*/1));
}

}  // namespace qorai_ads
