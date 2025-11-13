/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_tokens.h"

#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_tokens_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsPaymentTokensTest : public test::TestBase {};

TEST_F(QoraiAdsPaymentTokensTest, GetToken) {
  // Arrange
  const PaymentTokenList tokens = test::BuildPaymentTokens(/*count=*/2);
  ASSERT_THAT(tokens, ::testing::SizeIs(2));

  PaymentTokens payment_tokens;
  payment_tokens.SetTokens(tokens);

  // Act & Assert
  EXPECT_EQ(tokens.front(), payment_tokens.GetToken());
}

TEST_F(QoraiAdsPaymentTokensTest, GetAllTokens) {
  // Arrange
  PaymentTokens payment_tokens;
  payment_tokens.SetTokens(test::BuildPaymentTokens(/*count=*/2));

  // Act & Assert
  EXPECT_EQ(test::BuildPaymentTokens(/*count=*/2),
            payment_tokens.GetAllTokens());
}

TEST_F(QoraiAdsPaymentTokensTest, SetTokens) {
  // Arrange
  PaymentTokens payment_tokens;

  // Act
  payment_tokens.SetTokens(test::BuildPaymentTokens(/*count=*/2));

  // Assert
  EXPECT_EQ(test::BuildPaymentTokens(/*count=*/2),
            payment_tokens.GetAllTokens());
}

TEST_F(QoraiAdsPaymentTokensTest, SetEmptyTokens) {
  // Arrange
  PaymentTokens payment_tokens;

  // Act
  payment_tokens.SetTokens({});

  // Assert
  EXPECT_TRUE(payment_tokens.IsEmpty());
}

TEST_F(QoraiAdsPaymentTokensTest, AddTokens) {
  // Arrange
  const PaymentTokenList tokens = test::BuildPaymentTokens(/*count=*/2);
  ASSERT_THAT(tokens, ::testing::SizeIs(2));

  PaymentTokens payment_tokens;
  payment_tokens.SetTokens({tokens.at(0)});

  // Act
  payment_tokens.AddTokens({tokens.at(1)});

  // Assert
  EXPECT_EQ(2U, payment_tokens.Count());
}

TEST_F(QoraiAdsPaymentTokensTest, AddEmptyTokens) {
  // Arrange
  PaymentTokens payment_tokens;

  // Act
  payment_tokens.AddTokens({});

  // Assert
  EXPECT_TRUE(payment_tokens.IsEmpty());
}

TEST_F(QoraiAdsPaymentTokensTest, DoNotAddDuplicateTokens) {
  // Arrange
  const PaymentTokenInfo payment_token = test::BuildPaymentToken();

  PaymentTokens payment_tokens;
  payment_tokens.AddTokens({payment_token});

  // Act
  payment_tokens.AddTokens({payment_token});

  // Assert
  EXPECT_EQ(1U, payment_tokens.Count());
}

TEST_F(QoraiAdsPaymentTokensTest, RemoveToken) {
  // Arrange
  const PaymentTokenList tokens = test::BuildPaymentTokens(/*count=*/2);
  ASSERT_THAT(tokens, ::testing::SizeIs(2));

  PaymentTokens payment_tokens;
  payment_tokens.SetTokens(tokens);

  const PaymentTokenInfo& token_1 = tokens.at(0);
  const PaymentTokenInfo& token_2 = tokens.at(1);

  // Act
  payment_tokens.RemoveToken(token_2);

  // Assert
  EXPECT_EQ(PaymentTokenList{token_1}, payment_tokens.GetAllTokens());
}

TEST_F(QoraiAdsPaymentTokensTest, RemoveTokens) {
  // Arrange
  const PaymentTokenList tokens = test::BuildPaymentTokens(/*count=*/3);
  ASSERT_THAT(tokens, ::testing::SizeIs(3));

  PaymentTokens payment_tokens;
  payment_tokens.SetTokens(tokens);

  const PaymentTokenInfo& token_1 = tokens.at(0);
  const PaymentTokenInfo& token_2 = tokens.at(1);
  const PaymentTokenInfo& token_3 = tokens.at(2);

  // Act
  payment_tokens.RemoveTokens({token_1, token_3});

  // Assert
  EXPECT_EQ(PaymentTokenList{token_2}, payment_tokens.GetAllTokens());
}

TEST_F(QoraiAdsPaymentTokensTest, RemoveAllTokens) {
  // Arrange
  PaymentTokens payment_tokens;
  payment_tokens.SetTokens(test::BuildPaymentTokens(/*count=*/2));

  // Act
  payment_tokens.RemoveAllTokens();

  // Assert
  EXPECT_TRUE(payment_tokens.IsEmpty());
}

TEST_F(QoraiAdsPaymentTokensTest, TokenDoesExist) {
  // Arrange
  const PaymentTokenInfo payment_token = test::BuildPaymentToken();

  PaymentTokens payment_tokens;
  payment_tokens.SetTokens({payment_token});

  // Act & Assert
  EXPECT_TRUE(payment_tokens.TokenExists(payment_token));
}

TEST_F(QoraiAdsPaymentTokensTest, TokenDoesNotExist) {
  // Arrange
  PaymentTokens payment_tokens;

  // Act & Assert
  EXPECT_FALSE(payment_tokens.TokenExists(test::BuildPaymentToken()));
}

TEST_F(QoraiAdsPaymentTokensTest, Count) {
  // Arrange
  PaymentTokens payment_tokens;
  payment_tokens.SetTokens(test::BuildPaymentTokens(/*count=*/3));

  // Act & Assert
  EXPECT_EQ(3U, payment_tokens.Count());
}

TEST_F(QoraiAdsPaymentTokensTest, IsEmpty) {
  // Arrange
  const PaymentTokens payment_tokens;

  // Act & Assert
  EXPECT_TRUE(payment_tokens.IsEmpty());
}

TEST_F(QoraiAdsPaymentTokensTest, IsNotEmpty) {
  // Arrange
  PaymentTokens payment_tokens;
  payment_tokens.SetTokens(test::BuildPaymentTokens(/*count=*/1));

  // Act & Assert
  EXPECT_FALSE(payment_tokens.IsEmpty());
}

}  // namespace qorai_ads
