/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token_util.h"

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token_test_util.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsTokenUtilTest, TokensToRawTokens) {
  // Arrange
  const cbr::TokenList tokens = cbr::test::GetTokens();

  // Act
  const std::vector<challenge_bypass_ristretto::Token> raw_tokens =
      ToRawTokens(tokens);

  // Assert
  std::vector<challenge_bypass_ristretto::Token> expected_raw_tokens;
  expected_raw_tokens.reserve(tokens.size());
  for (const auto& token : tokens) {
    expected_raw_tokens.push_back(token.get());
  }
  EXPECT_EQ(expected_raw_tokens, raw_tokens);
}

TEST(QoraiAdsTokenUtilTest, EmptyTokensToRawTokens) {
  // Act
  const std::vector<challenge_bypass_ristretto::Token> raw_tokens =
      cbr::ToRawTokens({});

  // Assert
  EXPECT_THAT(raw_tokens, ::testing::IsEmpty());
}

}  // namespace qorai_ads
