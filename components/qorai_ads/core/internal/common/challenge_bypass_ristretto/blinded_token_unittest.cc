/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"

#include <sstream>

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsBlindedTokenTest : public test::TestBase {};

TEST_F(QoraiAdsBlindedTokenTest, FailToInitialize) {
  // Arrange
  const cbr::BlindedToken blinded_token;

  // Act & Assert
  EXPECT_FALSE(blinded_token.has_value());
}

TEST_F(QoraiAdsBlindedTokenTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::BlindedToken blinded_token("");

  // Act & Assert
  EXPECT_FALSE(blinded_token.has_value());
}

TEST_F(QoraiAdsBlindedTokenTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::BlindedToken blinded_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(blinded_token.has_value());
}

TEST_F(QoraiAdsBlindedTokenTest, DecodeBase64) {
  // Act
  const cbr::BlindedToken blinded_token =
      cbr::BlindedToken::DecodeBase64(cbr::test::kBlindedTokenBase64);

  // Assert
  EXPECT_TRUE(blinded_token.has_value());
}

TEST_F(QoraiAdsBlindedTokenTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::BlindedToken blinded_token = cbr::BlindedToken::DecodeBase64("");

  // Assert
  EXPECT_FALSE(blinded_token.has_value());
}

TEST_F(QoraiAdsBlindedTokenTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::BlindedToken blinded_token =
      cbr::BlindedToken::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(blinded_token.has_value());
}

TEST_F(QoraiAdsBlindedTokenTest, EncodeBase64) {
  // Arrange
  const cbr::BlindedToken blinded_token(cbr::test::kBlindedTokenBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kBlindedTokenBase64, blinded_token.EncodeBase64());
}

TEST_F(QoraiAdsBlindedTokenTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::BlindedToken blinded_token;

  // Act & Assert
  EXPECT_FALSE(blinded_token.EncodeBase64());
}

TEST_F(QoraiAdsBlindedTokenTest, IsEqual) {
  // Arrange
  const cbr::BlindedToken blinded_token(cbr::test::kBlindedTokenBase64);

  // Act & Assert
  EXPECT_EQ(blinded_token, blinded_token);
}

TEST_F(QoraiAdsBlindedTokenTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::BlindedToken blinded_token;

  // Act & Assert
  EXPECT_EQ(blinded_token, blinded_token);
}

TEST_F(QoraiAdsBlindedTokenTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::BlindedToken blinded_token("");

  // Act & Assert
  EXPECT_EQ(blinded_token, blinded_token);
}

TEST_F(QoraiAdsBlindedTokenTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::BlindedToken blinded_token(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(blinded_token, blinded_token);
}

TEST_F(QoraiAdsBlindedTokenTest, IsNotEqual) {
  // Act & Assert
  EXPECT_NE(cbr::BlindedToken(cbr::test::kBlindedTokenBase64),
            cbr::BlindedToken(cbr::test::kInvalidBase64));
}

TEST_F(QoraiAdsBlindedTokenTest, OutputStream) {
  // Arrange
  const cbr::BlindedToken blinded_token(cbr::test::kBlindedTokenBase64);

  // Act
  std::stringstream ss;
  ss << blinded_token;

  // Assert
  EXPECT_EQ(cbr::test::kBlindedTokenBase64, ss.str());
}

TEST_F(QoraiAdsBlindedTokenTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::BlindedToken blinded_token;

  // Act
  std::stringstream ss;
  ss << blinded_token;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
