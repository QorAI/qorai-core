/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/condition_matcher/matchers/regex_condition_matcher_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsRegexConditionMatcherUtilTest : public test::TestBase {};

TEST_F(QoraiAdsRegexConditionMatcherUtilTest, MatchRegex) {
  // Act & Assert
  EXPECT_TRUE(MatchRegex("foo.baz.bar", "(foo|bar)"));
}

TEST_F(QoraiAdsRegexConditionMatcherUtilTest, MatchEmptyRegex) {
  // Act & Assert
  EXPECT_TRUE(MatchRegex("", ""));
}

TEST_F(QoraiAdsRegexConditionMatcherUtilTest, DoNotMatchRegex) {
  // Act & Assert
  EXPECT_FALSE(MatchRegex("foo.baz.bar", "(waldo|fred)"));
}

TEST_F(QoraiAdsRegexConditionMatcherUtilTest, DoNotMatchMalformedRegex) {
  // Act & Assert
  EXPECT_FALSE(MatchRegex("foo.baz.bar", "* ?"));
}

}  // namespace qorai_ads
