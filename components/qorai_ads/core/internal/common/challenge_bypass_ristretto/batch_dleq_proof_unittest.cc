/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/batch_dleq_proof.h"

#include <sstream>

#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"  // IWYU pragma: keep
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/blinded_token_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"  // IWYU pragma: keep
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/public_key_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/signed_token.h"  // IWYU pragma: keep
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/signed_token_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/signing_key.h"  // IWYU pragma: keep
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/signing_key_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token.h"  // IWYU pragma: keep
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"  // IWYU pragma: keep
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsBatchDLEQProofTest : public test::TestBase {};

TEST_F(QoraiAdsBatchDLEQProofTest, FailToInitialize) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof;

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToInitializeWithEmptyBase64) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof("");

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToInitializeWithInvalidBase64) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToInitializeWithInvalidBlindedTokens) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(
      cbr::test::GetInvalidBlindedTokens(), cbr::test::GetSignedTokens(),
      cbr::test::GetSigningKey());

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToInitializeWithInvalidSignedTokens) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(
      cbr::test::GetBlindedTokens(), cbr::test::GetInvalidSignedTokens(),
      cbr::test::GetSigningKey());

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToInitializeWithInvalidSigningKey) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::GetBlindedTokens(),
                                             cbr::test::GetSignedTokens(),
                                             cbr::test::GetInvalidSigningKey());

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(QoraiAdsBatchDLEQProofTest, DecodeBase64) {
  // Act
  const cbr::BatchDLEQProof batch_dleq_proof =
      cbr::BatchDLEQProof::DecodeBase64(cbr::test::kBatchDLEQProofBase64);

  // Assert
  EXPECT_TRUE(batch_dleq_proof.has_value());
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToDecodeEmptyBase64) {
  // Act
  const cbr::BatchDLEQProof batch_dleq_proof =
      cbr::BatchDLEQProof::DecodeBase64("");

  // Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToDecodeInvalidBase64) {
  // Act
  const cbr::BatchDLEQProof batch_dleq_proof =
      cbr::BatchDLEQProof::DecodeBase64(cbr::test::kInvalidBase64);

  // Assert
  EXPECT_FALSE(batch_dleq_proof.has_value());
}

TEST_F(QoraiAdsBatchDLEQProofTest, EncodeBase64) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::kBatchDLEQProofBase64, batch_dleq_proof.EncodeBase64());
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToEncodeBase64WhenUninitialized) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof;

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.EncodeBase64());
}

TEST_F(QoraiAdsBatchDLEQProofTest, Verify) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_TRUE(batch_dleq_proof.Verify(cbr::test::GetBlindedTokens(),
                                      cbr::test::GetSignedTokens(),
                                      cbr::test::GetPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToVerifyWhenUninitialized) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof;

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.Verify(cbr::test::GetBlindedTokens(),
                                       cbr::test::GetSignedTokens(),
                                       cbr::test::GetPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToVerifyWithInvalidBlindedTokens) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.Verify(cbr::test::GetInvalidBlindedTokens(),
                                       cbr::test::GetSignedTokens(),
                                       cbr::test::GetPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToVerifyWithInvalidSignedTokens) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.Verify(cbr::test::GetBlindedTokens(),
                                       cbr::test::GetInvalidSignedTokens(),
                                       cbr::test::GetPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToVerifyWithMismatchingPublicKey) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.Verify(cbr::test::GetBlindedTokens(),
                                       cbr::test::GetSignedTokens(),
                                       cbr::test::GetMismatchingPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToVerifyWithInvalidPublicKey) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.Verify(cbr::test::GetBlindedTokens(),
                                       cbr::test::GetSignedTokens(),
                                       cbr::test::GetInvalidPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest, VerifyAndUnblind) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_EQ(cbr::test::GetUnblindedTokens(),
            batch_dleq_proof.VerifyAndUnblind(
                cbr::test::GetTokens(), cbr::test::GetBlindedTokens(),
                cbr::test::GetSignedTokens(), cbr::test::GetPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToVerifyAndUnblindWhenUninitialized) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof;

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.VerifyAndUnblind(
      cbr::test::GetTokens(), cbr::test::GetBlindedTokens(),
      cbr::test::GetSignedTokens(), cbr::test::GetPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToVerifyAndUnblindWithInvalidTokens) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.VerifyAndUnblind(
      cbr::test::GetInvalidTokens(), cbr::test::GetBlindedTokens(),
      cbr::test::GetSignedTokens(), cbr::test::GetPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest,
       FailToVerifyAndUnblindWithInvalidBlindedTokens) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.VerifyAndUnblind(
      cbr::test::GetTokens(), cbr::test::GetInvalidBlindedTokens(),
      cbr::test::GetSignedTokens(), cbr::test::GetPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest,
       FailToVerifyAndUnblindWithInvalidSignedTokens) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.VerifyAndUnblind(
      cbr::test::GetTokens(), cbr::test::GetBlindedTokens(),
      cbr::test::GetInvalidSignedTokens(), cbr::test::GetPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest,
       FailToVerifyAndUnblindWithMismatchingPublicKey) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.VerifyAndUnblind(
      cbr::test::GetTokens(), cbr::test::GetBlindedTokens(),
      cbr::test::GetSignedTokens(), cbr::test::GetMismatchingPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest, FailToVerifyAndUnblindWithInvalidPublicKey) {
  // Arrange
  cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_FALSE(batch_dleq_proof.VerifyAndUnblind(
      cbr::test::GetTokens(), cbr::test::GetBlindedTokens(),
      cbr::test::GetSignedTokens(), cbr::test::GetInvalidPublicKey()));
}

TEST_F(QoraiAdsBatchDLEQProofTest, IsEqual) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  EXPECT_EQ(batch_dleq_proof, batch_dleq_proof);
}

TEST_F(QoraiAdsBatchDLEQProofTest, IsEqualWhenUninitialized) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof;

  // Act & Assert
  EXPECT_EQ(batch_dleq_proof, batch_dleq_proof);
}

TEST_F(QoraiAdsBatchDLEQProofTest, IsEmptyBase64Equal) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof("");

  // Act & Assert
  EXPECT_EQ(batch_dleq_proof, batch_dleq_proof);
}

TEST_F(QoraiAdsBatchDLEQProofTest, IsInvalidBase64Equal) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_EQ(batch_dleq_proof, batch_dleq_proof);
}

TEST_F(QoraiAdsBatchDLEQProofTest, IsNotEqual) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act & Assert
  const cbr::BatchDLEQProof another_batch_dleq_proof(cbr::test::kInvalidBase64);
  EXPECT_NE(another_batch_dleq_proof, batch_dleq_proof);
}

TEST_F(QoraiAdsBatchDLEQProofTest, OutputStream) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof(cbr::test::kBatchDLEQProofBase64);

  // Act
  std::stringstream ss;
  ss << batch_dleq_proof;

  // Assert
  EXPECT_EQ(cbr::test::kBatchDLEQProofBase64, ss.str());
}

TEST_F(QoraiAdsBatchDLEQProofTest, OutputStreamWhenUninitialized) {
  // Arrange
  const cbr::BatchDLEQProof batch_dleq_proof;

  // Act
  std::stringstream ss;
  ss << batch_dleq_proof;

  // Assert
  EXPECT_THAT(ss.str(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
