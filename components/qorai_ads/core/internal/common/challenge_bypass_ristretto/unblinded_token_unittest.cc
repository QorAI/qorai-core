/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token_preimage.h"  // IWYU pragma: keep
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token_preimage_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/verification_key.h"  // IWYU pragma: keep
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsUnblindedTokenTest : public test::TestBase {};

TEST_F(QoraiAdsUnblindedTokenTest, FailToInitialize) {
  // Arrange
  const cbr::UnblindedToken unblinded_token;

  // Act & Assert
  EXPECT_FALSE(unblinded_token.has_value());
}

TEST_F(QoraiAdsUnblindedTokenTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::UnblindedToken unblinded_token("");

  // Act & Assert
  EXPECT_FALSE(unblinded_token.has_value());
}

TEST_F(QoraiAdsUnblindedTokenTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(unblinded_token.has_value());
}

TEST_F(QoraiAdsUnblindedTokenTest, DecodeBase64) {
  // Act
  const cbr::UnblindedToken unblinded_token =
      cbr::UnblindedToken::DecodeBase64(cbr::test::kUnblindedTokenBase64);

  // Assert
  EXPECT_TRUE(unblinded_token.has_value());
}

TEST_F(QoraiAdsUnblindedTokenTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::UnblindedToken unblinded_token =
      cbr::UnblindedToken::DecodeBase64("");

  // Assert
  EXPECT_FALSE(unblinded_token.has_value());
}

TEST_F(QoraiAdsUnblindedTokenTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::UnblindedToken unblinded_token =
      cbr::UnblindedToken::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(unblinded_token.has_value());
}

TEST_F(QoraiAdsUnblindedTokenTest, EncodeBase64) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kUnblindedTokenBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kUnblindedTokenBase64, unblinded_token.EncodeBase64());
}

TEST_F(QoraiAdsUnblindedTokenTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::UnblindedToken unblinded_token;

  // Act & Assert
  EXPECT_FALSE(unblinded_token.EncodeBase64());
}

TEST_F(QoraiAdsUnblindedTokenTest, IsEqual) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kUnblindedTokenBase64);

  // Act & Assert
  EXPECT_EQ(unblinded_token, unblinded_token);
}

TEST_F(QoraiAdsUnblindedTokenTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::UnblindedToken unblinded_token;

  // Act & Assert
  EXPECT_EQ(unblinded_token, unblinded_token);
}

TEST_F(QoraiAdsUnblindedTokenTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::UnblindedToken unblinded_token("");

  // Act & Assert
  EXPECT_EQ(unblinded_token, unblinded_token);
}

TEST_F(QoraiAdsUnblindedTokenTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(unblinded_token, unblinded_token);
}

TEST_F(QoraiAdsUnblindedTokenTest, IsNotEqual) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kUnblindedTokenBase64);

  // Act & Assert
  const cbr::UnblindedToken another_blinded_token(cbr::test::kInvalidBase64);
  EXPECT_NE(another_blinded_token, unblinded_token);
}

TEST_F(QoraiAdsUnblindedTokenTest, OutputStream) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kUnblindedTokenBase64);

  // Act
  std::stringstream ss;
  ss << unblinded_token;

  // Assert
  EXPECT_EQ(cbr::test::kUnblindedTokenBase64, ss.str());
}

TEST_F(QoraiAdsUnblindedTokenTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::UnblindedToken unblinded_token;

  // Act
  std::stringstream ss;
  ss << unblinded_token;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

TEST_F(QoraiAdsUnblindedTokenTest, DeriveVerificationKey) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kUnblindedTokenBase64);

  // Act & Assert
  EXPECT_TRUE(unblinded_token.DeriveVerificationKey());
}

TEST_F(QoraiAdsUnblindedTokenTest,
       FailToDeriveVerificationKeyWhenUninitialized) {
  // Arrange
  const cbr::UnblindedToken unblinded_token;

  // Act & Assert
  EXPECT_FALSE(unblinded_token.DeriveVerificationKey());
}

TEST_F(QoraiAdsUnblindedTokenTest,
       FailToDeriveVerificationKeyWithInvalidUnblindedToken) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(unblinded_token.DeriveVerificationKey());
}

TEST_F(QoraiAdsUnblindedTokenTest, GetTokenPreimage) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kUnblindedTokenBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::GetTokenPreimage(), unblinded_token.GetTokenPreimage());
}

TEST_F(QoraiAdsUnblindedTokenTest, FailToGetTokenPreimageWhenUninitialized) {
  // Arrange
  const cbr::UnblindedToken unblinded_token;

  // Act & Assert
  EXPECT_FALSE(unblinded_token.GetTokenPreimage());
}

TEST_F(QoraiAdsUnblindedTokenTest,
       FailToGetTokenPreimageWithInvalidUnblindedToken) {
  // Arrange
  const cbr::UnblindedToken unblinded_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(unblinded_token.GetTokenPreimage());
}

}  // namespace qorai_ads
