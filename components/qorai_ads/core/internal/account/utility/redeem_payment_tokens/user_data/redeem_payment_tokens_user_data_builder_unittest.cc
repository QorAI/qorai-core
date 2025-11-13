/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_payment_tokens/user_data/redeem_payment_tokens_user_data_builder.h"

#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_tokens_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsRedeemPaymentTokensUserDataBuilderTest : public test::TestBase {};

TEST_F(QoraiAdsRedeemPaymentTokensUserDataBuilderTest, BuildUserData) {
  // Act & Assert
  EXPECT_EQ(
      base::test::ParseJsonDict(R"JSON(
          {
            "platform": "windows",
            "totals": [
              {
                "ad_format": "ad_notification",
                "view": 2
              }
            ]
          })JSON"),
      BuildRedeemPaymentTokensUserData(test::BuildPaymentTokens(/*count=*/2)));
}

}  // namespace qorai_ads
