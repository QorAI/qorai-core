/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_token_util.h"

#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_tokens.h"
#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_tokens_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsPaymentTokenUtilTest : public test::TestBase {};

TEST_F(QoraiAdsPaymentTokenUtilTest, GetPaymentToken) {
  // Arrange
  const PaymentTokenList payment_tokens = test::SetPaymentTokens(/*count=*/2);

  // Act & Assert
  EXPECT_EQ(payment_tokens.front(), MaybeGetPaymentToken());
}

TEST_F(QoraiAdsPaymentTokenUtilTest, DoNotGetPaymentToken) {
  // Act & Assert
  EXPECT_FALSE(MaybeGetPaymentToken());
}

TEST_F(QoraiAdsPaymentTokenUtilTest, AddPaymentTokens) {
  // Arrange
  const PaymentTokenList payment_tokens = test::BuildPaymentTokens(/*count=*/2);
  ASSERT_THAT(payment_tokens, ::testing::SizeIs(2));

  const PaymentTokenInfo& token_1 = payment_tokens.at(0);
  const PaymentTokenInfo& token_2 = payment_tokens.at(1);

  test::GetPaymentTokens().SetTokens({token_1});

  // Act
  AddPaymentTokens({token_2});

  // Assert
  const PaymentTokenList expected_payment_tokens = {token_1, token_2};
  EXPECT_EQ(expected_payment_tokens, GetAllPaymentTokens());
}

TEST_F(QoraiAdsPaymentTokenUtilTest, RemovePaymentToken) {
  // Arrange
  const PaymentTokenList payment_tokens = test::BuildPaymentTokens(/*count=*/3);
  ASSERT_THAT(payment_tokens, ::testing::SizeIs(3));

  const PaymentTokenInfo& token_1 = payment_tokens.at(0);
  const PaymentTokenInfo& token_2 = payment_tokens.at(1);
  const PaymentTokenInfo& token_3 = payment_tokens.at(2);

  test::GetPaymentTokens().SetTokens(payment_tokens);

  // Act
  RemovePaymentToken(token_2);

  // Assert
  const PaymentTokenList expected_payment_tokens = {token_1, token_3};
  EXPECT_EQ(expected_payment_tokens, GetAllPaymentTokens());
}

TEST_F(QoraiAdsPaymentTokenUtilTest, PaymentTokenCount) {
  // Arrange
  test::SetPaymentTokens(/*count=*/3);

  // Act & Assert
  EXPECT_EQ(3U, PaymentTokenCount());
}

}  // namespace qorai_ads
