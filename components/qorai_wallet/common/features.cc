/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_wallet/common/features.h"

#include "base/feature_list.h"
#include "qorai/components/qorai_wallet/common/buildflags.h"
#include "build/build_config.h"

namespace qorai_wallet::features {

BASE_FEATURE(kNativeQoraiWalletFeature,
             "NativeQoraiWallet",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiWalletBitcoinFeature,
             "QoraiWalletBitcoin",
             base::FEATURE_ENABLED_BY_DEFAULT);
const base::FeatureParam<int> kBitcoinRpcThrottle{&kQoraiWalletBitcoinFeature,
                                                  "rpc_throttle", 1};
const base::FeatureParam<bool> kBitcoinTestnetDiscovery{
    &kQoraiWalletBitcoinFeature, "testnet_discovery", false};

BASE_FEATURE(kQoraiWalletBitcoinImportFeature,
             "QoraiWalletBitcoinImport",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiWalletBitcoinLedgerFeature,
             "QoraiWalletBitcoinLedger",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiWalletZCashFeature,
             "QoraiWalletZCash",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiWalletPolkadotFeature,
             "QoraiWalletPolkadot",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiWalletCardanoFeature,
             "QoraiWalletCardano",
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
             base::FEATURE_ENABLED_BY_DEFAULT
#else
             base::FEATURE_DISABLED_BY_DEFAULT

#endif
);
const base::FeatureParam<int> kCardanoRpcThrottle{&kQoraiWalletCardanoFeature,
                                                  "rpc_throttle", 1};
const base::FeatureParam<bool> kCardanoDAppSupport{
    &kQoraiWalletCardanoFeature, "cardano_dapp_support", false};

const base::FeatureParam<bool> kZCashShieldedTransactionsEnabled{
    &kQoraiWalletZCashFeature, "zcash_shielded_transactions_enabled", true};

BASE_FEATURE(kQoraiWalletAnkrBalancesFeature,
             "QoraiWalletAnkrBalances",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiWalletTransactionSimulationsFeature,
             "QoraiWalletTransactionSimulations",
             base::FEATURE_DISABLED_BY_DEFAULT);
}  // namespace qorai_wallet::features
