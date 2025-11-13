/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/wallet/wallet_util.h"

#include "qorai/components/qorai_ads/core/internal/account/wallet/wallet_info.h"
#include "qorai/components/qorai_ads/core/internal/account/wallet/wallet_test_constants.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsWalletUtilTest, CreateWalletFromRecoverySeed) {
  // Act
  std::optional<WalletInfo> wallet = CreateWalletFromRecoverySeed(
      test::kWalletPaymentId, test::kWalletRecoverySeedBase64);
  ASSERT_TRUE(wallet);

  // Assert
  EXPECT_THAT(*wallet, ::testing::FieldsAre(test::kWalletPaymentId,
                                            test::kWalletPublicKey,
                                            test::kWalletSecretKey));
}

TEST(QoraiAdsWalletUtilTest, DoNotCreateWalletFromInvalidRecoverySeed) {
  // Act & Assert
  EXPECT_FALSE(CreateWalletFromRecoverySeed(test::kWalletPaymentId,
                                            test::kInvalidWalletRecoverySeed));
}

}  // namespace qorai_ads
