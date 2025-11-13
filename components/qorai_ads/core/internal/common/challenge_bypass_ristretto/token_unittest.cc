/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token.h"

#include <sstream>

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsTokenTest : public test::TestBase {};

TEST_F(QoraiAdsTokenTest, Random) {
  // Arrange
  const cbr::Token token;

  // Act & Assert
  EXPECT_TRUE(token.has_value());
}

TEST_F(QoraiAdsTokenTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::Token token("");

  // Act & Assert
  EXPECT_FALSE(token.has_value());
}

TEST_F(QoraiAdsTokenTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::Token token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(token.has_value());
}

TEST_F(QoraiAdsTokenTest, DecodeBase64) {
  // Act
  const cbr::Token token = cbr::Token::DecodeBase64(cbr::test::kTokenBase64);

  // Assert
  EXPECT_TRUE(token.has_value());
}

TEST_F(QoraiAdsTokenTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::Token token = cbr::Token::DecodeBase64("");

  // Assert
  EXPECT_FALSE(token.has_value());
}

TEST_F(QoraiAdsTokenTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::Token token = cbr::Token::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(token.has_value());
}

TEST_F(QoraiAdsTokenTest, EncodeBase64) {
  // Arrange
  const cbr::Token token(cbr::test::kTokenBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kTokenBase64, token.EncodeBase64());
}

TEST_F(QoraiAdsTokenTest, EncodeRandomBase64) {
  // Arrange
  const cbr::Token token;

  // Act & Assert
  EXPECT_TRUE(token.EncodeBase64());
}

TEST_F(QoraiAdsTokenTest, IsEqual) {
  // Arrange
  const cbr::Token token;

  // Act & Assert
  EXPECT_EQ(token, token);
}

TEST_F(QoraiAdsTokenTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::Token token("");

  // Act & Assert
  EXPECT_EQ(token, token);
}

TEST_F(QoraiAdsTokenTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::Token token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(token, token);
}

TEST_F(QoraiAdsTokenTest, IsNotEqual) {
  // Arrange
  const cbr::Token token;

  // Act & Assert
  const cbr::Token another_token;
  EXPECT_NE(another_token, token);
}

TEST_F(QoraiAdsTokenTest, OutputStream) {
  // Arrange
  const cbr::Token token(cbr::test::kTokenBase64);

  // Act
  std::stringstream ss;
  ss << token;

  // Assert
  EXPECT_EQ(cbr::test::kTokenBase64, ss.str());
}

}  // namespace qorai_ads
