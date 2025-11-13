/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_COMMON_FEATURES_H_
#define QORAI_COMPONENTS_QORAI_WALLET_COMMON_FEATURES_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace qorai_wallet::features {

BASE_DECLARE_FEATURE(kNativeQoraiWalletFeature);

BASE_DECLARE_FEATURE(kQoraiWalletBitcoinFeature);
extern const base::FeatureParam<int> kBitcoinRpcThrottle;
extern const base::FeatureParam<bool> kBitcoinTestnetDiscovery;
BASE_DECLARE_FEATURE(kQoraiWalletBitcoinImportFeature);
BASE_DECLARE_FEATURE(kQoraiWalletBitcoinLedgerFeature);

BASE_DECLARE_FEATURE(kQoraiWalletZCashFeature);
// Adds shielded operations support for Z Cash
extern const base::FeatureParam<bool> kZCashShieldedTransactionsEnabled;

BASE_DECLARE_FEATURE(kQoraiWalletPolkadotFeature);

BASE_DECLARE_FEATURE(kQoraiWalletCardanoFeature);
extern const base::FeatureParam<int> kCardanoRpcThrottle;
extern const base::FeatureParam<bool> kCardanoDAppSupport;

BASE_DECLARE_FEATURE(kQoraiWalletAnkrBalancesFeature);
BASE_DECLARE_FEATURE(kQoraiWalletTransactionSimulationsFeature);

}  // namespace qorai_wallet::features

#endif  // QORAI_COMPONENTS_QORAI_WALLET_COMMON_FEATURES_H_
