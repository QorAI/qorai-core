/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/calendar/calendar_util.h"

#include "base/compiler_specific.h"
#include "base/time/time.h"  // IWYU pragma: keep
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsCalendarUtilTest, IsLeapYear) {
  // Act & Assert
  for (int year = 2000; year < 2050; ++year) {
    EXPECT_EQ(year % 4 == 0, IsLeapYear(year));
  }
}

TEST(QoraiAdsCalendarUtilTest, LocalDayOfWeek) {
  // Act & Assert
  EXPECT_EQ(/*wednesday*/ 3, DayOfWeek(test::TimeFromString("18 November 1970"),
                                       /*is_local*/ true));
}

TEST(QoraiAdsCalendarUtilTest, UTCDayOfWeek) {
  // Act & Assert
  EXPECT_EQ(/*monday*/ 1, DayOfWeek(test::TimeFromUTCString("18 November 1991"),
                                    /*is_local*/ false));
}

TEST(QoraiAdsCalendarUtilTest, DaysInMonth) {
  // Arrange
  constexpr int kLastDayInMonth[12] = {31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31};

  // Act & Assert
  for (size_t i = 0; i < 12; ++i) {
    EXPECT_EQ(UNSAFE_TODO(kLastDayInMonth[i]),
              DaysInMonth(/*year=*/2021, /*month=*/i + 1));
  }
}

TEST(QoraiAdsCalendarUtilTest, DaysInMonthForLeapYear) {
  // Arrange
  constexpr int kDaysInMonth[12] = {31, 29, 31, 30, 31, 30,
                                    31, 31, 30, 31, 30, 31};

  // Act & Assert
  for (size_t i = 0; i < 12; ++i) {
    EXPECT_EQ(UNSAFE_TODO(kDaysInMonth[i]),
              DaysInMonth(/*year=*/2020, /*month=*/i + 1));
  }
}

}  // namespace qorai_ads
