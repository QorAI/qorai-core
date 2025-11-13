/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/prefs/pref_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsRedeemPaymentTokensUtilTest : public test::TestBase {};

TEST_F(QoraiAdsRedeemPaymentTokensUtilTest, SetNextTokenRedemptionAt) {
  // Arrange
  SetNextTokenRedemptionAt(test::DistantFuture());

  // Act & Assert
  EXPECT_FALSE(
      GetProfileTimePref(prefs::kNextPaymentTokenRedemptionAt).is_null());
}

TEST_F(QoraiAdsRedeemPaymentTokensUtilTest, ScheduleNextTokenRedemptionAt) {
  // Act & Assert
  EXPECT_FALSE(ScheduleNextTokenRedemptionAt().is_null());
}

TEST_F(QoraiAdsRedeemPaymentTokensUtilTest,
       CalculateDelayBeforeRedeemingTokens) {
  // Arrange
  SetNextTokenRedemptionAt(test::Now() + base::Days(1));

  // Act & Assert
  EXPECT_EQ(base::Days(1), CalculateDelayBeforeRedeemingTokens());
}

TEST_F(QoraiAdsRedeemPaymentTokensUtilTest,
       CalculateDelayBeforeRedeemingTokensIfHasNotPreviouslyRedeemedTokens) {
  // Act & Assert
  EXPECT_FALSE(ScheduleNextTokenRedemptionAt().is_null());
}

TEST_F(QoraiAdsRedeemPaymentTokensUtilTest,
       CalculateDelayBeforeRedeemingTokensIfShouldHaveRedeemedTokensInThePast) {
  // Arrange
  SetNextTokenRedemptionAt(test::DistantPast());

  // Act & Assert
  EXPECT_EQ(base::Minutes(1), CalculateDelayBeforeRedeemingTokens());
}

TEST_F(QoraiAdsRedeemPaymentTokensUtilTest,
       CalculateMinimumDelayBeforeRedeemingTokens) {
  // Arrange
  SetNextTokenRedemptionAt(test::Now() + base::Milliseconds(1));

  // Act & Assert
  EXPECT_EQ(base::Minutes(1), CalculateDelayBeforeRedeemingTokens());
}

}  // namespace qorai_ads
