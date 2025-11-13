/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/blinded_token_util.h"

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/blinded_token_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token_test_util.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsBlindedTokenUtilTest, BlindTokens) {
  // Arrange
  const cbr::TokenList tokens = cbr::test::GetTokens();

  // Act
  const cbr::BlindedTokenList blinded_tokens = BlindTokens(tokens);

  // Assert
  EXPECT_EQ(cbr::test::GetBlindedTokens(), blinded_tokens);
}

TEST(QoraiAdsBlindedTokenUtilTToUnblindedTokensest, BlindEmptyTokens) {
  // Act & Assert
  EXPECT_THAT(cbr::BlindTokens({}), ::testing::IsEmpty());
}

TEST(QoraiAdsBlindedTokenUtilTest, BlindedTokensToRawBlindedTokens) {
  // Arrange
  const cbr::BlindedTokenList blinded_tokens = cbr::test::GetBlindedTokens();

  // Act
  const std::vector<challenge_bypass_ristretto::BlindedToken>
      raw_blinded_tokens = ToRawBlindedTokens(blinded_tokens);

  // Assert
  std::vector<challenge_bypass_ristretto::BlindedToken>
      expected_raw_blinded_tokens;
  expected_raw_blinded_tokens.reserve(blinded_tokens.size());
  for (const auto& blinded_token : blinded_tokens) {
    expected_raw_blinded_tokens.push_back(blinded_token.get());
  }
  EXPECT_EQ(expected_raw_blinded_tokens, raw_blinded_tokens);
}

TEST(QoraiAdsBlindedTokenUtilTest, EmptyBlindedTokensToRawBlindedTokens) {
  // Act & Assert
  EXPECT_THAT(cbr::ToRawBlindedTokens({}), ::testing::IsEmpty());
}

}  // namespace qorai_ads
