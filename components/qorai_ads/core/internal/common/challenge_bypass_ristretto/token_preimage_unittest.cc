/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token_preimage.h"

#include <sstream>

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsTokenPreimageTest : public test::TestBase {};

TEST_F(QoraiAdsTokenPreimageTest, FailToInitialize) {
  // Arrange
  const cbr::TokenPreimage token_preimage;

  // Act & Assert
  EXPECT_FALSE(token_preimage.has_value());
}

TEST_F(QoraiAdsTokenPreimageTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::TokenPreimage token_preimage("");

  // Act & Assert
  EXPECT_FALSE(token_preimage.has_value());
}

TEST_F(QoraiAdsTokenPreimageTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::TokenPreimage token_preimage(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(token_preimage.has_value());
}

TEST_F(QoraiAdsTokenPreimageTest, DecodeBase64) {
  // Act
  const cbr::TokenPreimage token_preimage =
      cbr::TokenPreimage::DecodeBase64(cbr::test::kTokenPreimageBase64);

  // Assert
  EXPECT_TRUE(token_preimage.has_value());
}

TEST_F(QoraiAdsTokenPreimageTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::TokenPreimage token_preimage =
      cbr::TokenPreimage::DecodeBase64("");

  // Assert
  EXPECT_FALSE(token_preimage.has_value());
}

TEST_F(QoraiAdsTokenPreimageTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::TokenPreimage token_preimage =
      cbr::TokenPreimage::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(token_preimage.has_value());
}

TEST_F(QoraiAdsTokenPreimageTest, EncodeBase64) {
  // Arrange
  const cbr::TokenPreimage token_preimage(cbr::test::kTokenPreimageBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kTokenPreimageBase64, token_preimage.EncodeBase64());
}

TEST_F(QoraiAdsTokenPreimageTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::TokenPreimage token_preimage;

  // Act & Assert
  EXPECT_FALSE(token_preimage.EncodeBase64());
}

TEST_F(QoraiAdsTokenPreimageTest, IsEqual) {
  // Arrange
  const cbr::TokenPreimage token_preimage(cbr::test::kTokenPreimageBase64);

  // Act & Assert
  EXPECT_EQ(token_preimage, token_preimage);
}

TEST_F(QoraiAdsTokenPreimageTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::TokenPreimage token_preimage;

  // Act & Assert
  EXPECT_EQ(token_preimage, token_preimage);
}

TEST_F(QoraiAdsTokenPreimageTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::TokenPreimage token_preimage("");

  // Act & Assert
  EXPECT_EQ(token_preimage, token_preimage);
}

TEST_F(QoraiAdsTokenPreimageTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::TokenPreimage token_preimage(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(token_preimage, token_preimage);
}

TEST_F(QoraiAdsTokenPreimageTest, IsNotEqual) {
  // Arrange
  const cbr::TokenPreimage token_preimage(cbr::test::kTokenPreimageBase64);

  // Act & Assert
  const cbr::TokenPreimage another_token_preimage(cbr::test::kInvalidBase64);
  EXPECT_NE(another_token_preimage, token_preimage);
}

TEST_F(QoraiAdsTokenPreimageTest, OutputStream) {
  // Arrange
  const cbr::TokenPreimage token_preimage(cbr::test::kTokenPreimageBase64);

  // Act
  std::stringstream ss;
  ss << token_preimage;

  // Assert
  EXPECT_EQ(cbr::test::kTokenPreimageBase64, ss.str());
}

TEST_F(QoraiAdsTokenPreimageTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::TokenPreimage token_preimage;

  // Act
  std::stringstream ss;
  ss << token_preimage;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
