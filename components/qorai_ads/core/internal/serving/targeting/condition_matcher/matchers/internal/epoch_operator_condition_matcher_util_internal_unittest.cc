/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/condition_matcher/matchers/internal/epoch_operator_condition_matcher_util_internal.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsOperatorConditionMatcherUtilInternalTest : public test::TestBase {
};

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest,
       DoNotParseNegativeDays) {
  // Act & Assert
  EXPECT_FALSE(ParseDays("[T=]:-1"));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest, ParseDayZero) {
  // Act & Assert
  EXPECT_EQ(0, ParseDays("[T=]:0"));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest, ParseDays) {
  // Act & Assert
  EXPECT_EQ(7, ParseDays("[T=]:7"));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest,
       DoNotParseNonIntegerDays) {
  // Act & Assert
  EXPECT_FALSE(ParseDays("[T=]:1.5"));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest,
       DoNotParseMalformedDays) {
  // Act & Assert
  EXPECT_FALSE(ParseDays("[T=]: 7 "));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest,
       DoNotParseInvalidDays) {
  // Act & Assert
  EXPECT_FALSE(ParseDays("[T=]:seven"));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest, IsUnixEpochTimestamp) {
  // Act & Assert
  EXPECT_TRUE(IsUnixEpochTimestamp(0));
  EXPECT_TRUE(IsUnixEpochTimestamp(2147483647));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest,
       IsNotUnixEpochTimestamp) {
  // Act & Assert
  EXPECT_FALSE(IsUnixEpochTimestamp(-1));
  EXPECT_FALSE(IsUnixEpochTimestamp(2147483648));
  EXPECT_FALSE(IsUnixEpochTimestamp(
      13372214400000000 /* 1st October 2024 00:00:00 UTC */));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest, WindowsToUnixEpoch) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(1727740800,
            WindowsToUnixEpoch(
                13372214400000000 /* 1st October 2024 00:00:00 UTC */));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest,
       TimeDeltaSinceUnixEpoch) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(base::Days(2),
            TimeDeltaSinceEpoch(1727740800 /*1st October 2024 00:00:00 UTC*/));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest,
       TimeDeltaSinceWindowsEpoch) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(base::Days(2),
            TimeDeltaSinceEpoch(
                13372214400000000 /*1st October 2024 00:00:00.000 UTC*/));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest,
       ParseWindowsEpochTimeDelta) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(
      base::Days(2),
      ParseTimeDelta("13372214400000000" /*1st October 2024 00:00:00 UTC*/));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest,
       ParseUnixEpochWithFractionalSecondsTimeDelta) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(
      base::Days(2),
      ParseTimeDelta("1727740800.3237710" /*1st October 2024 00:00:00 UTC*/));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest,
       ParseUnixEpochTimeDelta) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(base::Days(2),
            ParseTimeDelta("1727740800" /*1st October 2024 00:00:00 UTC*/));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest,
       ParseTimeStringTimeDelta) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_EQ(
      base::Days(2),
      ParseTimeDelta("2024-10-01T00:00:00Z" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(
      base::Days(2),
      ParseTimeDelta(
          "2024-10-01T00:00:00.000000Z" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(
      base::Days(2),
      ParseTimeDelta("2024-10-01T00:00:00" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(
      base::Days(2),
      ParseTimeDelta(
          "2024-10-01T00:00:00.000000" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(base::Days(2),
            ParseTimeDelta(
                "2024-09-30T19:00:00-05:00" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(
      base::Days(2),
      ParseTimeDelta("1 Oct 2024 00:00:00" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(
      base::Days(2),
      ParseTimeDelta(
          "1 Oct 2024 00:00:00.000000" /*1st October 2024 00:00:00 UTC*/));
  EXPECT_EQ(base::Days(2),
            ParseTimeDelta(
                "30 Sept 2024 19:00:00 EST" /*1st October 2024 00:00:00 UTC*/));
}

TEST_F(QoraiAdsOperatorConditionMatcherUtilInternalTest, DoNotParseTimeDelta) {
  // Act & Assert
  EXPECT_FALSE(ParseTimeDelta("broken time"));
}

}  // namespace qorai_ads
