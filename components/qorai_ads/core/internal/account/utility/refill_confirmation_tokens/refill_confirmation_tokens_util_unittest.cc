/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/utility/refill_confirmation_tokens/refill_confirmation_tokens_util.h"

#include <cstddef>

#include "qorai/components/qorai_ads/core/internal/account/tokens/confirmation_tokens/confirmation_tokens_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/tokens_feature.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsRefillConfirmationTokensUtilTest : public test::TestBase {};

TEST_F(QoraiAdsRefillConfirmationTokensUtilTest,
       ShouldRefillConfirmationTokens) {
  // Arrange
  const size_t count = kMinConfirmationTokens.Get() - 1;
  test::RefillConfirmationTokens(count);

  // Act & Assert
  EXPECT_TRUE(ShouldRefillConfirmationTokens());
}

TEST_F(QoraiAdsRefillConfirmationTokensUtilTest,
       ShouldNotRefillConfirmationTokens) {
  // Arrange
  const size_t count = kMinConfirmationTokens.Get();
  test::RefillConfirmationTokens(count);

  // Act & Assert
  EXPECT_FALSE(ShouldRefillConfirmationTokens());
}

TEST_F(QoraiAdsRefillConfirmationTokensUtilTest,
       CalculateAmountOfConfirmationTokensToRefill) {
  // Arrange
  test::RefillConfirmationTokens(/*count=*/10);

  // Act & Assert
  EXPECT_EQ(kMaxConfirmationTokens.Get() - 10,
            CalculateAmountOfConfirmationTokensToRefill());
}

}  // namespace qorai_ads
