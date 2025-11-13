/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/signed_token.h"

#include <sstream>

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsSignedTokenTest : public test::TestBase {};

TEST_F(QoraiAdsSignedTokenTest, FailToInitialize) {
  // Arrange
  const cbr::SignedToken signed_token;

  // Act & Assert
  EXPECT_FALSE(signed_token.has_value());
}

TEST_F(QoraiAdsSignedTokenTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::SignedToken signed_token("");

  // Act & Assert
  EXPECT_FALSE(signed_token.has_value());
}

TEST_F(QoraiAdsSignedTokenTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::SignedToken signed_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(signed_token.has_value());
}

TEST_F(QoraiAdsSignedTokenTest, DecodeBase64) {
  // Act
  const cbr::SignedToken signed_token =
      cbr::SignedToken::DecodeBase64(cbr::test::kSignedTokenBase64);

  // Assert
  EXPECT_TRUE(signed_token.has_value());
}

TEST_F(QoraiAdsSignedTokenTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::SignedToken signed_token = cbr::SignedToken::DecodeBase64("");

  // Assert
  EXPECT_FALSE(signed_token.has_value());
}

TEST_F(QoraiAdsSignedTokenTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::SignedToken signed_token =
      cbr::SignedToken::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(signed_token.has_value());
}

TEST_F(QoraiAdsSignedTokenTest, EncodeBase64) {
  // Arrange
  const cbr::SignedToken signed_token(cbr::test::kSignedTokenBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kSignedTokenBase64, signed_token.EncodeBase64());
}

TEST_F(QoraiAdsSignedTokenTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::SignedToken signed_token;

  // Act & Assert
  EXPECT_FALSE(signed_token.EncodeBase64());
}

TEST_F(QoraiAdsSignedTokenTest, IsEqual) {
  // Arrange
  const cbr::SignedToken signed_token(cbr::test::kSignedTokenBase64);

  // Act & Assert
  EXPECT_EQ(signed_token, signed_token);
}

TEST_F(QoraiAdsSignedTokenTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::SignedToken signed_token;

  // Act & Assert
  EXPECT_EQ(signed_token, signed_token);
}

TEST_F(QoraiAdsSignedTokenTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::SignedToken signed_token("");

  // Act & Assert
  EXPECT_EQ(signed_token, signed_token);
}

TEST_F(QoraiAdsSignedTokenTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::SignedToken signed_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(signed_token, signed_token);
}

TEST_F(QoraiAdsSignedTokenTest, IsNotEqual) {
  // Arrange
  const cbr::SignedToken signed_token(cbr::test::kSignedTokenBase64);

  // Act & Assert
  const cbr::SignedToken another_signed_token(cbr::test::kInvalidBase64);
  EXPECT_NE(another_signed_token, signed_token);
}

TEST_F(QoraiAdsSignedTokenTest, OutputStream) {
  // Arrange
  const cbr::SignedToken signed_token(cbr::test::kSignedTokenBase64);

  // Act
  std::stringstream ss;
  ss << signed_token;

  // Assert
  EXPECT_EQ(cbr::test::kSignedTokenBase64, ss.str());
}

TEST_F(QoraiAdsSignedTokenTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::SignedToken signed_token;

  // Act
  std::stringstream ss;
  ss << signed_token;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
