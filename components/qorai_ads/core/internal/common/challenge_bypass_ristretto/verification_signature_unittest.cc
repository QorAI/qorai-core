/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/verification_signature.h"

#include <sstream>

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsVerificationSignatureTest : public test::TestBase {};

TEST_F(QoraiAdsVerificationSignatureTest, FailToInitialize) {
  // Arrange
  const cbr::VerificationSignature verification_signature;

  // Act & Assert
  EXPECT_FALSE(verification_signature.has_value());
}

TEST_F(QoraiAdsVerificationSignatureTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::VerificationSignature verification_signature("");

  // Act & Assert
  EXPECT_FALSE(verification_signature.has_value());
}

TEST_F(QoraiAdsVerificationSignatureTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::VerificationSignature verification_signature(
      cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(verification_signature.has_value());
}

TEST_F(QoraiAdsVerificationSignatureTest, DecodeBase64) {
  // Act
  const cbr::VerificationSignature verification_signature =
      cbr::VerificationSignature::DecodeBase64(
          cbr::test::kVerificationSignatureBase64);

  // Assert
  EXPECT_TRUE(verification_signature.has_value());
}

TEST_F(QoraiAdsVerificationSignatureTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::VerificationSignature verification_signature =
      cbr::VerificationSignature::DecodeBase64("");

  // Assert
  EXPECT_FALSE(verification_signature.has_value());
}

TEST_F(QoraiAdsVerificationSignatureTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::VerificationSignature verification_signature =
      cbr::VerificationSignature::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(verification_signature.has_value());
}

TEST_F(QoraiAdsVerificationSignatureTest, EncodeBase64) {
  // Arrange
  const cbr::VerificationSignature verification_signature(
      cbr::test::kVerificationSignatureBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kVerificationSignatureBase64,
            verification_signature.EncodeBase64());
}

TEST_F(QoraiAdsVerificationSignatureTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::VerificationSignature verification_signature;

  // Act & Assert
  EXPECT_FALSE(verification_signature.EncodeBase64());
}

TEST_F(QoraiAdsVerificationSignatureTest, IsEqual) {
  // Arrange
  const cbr::VerificationSignature verification_signature(
      cbr::test::kVerificationSignatureBase64);

  // Act & Assert
  EXPECT_EQ(verification_signature, verification_signature);
}

TEST_F(QoraiAdsVerificationSignatureTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::VerificationSignature verification_signature;

  // Act & Assert
  EXPECT_EQ(verification_signature, verification_signature);
}

TEST_F(QoraiAdsVerificationSignatureTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::VerificationSignature verification_signature("");

  // Act & Assert
  EXPECT_EQ(verification_signature, verification_signature);
}

TEST_F(QoraiAdsVerificationSignatureTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::VerificationSignature verification_signature(
      cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(verification_signature, verification_signature);
}

TEST_F(QoraiAdsVerificationSignatureTest, IsNotEqual) {
  // Arrange
  const cbr::VerificationSignature verification_signature(
      cbr::test::kVerificationSignatureBase64);

  // Act & Assert
  const cbr::VerificationSignature another_verification_signature(
      cbr::test::kInvalidBase64);
  EXPECT_NE(another_verification_signature, verification_signature);
}

TEST_F(QoraiAdsVerificationSignatureTest, OutputStream) {
  // Arrange
  const cbr::VerificationSignature verification_signature(
      cbr::test::kVerificationSignatureBase64);

  // Act
  std::stringstream ss;
  ss << verification_signature;

  // Assert
  EXPECT_EQ(cbr::test::kVerificationSignatureBase64, ss.str());
}

TEST_F(QoraiAdsVerificationSignatureTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::VerificationSignature verification_signature;

  // Act
  std::stringstream ss;
  ss << verification_signature;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
