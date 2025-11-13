/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/deposits/non_cash_deposit.h"

#include "base/test/mock_callback.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsNonCashDepositTest : public test::TestBase {};

TEST_F(QoraiAdsNonCashDepositTest, GetValue) {
  // Arrange
  NonCashDeposit deposit;

  // Act & Assert
  base::MockCallback<GetDepositCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true, /*value=*/0.0));
  deposit.GetValue(test::kCreativeInstanceId, callback.Get());
}

}  // namespace qorai_ads
