/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/statement/statement_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsAccountFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kAccountStatementFeature));
}

TEST(QoraiAdsAccountFeatureTest, NextPaymentDay) {
  // Act & Assert
  EXPECT_EQ(7, kNextPaymentDay.Get());
}

TEST(QoraiAdsAccountFeatureTest, MinEstimatedEarningsMultiplier) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(0.8, kMinEstimatedEarningsMultiplier.Get());
}

}  // namespace qorai_ads
