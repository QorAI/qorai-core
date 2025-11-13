/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/segment_user_data.h"

#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transaction_info.h"
#include "qorai/components/qorai_ads/core/internal/account/transactions/transactions_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsSegmentUserDataTest : public test::TestBase {};

TEST_F(QoraiAdsSegmentUserDataTest, BuildSegmentUserData) {
  // Arrange
  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "segment": "untargeted"
                    })JSON"),
            BuildSegmentUserData(transaction));
}

TEST_F(QoraiAdsSegmentUserDataTest, DoNotBuildSearchResultAdSegmentUserData) {
  // Arrange
  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kSearchResultAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_THAT(BuildSegmentUserData(transaction), ::testing::IsEmpty());
}

TEST_F(QoraiAdsSegmentUserDataTest,
       DoNotBuildSegmentUserDataForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_THAT(BuildSegmentUserData(transaction), ::testing::IsEmpty());
}

TEST_F(QoraiAdsSegmentUserDataTest, DoNotBuildSegmentUserDataIfNoSegment) {
  // Arrange
  TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/false);
  transaction.segment = "";

  // Act & Assert
  EXPECT_THAT(BuildSegmentUserData(transaction), ::testing::IsEmpty());
}

}  // namespace qorai_ads
