/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/condition_matcher/condition_matcher_util.h"

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/ads_client/ads_client_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsConditionMatcherUtilTest : public test::TestBase {
 public:
  QoraiAdsConditionMatcherUtilTest() {
    // We need to set the clock to 00:00:00 UTC here to ensure the pref registry
    // in `common/test/pref_registry_test_util.cc` is initialized correctly with
    // deterministic default values.
    AdvanceClockTo(test::TimeFromUTCString("14 October 2024 00:00:00"));
  }
};

TEST_F(QoraiAdsConditionMatcherUtilTest, MatchEmptyConditions) {
  // Act & Assert
  EXPECT_TRUE(MatchConditions(GetAdsClient().GetVirtualPrefs(),
                              /*condition_matchers=*/{}));
}

TEST_F(QoraiAdsConditionMatcherUtilTest, MatchMultipleConditions) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {prefs::kSubdivisionTargetingUserSelectedSubdivision, "AUTO"},
      {prefs::kOptedInToNotificationAds, "1"}};

  // Act & Assert
  EXPECT_TRUE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest, MatchEpochEqualOperatorCondition) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {prefs::kServeAdAt, "[T=]:7"}};

  AdvanceClockBy(base::Days(7));

  // Act & Assert
  EXPECT_TRUE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest,
       MatchEpochEqualOperatorConditionForUnknownPrefPath) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {"unknown_pref_path", "[T=]:0"}};

  // Act & Assert
  EXPECT_TRUE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest,
       DoNotMatchEpochEqualOperatorConditionForUnknownPrefPath) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {"unknown_pref_path", "[T=]:1"}};

  // Act & Assert
  EXPECT_FALSE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest,
       DoNotMatchEpochEqualOperatorCondition) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {prefs::kServeAdAt, "[T=]:7"}};

  AdvanceClockBy(base::Days(7) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_FALSE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest, MatchNumericalEqualOperatorCondition) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {prefs::kMaximumNotificationAdsPerHour,
       "[R=]:-1"}};  // Value is "-1" in the pref.

  // Act & Assert
  EXPECT_TRUE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest,
       MatchNumericalEqualOperatorConditionForUnknownPrefPath) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {"unknown_pref_path", "[R=]:0"}};

  // Act & Assert
  EXPECT_TRUE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest,
       DoNotMatchNumericalEqualOperatorConditionForUnknownPrefPath) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {"unknown_pref_path", "[R=]:1"}};

  // Act & Assert
  EXPECT_FALSE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest,
       DoNotMatchNumericalEqualOperatorCondition) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {prefs::kMaximumNotificationAdsPerHour,
       "[R=]:1"}};  // Value is "-1" in the pref.

  // Act & Assert
  EXPECT_FALSE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest, MatchPatternCondition) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {prefs::kSubdivisionTargetingUserSelectedSubdivision,
       "?UT*"}};  // Value is "AUTO" in the pref.

  // Act & Assert
  EXPECT_TRUE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest, DoNotMatchPatternCondition) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {prefs::kSubdivisionTargetingUserSelectedSubdivision,
       "?FOO*"}};  // Value is "AUTO" in the pref.

  // Act & Assert
  EXPECT_FALSE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest, MatchRegexCondition) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {prefs::kSubdivisionTargetingUserSelectedSubdivision,
       "^AU"}};  // Value is "AUTO" in the pref.

  // Act & Assert
  EXPECT_TRUE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest, DoNotMatchRegexCondition) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {prefs::kSubdivisionTargetingUserSelectedSubdivision,
       "^FOO"}};  // Value is "AUTO" in the pref.

  // Act & Assert
  EXPECT_FALSE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest,
       DoNotMatchConditionsIfPrefPathWasNotFound) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {{"foo.bar", "baz"}};

  // Act & Assert
  EXPECT_FALSE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest,
       MatchConditionsWithNotOperatorWhenPrefPathNotFound) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {{"[!]:foo.bar", "baz"}};

  // Act & Assert
  EXPECT_TRUE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

TEST_F(QoraiAdsConditionMatcherUtilTest,
       DoNotMatchConditionsIfAllConditionsAreFalse) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {prefs::kOptedInToNotificationAds, "0"},  // Value is "1" in the pref.
      {prefs::kServeAdAt, "[T>]:7"}};           // 5 days ago in the pref.

  AdvanceClockBy(base::Days(5));

  // Act & Assert
  EXPECT_FALSE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

}  // namespace qorai_ads
