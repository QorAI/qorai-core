/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// npm run test -- qorai_unit_tests --filter=QoraiAds*

#include "qorai/components/qorai_ads/core/internal/account/account_util.h"

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/ads_core/ads_core_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

namespace qorai_ads {

class QoraiAdsAccountUtilTest : public test::TestBase {};

TEST_F(QoraiAdsAccountUtilTest, AlwaysAllowDepositsForRewardsUser) {
  // Act & Assert
  for (int i = 0; i < static_cast<int>(mojom::AdType::kMaxValue); ++i) {
    for (int j = 0; j < static_cast<int>(mojom::ConfirmationType::kMaxValue);
         ++j) {
      EXPECT_TRUE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                     static_cast<mojom::AdType>(i),
                                     static_cast<mojom::ConfirmationType>(j)));
    }
  }
}

TEST_F(QoraiAdsAccountUtilTest, AllowInlineContentAdDepositsForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  for (int i = 0; i < static_cast<int>(mojom::ConfirmationType::kMaxValue);
       ++i) {
    EXPECT_TRUE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                   mojom::AdType::kInlineContentAd,
                                   static_cast<mojom::ConfirmationType>(i)));
  }
}

TEST_F(
    QoraiAdsAccountUtilTest,
    DoNotAllowInlineContentAdDepositsForNonRewardsUserIfOptedOutOfQoraiNews) {
  // Arrange
  test::DisableQoraiRewards();

  test::OptOutOfQoraiNewsAds();

  // Act & Assert
  for (int i = 0; i < static_cast<int>(mojom::ConfirmationType::kMaxValue);
       ++i) {
    EXPECT_FALSE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                    mojom::AdType::kInlineContentAd,
                                    static_cast<mojom::ConfirmationType>(i)));
  }
}

TEST_F(QoraiAdsAccountUtilTest,
       AllowPromotedContentAdDepositsForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  for (int i = 0; i < static_cast<int>(mojom::ConfirmationType::kMaxValue);
       ++i) {
    EXPECT_TRUE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                   mojom::AdType::kPromotedContentAd,
                                   static_cast<mojom::ConfirmationType>(i)));
  }
}

TEST_F(
    QoraiAdsAccountUtilTest,
    DoNotAllowPromotedContentAdDepositsForNonRewardsUserIfOptedOutOfQoraiNews) {
  // Arrange
  test::DisableQoraiRewards();

  test::OptOutOfQoraiNewsAds();

  // Act & Assert
  for (int i = 0; i < static_cast<int>(mojom::ConfirmationType::kMaxValue);
       ++i) {
    EXPECT_FALSE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                    mojom::AdType::kPromotedContentAd,
                                    static_cast<mojom::ConfirmationType>(i)));
  }
}

TEST_F(QoraiAdsAccountUtilTest, AllowNewTabPageAdDepositsForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  for (int i = 0; i < static_cast<int>(mojom::ConfirmationType::kMaxValue);
       ++i) {
    EXPECT_TRUE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                   mojom::AdType::kNewTabPageAd,
                                   static_cast<mojom::ConfirmationType>(i)));
  }
}

TEST_F(
    QoraiAdsAccountUtilTest,
    DoNotAllowNewTabPageAdDepositsForNonRewardsUserIfOptedOutOfNewTabPageAds) {
  // Arrange
  test::DisableQoraiRewards();

  test::OptOutOfNewTabPageAds();

  // Act & Assert
  for (int i = 0; i < static_cast<int>(mojom::ConfirmationType::kMaxValue);
       ++i) {
    EXPECT_FALSE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                    mojom::AdType::kNewTabPageAd,
                                    static_cast<mojom::ConfirmationType>(i)));
  }
}

TEST_F(
    QoraiAdsAccountUtilTest,
    DoNotAllowNewTabPageAdDepositsForNonRewardsUserWhenMetricTypeIsDisabled) {
  // Arrange
  test::DisableQoraiRewards();

  UpdateReportMetricState(test::kCreativeInstanceId,
                          mojom::NewTabPageAdMetricType::kDisabled);

  // Act & Assert
  for (int i = 0; i < static_cast<int>(mojom::ConfirmationType::kMaxValue);
       ++i) {
    EXPECT_FALSE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                    mojom::AdType::kNewTabPageAd,
                                    static_cast<mojom::ConfirmationType>(i)));
  }
}

TEST_F(QoraiAdsAccountUtilTest,
       DoNotAllowNotificationAdDepositsForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  for (int i = 0; i < static_cast<int>(mojom::ConfirmationType::kMaxValue);
       ++i) {
    EXPECT_FALSE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                    mojom::AdType::kNotificationAd,
                                    static_cast<mojom::ConfirmationType>(i)));
  }
}

TEST_F(QoraiAdsAccountUtilTest,
       OnlyAllowSearchResultAdConversionDepositForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  for (int i = 0; i < static_cast<int>(mojom::ConfirmationType::kMaxValue);
       ++i) {
    const auto confirmation_type = static_cast<mojom::ConfirmationType>(i);

    const bool is_allowed_to_deposit =
        IsAllowedToDeposit(test::kCreativeInstanceId,
                           mojom::AdType::kSearchResultAd, confirmation_type);

    if (confirmation_type == mojom::ConfirmationType::kConversion) {
      EXPECT_TRUE(is_allowed_to_deposit);
    } else {
      EXPECT_FALSE(is_allowed_to_deposit);
    }
  }
}

}  // namespace qorai_ads
