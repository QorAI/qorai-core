/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/daypart_exclusion_rule_util.h"

#include "qorai/components/qorai_ads/core/internal/creatives/creative_daypart_info.h"
#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/daypart_exclusion_rule_test_util.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsDaypartExclusionRuleUtilTest, MatchDayOfWeek) {
  // Arrange
  CreativeDaypartInfo daypart;
  daypart.days_of_week = "0123456";

  // Act & Assert
  EXPECT_TRUE(MatchDayOfWeek(daypart, /*wednesday*/ 3));
}

TEST(QoraiAdsDaypartExclusionRuleUtilTest, DoNotMatchDayOfWeek) {
  // Arrange
  CreativeDaypartInfo daypart;
  daypart.days_of_week = "012456";

  // Act & Assert
  EXPECT_FALSE(MatchDayOfWeek(daypart, /*wednesday*/ 3));
}

TEST(QoraiAdsDaypartExclusionRuleUtilTest, MatchTimeSlot) {
  // Arrange
  CreativeDaypartInfo daypart;
  daypart.start_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/0, /*minutes=*/0);
  daypart.end_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/23, /*minutes=*/59);

  // Act & Assert
  EXPECT_TRUE(MatchTimeSlot(daypart, test::ConvertHoursAndMinutesToTotalMinutes(
                                         /*hours=*/5, /*minutes=*/35)));
}

TEST(QoraiAdsDaypartExclusionRuleUtilTest, MatchExactTimeSlot) {
  // Arrange
  CreativeDaypartInfo daypart;
  daypart.start_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/5, /*minutes=*/35);
  daypart.end_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/5, /*minutes=*/35);

  // Act & Assert
  EXPECT_TRUE(MatchTimeSlot(daypart, test::ConvertHoursAndMinutesToTotalMinutes(
                                         /*hours=*/5, /*minutes=*/35)));
}

TEST(QoraiAdsDaypartExclusionRuleUtilTest, DoNotMatchTimeSlotAfterEndMinute) {
  // Arrange
  CreativeDaypartInfo daypart;
  daypart.start_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/0, /*minutes=*/0);
  daypart.end_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/5, /*minutes=*/34);

  // Act & Assert
  EXPECT_FALSE(MatchTimeSlot(
      daypart,
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/5, /*minutes=*/35)));
}

TEST(QoraiAdsDaypartExclusionRuleUtilTest,
     DoNotMatchTimeSlotBeforeStartMinute) {
  // Arrange
  CreativeDaypartInfo daypart;
  daypart.start_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/5, /*minutes=*/36);
  daypart.end_minute =
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/23, /*minutes=*/59);

  // Act & Assert
  EXPECT_FALSE(MatchTimeSlot(
      daypart,
      test::ConvertHoursAndMinutesToTotalMinutes(/*hours=*/5, /*minutes=*/35)));
}

}  // namespace qorai_ads
