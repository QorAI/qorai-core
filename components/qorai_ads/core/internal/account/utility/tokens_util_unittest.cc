/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/utility/tokens_util.h"

#include "base/values.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"  // IWYU pragma: keep
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/blinded_token_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/challenge_bypass_ristretto_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/public_key_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/signed_token.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token.h"  // IWYU pragma: keep
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/token_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

namespace {

base::Value::Dict BuildUrlResponseBody() {
  return base::Value::Dict()
      .Set("batchProof", cbr::test::kBatchDLEQProofBase64)
      .Set("signedTokens",
           base::Value::List().Append(cbr::test::kSignedTokenBase64))
      .Set("publicKey", cbr::test::kPublicKeyBase64);
}

}  // namespace

class QoraiAdsSignedTokensUtilTest : public test::TestBase {};

TEST_F(QoraiAdsSignedTokensUtilTest, ParsePublicKey) {
  // Act & Assert
  EXPECT_EQ(cbr::PublicKey(cbr::test::kPublicKeyBase64),
            ParsePublicKey(BuildUrlResponseBody()));
}

TEST_F(QoraiAdsSignedTokensUtilTest, DoNotParseInvalidPublicKey) {
  // Arrange
  const base::Value::Dict dict =
      BuildUrlResponseBody().Set("publicKey", cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(ParsePublicKey(dict));
}

TEST_F(QoraiAdsSignedTokensUtilTest, ParseSignedTokens) {
  // Act
  std::optional<cbr::SignedTokenList> signed_tokens =
      ParseSignedTokens(BuildUrlResponseBody());
  ASSERT_TRUE(signed_tokens);

  // Assert
  const cbr::SignedTokenList expected_signed_tokens = {
      cbr::SignedToken(cbr::test::kSignedTokenBase64)};
  EXPECT_EQ(expected_signed_tokens, signed_tokens);
}

TEST_F(QoraiAdsSignedTokensUtilTest, DoNotParseSignedTokensIfMissingKey) {
  // Arrange
  base::Value::Dict dict = BuildUrlResponseBody();
  dict.Remove("signedTokens");

  // Act & Assert
  EXPECT_FALSE(ParseSignedTokens(dict));
}

TEST_F(QoraiAdsSignedTokensUtilTest, DoNotParseInvalidSignedTokens) {
  // Arrange
  const base::Value::Dict dict =
      BuildUrlResponseBody().Set("signedTokens", cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(ParseSignedTokens(dict));
}

TEST_F(QoraiAdsSignedTokensUtilTest, ParseVerifyAndUnblindTokens) {
  // Arrange
  test::BuildAndSetIssuers();

  // Act
  const auto result = ParseVerifyAndUnblindTokens(
      BuildUrlResponseBody(), cbr::test::GetTokens(),
      cbr::test::GetBlindedTokens(), cbr::test::GetPublicKey());

  // Assert
  EXPECT_TRUE(result.has_value());
}

TEST_F(QoraiAdsSignedTokensUtilTest,
       DoNotParseVerifyAndUnblindTokensIfMissingBatchDLEQProof) {
  // Arrange
  base::Value::Dict dict = BuildUrlResponseBody();
  dict.Remove("batchProof");

  // Act
  const auto result = ParseVerifyAndUnblindTokens(dict, cbr::test::GetTokens(),
                                                  cbr::test::GetBlindedTokens(),
                                                  cbr::test::GetPublicKey());

  // Assert
  EXPECT_FALSE(result.has_value());
}

TEST_F(QoraiAdsSignedTokensUtilTest,
       DoNotParseVerifyAndUnblindMissingSignedTokens) {
  // Arrange
  base::Value::Dict dict = BuildUrlResponseBody();
  dict.Remove("signedTokens");

  // Act
  const auto result = ParseVerifyAndUnblindTokens(dict, cbr::test::GetTokens(),
                                                  cbr::test::GetBlindedTokens(),
                                                  cbr::test::GetPublicKey());

  // Assert
  EXPECT_FALSE(result.has_value());
}

TEST_F(QoraiAdsSignedTokensUtilTest,
       DoNoParseVerifyAndUnblindMalformedSignedTokens) {
  // Arrange
  const base::Value::Dict dict = BuildUrlResponseBody().Set(
      "signedTokens", base::Value::List().Append(/*invalid*/ 0));

  // Act
  const auto result = ParseVerifyAndUnblindTokens(dict, cbr::test::GetTokens(),
                                                  cbr::test::GetBlindedTokens(),
                                                  cbr::test::GetPublicKey());

  // Assert
  EXPECT_FALSE(result.has_value());
}

TEST_F(QoraiAdsSignedTokensUtilTest,
       DoNotParseVerifyAndUnblindInvalidSignedTokens) {
  // Arrange
  const base::Value::Dict dict = BuildUrlResponseBody().Set(
      "signedTokens", base::Value::List().Append(cbr::test::kInvalidBase64));

  // Act
  const auto result = ParseVerifyAndUnblindTokens(dict, cbr::test::GetTokens(),
                                                  cbr::test::GetBlindedTokens(),
                                                  cbr::test::GetPublicKey());

  // Assert
  EXPECT_FALSE(result.has_value());
}

}  // namespace qorai_ads
