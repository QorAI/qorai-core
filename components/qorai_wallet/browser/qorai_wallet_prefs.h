/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_PREFS_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_PREFS_H_

class PrefService;
class PrefRegistrySimple;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace qorai_wallet {

void RegisterLocalStatePrefs(PrefRegistrySimple* registry);
void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);
void RegisterLocalStatePrefsForMigration(PrefRegistrySimple* registry);
void RegisterProfilePrefsForMigration(
    user_prefs::PrefRegistrySyncable* registry);
void ClearJsonRpcServiceProfilePrefs(PrefService* prefs);
void ClearKeyringServiceProfilePrefs(PrefService* prefs);
void ClearQoraiWalletServicePrefs(PrefService* prefs);
void MigrateObsoleteProfilePrefs(PrefService* prefs);
void MigrateCryptoWalletsPrefToQoraiWallet(PrefService* prefs);

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_PREFS_H_
