/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/condition_matcher/matchers/pattern_condition_matcher_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsPatternConditionMatcherUtilTest : public test::TestBase {};

TEST_F(QoraiAdsPatternConditionMatcherUtilTest, MatchPattern) {
  // Act & Assert
  EXPECT_TRUE(MatchPattern("foo.baz.bar", "foo?baz.*"));
}

TEST_F(QoraiAdsPatternConditionMatcherUtilTest, MatchEmptyPattern) {
  // Act & Assert
  EXPECT_TRUE(MatchPattern("", ""));
}

TEST_F(QoraiAdsPatternConditionMatcherUtilTest, MatchEscapedPattern) {
  // Act & Assert
  EXPECT_TRUE(MatchPattern(R"(*.bar.?)", R"(\*.bar.\?)"));
}

TEST_F(QoraiAdsPatternConditionMatcherUtilTest, DoNotMatchPattern) {
  // Act & Assert
  EXPECT_FALSE(MatchPattern("foo.baz.bar", "bar.*.foo"));
}

}  // namespace qorai_ads
