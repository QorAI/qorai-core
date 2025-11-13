/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"

#include <sstream>

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsPublicKeyTest : public test::TestBase {};

TEST_F(QoraiAdsPublicKeyTest, FailToInitialize) {
  // Arrange
  const cbr::PublicKey public_key;

  // Act & Assert
  EXPECT_FALSE(public_key.has_value());
}

TEST_F(QoraiAdsPublicKeyTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::PublicKey public_key("");

  // Act & Assert
  EXPECT_FALSE(public_key.has_value());
}

TEST_F(QoraiAdsPublicKeyTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::PublicKey public_key(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(public_key.has_value());
}

TEST_F(QoraiAdsPublicKeyTest, DecodeBase64) {
  // Act
  const cbr::PublicKey public_key =
      cbr::PublicKey::DecodeBase64(cbr::test::kPublicKeyBase64);

  // Assert
  EXPECT_TRUE(public_key.has_value());
}

TEST_F(QoraiAdsPublicKeyTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::PublicKey public_key = cbr::PublicKey::DecodeBase64("");

  // Assert
  EXPECT_FALSE(public_key.has_value());
}

TEST_F(QoraiAdsPublicKeyTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::PublicKey public_key =
      cbr::PublicKey::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(public_key.has_value());
}

TEST_F(QoraiAdsPublicKeyTest, EncodeBase64) {
  // Arrange
  const cbr::PublicKey public_key(cbr::test::kPublicKeyBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kPublicKeyBase64, public_key.EncodeBase64());
}

TEST_F(QoraiAdsPublicKeyTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::PublicKey public_key;

  // Act & Assert
  EXPECT_FALSE(public_key.EncodeBase64());
}

TEST_F(QoraiAdsPublicKeyTest, IsEqual) {
  // Arrange
  const cbr::PublicKey public_key(cbr::test::kPublicKeyBase64);

  // Act & Assert
  EXPECT_EQ(public_key, public_key);
}

TEST_F(QoraiAdsPublicKeyTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::PublicKey public_key;

  // Act & Assert
  EXPECT_EQ(public_key, public_key);
}

TEST_F(QoraiAdsPublicKeyTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::PublicKey public_key("");

  // Act & Assert
  EXPECT_EQ(public_key, public_key);
}

TEST_F(QoraiAdsPublicKeyTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::PublicKey public_key(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(public_key, public_key);
}

TEST_F(QoraiAdsPublicKeyTest, IsNotEqual) {
  // Arrange
  const cbr::PublicKey public_key(cbr::test::kPublicKeyBase64);

  // Act & Assert
  const cbr::PublicKey another_public_key(cbr::test::kInvalidBase64);
  EXPECT_NE(another_public_key, public_key);
}

TEST_F(QoraiAdsPublicKeyTest, OutputStream) {
  // Arrange
  const cbr::PublicKey public_key(cbr::test::kPublicKeyBase64);

  // Act
  std::stringstream ss;
  ss << public_key;

  // Assert
  EXPECT_EQ(cbr::test::kPublicKeyBase64, ss.str());
}

TEST_F(QoraiAdsPublicKeyTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::PublicKey public_key;

  // Act
  std::stringstream ss;
  ss << public_key;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
