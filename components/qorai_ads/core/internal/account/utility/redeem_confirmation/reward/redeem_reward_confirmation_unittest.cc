/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_confirmation/reward/redeem_reward_confirmation.h"

#include <optional>

#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_ads/core/internal/account/confirmations/confirmation_info.h"
#include "qorai/components/qorai_ads/core/internal/account/confirmations/reward/reward_confirmation_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/confirmations/reward/reward_confirmation_util.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/tokens/confirmation_tokens/confirmation_tokens_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/tokens/token_generator_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_confirmation/redeem_confirmation_delegate_mock.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_confirmation/reward/redeem_reward_confirmation_feature.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_confirmation/reward/redeem_reward_confirmation_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/create_reward_confirmation_url_request_builder_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/create_reward_confirmation_url_request_builder_util.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/fetch_payment_token_url_request_builder_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_constants.h"
#include "net/http/http_status_code.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsRedeemRewardConfirmationTest : public test::TestBase {
 protected:
  RedeemConfirmationDelegateMock delegate_mock_;
  base::WeakPtrFactory<RedeemConfirmationDelegateMock>
      confirmation_delegate_weak_factory_{&delegate_mock_};
};

TEST_F(QoraiAdsRedeemRewardConfirmationTest, Redeem) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, test::BuildFetchPaymentTokenUrlResponseBody()}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation(*confirmation));

  EXPECT_CALL(delegate_mock_, OnFailedToRedeemConfirmation).Times(0);

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest, RetryRedeemingIfNoIssuers) {
  // Arrange
  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/true);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/true));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  EXPECT_FALSE(HasPendingTasks());
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       RedeemIfConfirmationWasPreviouslyCreated) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, test::BuildFetchPaymentTokenUrlResponseBody()}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation(*confirmation));

  EXPECT_CALL(delegate_mock_, OnFailedToRedeemConfirmation).Times(0);

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingForFetchPaymentTokenHttpNotFoundResponse) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_NOT_FOUND, net::GetHttpReasonPhrase(net::HTTP_NOT_FOUND)}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingForFetchPaymentTokenHttpBadRequestResponse) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_BAD_REQUEST,
         net::GetHttpReasonPhrase(net::HTTP_BAD_REQUEST)}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       RetryRedeemingForFetchPaymentTokenHttpAcceptedResponse) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_ACCEPTED, test::BuildFetchPaymentTokenUrlResponseBody()}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/true));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       RetryRedeemingForFetchPaymentTokenHttpInternalServerErrorResponse) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_INTERNAL_SERVER_ERROR,
         net::GetHttpReasonPhrase(net::HTTP_INTERNAL_SERVER_ERROR)}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/true));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       RetryRedeemingIfInvalidResponseBody) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, /*response_body=*/test::kMalformedJson}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/true));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyIdIsMissing) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "bPE1QE65mkIgytffeu7STOfly+x10BXCGuk5pVlOHQU=",
                "batchProof" : "FWTZ5fOYITYlMWMYaxg254QWs+Pmd0dHzoor0mzIlQ8tWHagc7jm7UVJykqIo+ZSM+iK29mPuWJxPHpG4HypBw==",
                "signedTokens" : [
                  "DHe4S37Cn1WaTbCC+ytiNTB2s5H0vcLzVcRgzRoO3lU="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyIdDoesNotMatchConfirmationId) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "393abadc-e9ae-4aac-a321-3307e0d527c6",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "bPE1QE65mkIgytffeu7STOfly+x10BXCGuk5pVlOHQU=",
                "batchProof" : "FWTZ5fOYITYlMWMYaxg254QWs+Pmd0dHzoor0mzIlQ8tWHagc7jm7UVJykqIo+ZSM+iK29mPuWJxPHpG4HypBw==",
                "signedTokens" : [
                  "DHe4S37Cn1WaTbCC+ytiNTB2s5H0vcLzVcRgzRoO3lU="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyPaymentTokenIsMissing) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6"
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyPublicKeyIsMissing) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "batchProof" : "FWTZ5fOYITYlMWMYaxg254QWs+Pmd0dHzoor0mzIlQ8tWHagc7jm7UVJykqIo+ZSM+iK29mPuWJxPHpG4HypBw==",
                "signedTokens" : [
                  "DHe4S37Cn1WaTbCC+ytiNTB2s5H0vcLzVcRgzRoO3lU="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyPublicKeyIsInvalid) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "INVALID",
                "batchProof" : "FWTZ5fOYITYlMWMYaxg254QWs+Pmd0dHzoor0mzIlQ8tWHagc7jm7UVJykqIo+ZSM+iK29mPuWJxPHpG4HypBw==",
                "signedTokens" : [
                  "DHe4S37Cn1WaTbCC+ytiNTB2s5H0vcLzVcRgzRoO3lU="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       RetryRedeemingIfPublicKeyDoesNotExist) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "paymentToken" : {
                "publicKey" : "Si61i/8huYsx01ED6SZIOvDuD6GQV5LAi2CMu3NAVCQ=",
                "batchProof" : "FWTZ5fOYITYlMWMYaxg254QWs+Pmd0dHzoor0mzIlQ8tWHagc7jm7UVJykqIo+ZSM+iK29mPuWJxPHpG4HypBw==",
                "signedTokens" : [
                  "DHe4S37Cn1WaTbCC+ytiNTB2s5H0vcLzVcRgzRoO3lU="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/true));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyBatchProofIsMissing) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "bPE1QE65mkIgytffeu7STOfly+x10BXCGuk5pVlOHQU=",
                "signedTokens" : [
                  "DHe4S37Cn1WaTbCC+ytiNTB2s5H0vcLzVcRgzRoO3lU="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyBatchProofIsInvalid) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "bPE1QE65mkIgytffeu7STOfly+x10BXCGuk5pVlOHQU=",
                "batchProof" : "INVALID",
                "signedTokens" : [
                  "DHe4S37Cn1WaTbCC+ytiNTB2s5H0vcLzVcRgzRoO3lU="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodySignedTokensAreMissing) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "bPE1QE65mkIgytffeu7STOfly+x10BXCGuk5pVlOHQU=",
                "batchProof" : "FWTZ5fOYITYlMWMYaxg254QWs+Pmd0dHzoor0mzIlQ8tWHagc7jm7UVJykqIo+ZSM+iK29mPuWJxPHpG4HypBw=="
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodySignedTokenIsInvalid) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "bPE1QE65mkIgytffeu7STOfly+x10BXCGuk5pVlOHQU=",
                "batchProof" : "FWTZ5fOYITYlMWMYaxg254QWs+Pmd0dHzoor0mzIlQ8tWHagc7jm7UVJykqIo+ZSM+iK29mPuWJxPHpG4HypBw=="
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfFailedToVerifyAndUnblindTokens) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "bPE1QE65mkIgytffeu7STOfly+x10BXCGuk5pVlOHQU=",
                "batchProof" : "INVALID",
                "signedTokens" : [
                  "DHe4S37Cn1WaTbCC+ytiNTB2s5H0vcLzVcRgzRoO3lU="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(QoraiAdsRedeemRewardConfirmationTest, FetchPaymentTokenAfter) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(test::kTransactionId,
                                            test::kCredentialBase64Url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(test::kTransactionId),
       {{net::HTTP_OK, test::BuildFetchPaymentTokenUrlResponseBody()}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*should_generate_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  EXPECT_EQ(kFetchPaymentTokenAfter.Get(), NextPendingTaskDelay());
  EXPECT_EQ(1U, GetPendingTaskCount());
}

}  // namespace qorai_ads
