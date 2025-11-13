/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/confirmations/non_reward/non_reward_confirmation_util.h"

#include "qorai/components/qorai_ads/core/internal/account/confirmations/confirmation_info.h"
#include "qorai/components/qorai_ads/core/internal/account/confirmations/user_data_builder/confirmation_user_data_builder.h"
#include "qorai/components/qorai_ads/core/internal/account/confirmations/user_data_builder/confirmation_user_data_builder_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_info.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transactions_test_util.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsNonRewardConfirmationUtilTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    test::MockConfirmationUserData();
  }
};

TEST_F(QoraiAdsNonRewardConfirmationUtilTest, BuildNonRewardConfirmation) {
  // Arrange
  test::DisableQoraiRewards();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/false);

  // Act
  std::optional<ConfirmationInfo> confirmation =
      BuildNonRewardConfirmation(transaction, /*user_data=*/{});
  ASSERT_TRUE(confirmation);

  // Assert
  EXPECT_THAT(
      *confirmation,
      ::testing::FieldsAre(test::kTransactionId, test::kCreativeInstanceId,
                           mojom::ConfirmationType::kViewedImpression,
                           mojom::AdType::kNotificationAd,
                           /*created_at*/ test::Now(),
                           /*reward*/ std::nullopt, UserDataInfo{}));
}

TEST_F(QoraiAdsNonRewardConfirmationUtilTest,
       DISABLED_DoNotBuildNonRewardConfirmationWithInvalidTransaction) {
  // Arrange
  test::DisableQoraiRewards();

  // Act
  std::optional<ConfirmationInfo> confirmation =
      BuildNonRewardConfirmation(/*transaction=*/{}, /*user_data=*/{});
  ASSERT_TRUE(confirmation);

  // Assert
  EXPECT_DEATH_IF_SUPPORTED(*confirmation,
                            "Check failed: transaction.IsValid*");
}

TEST_F(QoraiAdsNonRewardConfirmationUtilTest,
       DISABLED_DoNotBuildNonRewardConfirmationForRewardsUser) {
  // Arrange
  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/false);

  // Act
  std::optional<ConfirmationInfo> confirmation =
      BuildNonRewardConfirmation(transaction, /*user_data=*/{});
  ASSERT_TRUE(confirmation);

  // Assert
  EXPECT_DEATH_IF_SUPPORTED(*confirmation,
                            "Check failed: !UserHasJoinedQoraiRewards*");
}

}  // namespace qorai_ads
