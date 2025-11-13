/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_confirmation/reward/redeem_reward_confirmation_util.h"

#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_tokens_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsRedeemRewardConfirmationUtilTest : public test::TestBase {};

TEST_F(QoraiAdsRedeemRewardConfirmationUtilTest, AddPaymentToken) {
  // Arrange
  const PaymentTokenInfo payment_token = test::BuildPaymentToken();

  // Act & Assert
  EXPECT_TRUE(MaybeAddPaymentToken(payment_token));
}

TEST_F(QoraiAdsRedeemRewardConfirmationUtilTest,
       DoNotAddDuplicatePaymentToken) {
  // Arrange
  const PaymentTokenInfo payment_token = test::BuildPaymentToken();
  ASSERT_TRUE(MaybeAddPaymentToken(payment_token));

  // Act & Assert
  EXPECT_FALSE(MaybeAddPaymentToken(payment_token));
}
TEST_F(QoraiAdsRedeemRewardConfirmationUtilTest, LogPaymentTokenStatus) {
  // Act & Assert
  EXPECT_CALL(ads_client_mock_, Log);

  LogPaymentTokenStatus();
}

}  // namespace qorai_ads
