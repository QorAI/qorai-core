/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_wallet/browser/qorai_wallet_prefs.h"

#include <vector>

#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/testing_pref_service.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace qorai_wallet {

TEST(QoraiWalletPrefsTest, MigratesCryptoWalletsPrefToQoraiWallet) {
  TestingPrefServiceSimple prefs;
  prefs.registry()->RegisterIntegerPref(
      kDefaultEthereumWallet,
      static_cast<int>(mojom::DefaultWallet::AskDeprecated));  // default unused

  // Changes CryptoWalletsDeprecated to QoraiWalletPreferExtension
  prefs.SetInteger(
      kDefaultEthereumWallet,
      static_cast<int>(mojom::DefaultWallet::CryptoWalletsDeprecated));
  MigrateCryptoWalletsPrefToQoraiWallet(&prefs);
  EXPECT_EQ(prefs.GetInteger(kDefaultEthereumWallet),
            static_cast<int>(mojom::DefaultWallet::QoraiWalletPreferExtension));

  // These values should not change after migration
  const std::vector<mojom::DefaultWallet> noChangeValues = {
      mojom::DefaultWallet::QoraiWallet,
      mojom::DefaultWallet::QoraiWalletPreferExtension,
      mojom::DefaultWallet::None};

  for (const auto wallet : noChangeValues) {
    prefs.SetInteger(kDefaultEthereumWallet, static_cast<int>(wallet));
    MigrateCryptoWalletsPrefToQoraiWallet(&prefs);
    EXPECT_EQ(prefs.GetInteger(kDefaultEthereumWallet),
              static_cast<int>(wallet))
        << "Wallet type " << static_cast<int>(wallet)
        << " should remain unchanged.";
  }
}

}  // namespace qorai_wallet
