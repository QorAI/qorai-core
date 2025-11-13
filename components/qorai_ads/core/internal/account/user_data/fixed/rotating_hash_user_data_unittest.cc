/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/rotating_hash_user_data.h"

#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_info.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transactions_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsRotatingHashUserDataTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    AdvanceClockTo(test::TimeFromUTCString("2 June 2022 11:00"));
  }
};

TEST_F(QoraiAdsRotatingHashUserDataTest, BuildRotatingHashUserData) {
  // Arrange
  test::MockDeviceId();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "rotatingHash": "j9D7eKSoPLYNfxkG2Mx+SbgKJ9hcKg1QwDB8B5qxlpk="
                    })JSON"),
            BuildRotatingHashUserData(transaction));
}

TEST_F(QoraiAdsRotatingHashUserDataTest,
       DoNotBuildRotatingHashUserDataForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  test::MockDeviceId();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_THAT(BuildRotatingHashUserData(transaction), ::testing::IsEmpty());
}

TEST_F(QoraiAdsRotatingHashUserDataTest,
       DoNotBuildRotatingHashUserDataIfMissingDeviceId) {
  // Arrange
  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_THAT(BuildRotatingHashUserData(transaction), ::testing::IsEmpty());
}

}  // namespace qorai_ads
