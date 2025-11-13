/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/summary_user_data_util.h"

#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_tokens_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsSummaryUserDataUtilTest, BuildBucketsIfNoPaymentTokens) {
  // Act & Assert
  EXPECT_THAT(BuildAdTypeBuckets(/*payment_tokens=*/{}), ::testing::IsEmpty());
}

TEST(QoraiAdsSummaryUserDataUtilTest, BuildBuckets) {
  // Arrange
  PaymentTokenList payment_tokens;

  const PaymentTokenInfo payment_token_1 =
      test::BuildPaymentToken(mojom::ConfirmationType::kViewedImpression,
                              mojom::AdType::kNotificationAd);
  payment_tokens.push_back(payment_token_1);

  const PaymentTokenInfo payment_token_2 =
      test::BuildPaymentToken(mojom::ConfirmationType::kViewedImpression,
                              mojom::AdType::kNotificationAd);
  payment_tokens.push_back(payment_token_2);

  const PaymentTokenInfo payment_token_3 = test::BuildPaymentToken(
      mojom::ConfirmationType::kClicked, mojom::AdType::kNotificationAd);
  payment_tokens.push_back(payment_token_3);

  const PaymentTokenInfo payment_token_4 =
      test::BuildPaymentToken(mojom::ConfirmationType::kViewedImpression,
                              mojom::AdType::kInlineContentAd);
  payment_tokens.push_back(payment_token_4);

  // Act
  const AdTypeBucketMap ad_type_buckets = BuildAdTypeBuckets(payment_tokens);

  // Assert
  const AdTypeBucketMap expected_ad_type_buckets = {
      {mojom::AdType::kNotificationAd,
       {{mojom::ConfirmationType::kClicked, 1},
        {mojom::ConfirmationType::kViewedImpression, 2}}},
      {mojom::AdType::kInlineContentAd,
       {{mojom::ConfirmationType::kViewedImpression, 1}}}};
  EXPECT_EQ(expected_ad_type_buckets, ad_type_buckets);
}

}  // namespace qorai_ads
