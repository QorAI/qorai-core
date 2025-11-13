/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/confirmations/user_data_builder/fixed/confirmation_fixed_user_data_builder.h"

#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/confirmations/user_data_builder/confirmation_user_data_builder_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_info.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transactions_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsFixedUserDataBuilderTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    test::MockConfirmationUserData();

    AdvanceClockTo(test::TimeFromUTCString("November 18 2020 12:34:56.789"));
  }
};

TEST_F(QoraiAdsFixedUserDataBuilderTest, BuildFixedUserData) {
  // Arrange
  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "buildChannel": "release",
                      "catalog": [
                        {
                          "id": "29e5c8bc0ba319069980bb390d8e8f9b58c05a20"
                        }
                      ],
                      "createdAtTimestamp": "2020-11-18T12:00:00.000Z",
                      "platform": "windows",
                      "rotatingHash": "I6KM54gXOrWqRHyrD518LmhePLHpIk4KSgCKOl0e3sc=",
                      "segment": "untargeted",
                      "studies": [],
                      "versionNumber": "1.2.3.4"
                    })JSON"),
            BuildFixedUserData(transaction));
}

TEST_F(QoraiAdsFixedUserDataBuilderTest,
       DoNotBuildFixedUserDataForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_THAT(BuildFixedUserData(transaction), ::testing::IsEmpty());
}

}  // namespace qorai_ads
