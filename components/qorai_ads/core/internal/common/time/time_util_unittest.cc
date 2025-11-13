/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/time/time_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsTimeUtilTest : public test::TestBase,
                             public ::testing::WithParamInterface<bool> {};

TEST_F(QoraiAdsTimeUtilTest, LocalTimeInMinutesSinceMidnight) {
  // Arrange
  const base::Time time = test::TimeFromString("November 18 2020 12:34:56");

  // Act & Assert
  EXPECT_EQ((12 * base::Time::kMinutesPerHour) + 34,
            LocalTimeInMinutesSinceMidnight(time));
}

TEST_F(QoraiAdsTimeUtilTest, LocalTimeAtBeginningOfPreviousMonth) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("November 18 2020 12:34:56.789",
                                      /*should_adjust_for_dst=*/true));

  // Act & Assert
  const base::Time expected_time =
      test::TimeFromString("October 1 2020 00:00:00.000",
                           /*should_adjust_for_dst=*/true);
  EXPECT_EQ(expected_time, LocalTimeAtBeginningOfPreviousMonth());
}

TEST_F(QoraiAdsTimeUtilTest, LocalTimeAtBeginningOfPreviousMonthOnTheCusp) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("January 1 2020 00:00:00.000",
                                      /*should_adjust_for_dst=*/true));

  // Act & Assert
  const base::Time expected_time =
      test::TimeFromString("December 1 2019 00:00:00.000",
                           /*should_adjust_for_dst=*/true);
  EXPECT_EQ(expected_time, LocalTimeAtBeginningOfPreviousMonth());
}

TEST_F(QoraiAdsTimeUtilTest, LocalTimeAtEndOfPreviousMonth) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("November 18 2020 12:34:56.789",
                                      /*should_adjust_for_dst=*/true));

  // Act & Assert
  const base::Time expected_time =
      test::TimeFromString("October 31 2020 23:59:59.999",
                           /*should_adjust_for_dst=*/true);
  EXPECT_EQ(expected_time, LocalTimeAtEndOfPreviousMonth());
}

TEST_F(QoraiAdsTimeUtilTest, LocalTimeAtEndOfPreviousMonthOnTheCusp) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("January 1 2020 00:00:00.000",
                                      /*should_adjust_for_dst=*/true));

  // Act & Assert
  const base::Time expected_time =
      test::TimeFromString("December 31 2019 23:59:59.999",
                           /*should_adjust_for_dst=*/true);
  EXPECT_EQ(expected_time, LocalTimeAtEndOfPreviousMonth());
}

TEST_F(QoraiAdsTimeUtilTest, LocalTimeAtBeginningOfThisMonth) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("November 18 2020 12:34:56.789",
                                      /*should_adjust_for_dst=*/true));

  // Act & Assert
  const base::Time expected_time =
      test::TimeFromString("November 1 2020 00:00:00.000",
                           /*should_adjust_for_dst=*/true);
  EXPECT_EQ(expected_time, LocalTimeAtBeginningOfThisMonth());
}

TEST_F(QoraiAdsTimeUtilTest, LocalTimeAtEndOfThisMonth) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("November 18 2020 12:34:56.789",
                                      /*should_adjust_for_dst=*/true));

  // Act & Assert
  const base::Time expected_time =
      test::TimeFromString("November 30 2020 23:59:59.999",
                           /*should_adjust_for_dst=*/true);
  EXPECT_EQ(expected_time, LocalTimeAtEndOfThisMonth());
}

TEST_F(QoraiAdsTimeUtilTest, TimeToPrivacyPreservingIso8601) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("November 18 2020 23:45:12.345"));

  // Act & Assert
  EXPECT_EQ("2020-11-18T23:00:00.000Z",
            TimeToPrivacyPreservingIso8601(test::Now()));
}

}  // namespace qorai_ads
