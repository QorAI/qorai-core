/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/statement/ads_received_util.h"

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/account/transactions/transactions_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsAdsReceivedUtilTest : public test::TestBase {};

TEST_F(
    QoraiAdsAdsReceivedUtilTest,
    GetAdsReceivedForDateRangeWhenUserHasJoinedQoraiRewardsAndNotConnectedWallet) {
  // Arrange
  test::DisconnectExternalQoraiRewardsWallet();

  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  TransactionList transactions;

  const TransactionInfo transaction_1 = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_1);

  AdvanceClockTo(test::TimeFromString("25 December 2020"));

  const TransactionInfo transaction_2 = test::BuildUnreconciledTransaction(
      /*value=*/0.0, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_2);

  const TransactionInfo transaction_3 = test::BuildUnreconciledTransaction(
      /*value=*/0.03, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_3);

  const base::Time from_time = test::Now();

  AdvanceClockTo(test::TimeFromString("1 January 2021"));

  const TransactionInfo transaction_4 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_4);

  TransactionInfo transaction_5 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNewTabPageAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_5);

  TransactionInfo transaction_6 = test::BuildUnreconciledTransaction(
      /*value=*/0.0, mojom::AdType::kInlineContentAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_6);

  // Act
  const size_t ads_received = GetAdsReceivedForDateRange(
      transactions, from_time, test::DistantFuture());

  // Assert
  EXPECT_EQ(4U, ads_received);
}

TEST_F(
    QoraiAdsAdsReceivedUtilTest,
    GetAdsReceivedForDateRangeWhenUserHasJoinedQoraiRewardsAndConnectedWallet) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  TransactionList transactions;

  const TransactionInfo transaction_1 = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_1);

  AdvanceClockTo(test::TimeFromString("25 December 2020"));

  const TransactionInfo transaction_2 = test::BuildUnreconciledTransaction(
      /*value=*/0.0, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_2);

  const TransactionInfo transaction_3 = test::BuildUnreconciledTransaction(
      /*value=*/0.03, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_3);

  const base::Time from_time = test::Now();

  AdvanceClockTo(test::TimeFromString("1 January 2021"));

  const TransactionInfo transaction_4 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_4);

  TransactionInfo transaction_5 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNewTabPageAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_5);

  TransactionInfo transaction_6 = test::BuildUnreconciledTransaction(
      /*value=*/0.0, mojom::AdType::kInlineContentAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_6);

  // Act
  const size_t ads_received = GetAdsReceivedForDateRange(
      transactions, from_time, test::DistantFuture());

  // Assert
  EXPECT_EQ(3U, ads_received);
}

TEST_F(QoraiAdsAdsReceivedUtilTest, DoNotGetAdsSummaryForDateRange) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  TransactionList transactions;

  const TransactionInfo transaction_1 = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_1);

  const TransactionInfo transaction_2 = test::BuildUnreconciledTransaction(
      /*value=*/0.0, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*should_generate_random_uuids=*/true);
  transactions.push_back(transaction_2);

  AdvanceClockTo(test::TimeFromString("1 January 2021"));

  // Act
  const size_t ads_received = GetAdsReceivedForDateRange(
      transactions, /*from_time=*/test::Now(), test::DistantFuture());

  // Assert
  EXPECT_EQ(0U, ads_received);
}

TEST_F(QoraiAdsAdsReceivedUtilTest, GetAdsSummaryForNoTransactions) {
  // Act
  const size_t ads_received = GetAdsReceivedForDateRange(
      /*transactions=*/{}, test::DistantPast(), test::DistantFuture());

  // Assert
  EXPECT_EQ(0U, ads_received);
}

}  // namespace qorai_ads
