/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_wallet/browser/qorai_wallet_prefs.h"

#include <utility>

#include "base/check.h"
#include "base/values.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_constants.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_utils.h"
#include "qorai/components/qorai_wallet/browser/json_rpc_service.h"
#include "qorai/components/qorai_wallet/browser/keyring_service.h"
#include "qorai/components/qorai_wallet/browser/keyring_service_migrations.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/qorai_wallet/browser/tx_state_manager.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/common/pref_names.h"
#include "qorai/components/p3a_utils/feature_usage.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
#include "components/prefs/scoped_user_pref_update.h"

namespace qorai_wallet {

namespace {

constexpr int kDefaultWalletAutoLockMinutes = 10;

// Deprecated 12/2023.
constexpr char kQoraiWalletUserAssetEthContractAddressMigrated[] =
    "qorai.wallet.user.asset.eth_contract_address_migrated";
// Deprecated 12/2023.
constexpr char kQoraiWalletUserAssetsAddPreloadingNetworksMigrated[] =
    "qorai.wallet.user.assets.add_preloading_networks_migrated_3";
// Deprecated 12/2023.
constexpr char kQoraiWalletUserAssetsAddIsNFTMigrated[] =
    "qorai.wallet.user.assets.add_is_nft_migrated";
// Deprecated 12/2023.
constexpr char kQoraiWalletEthereumTransactionsCoinTypeMigrated[] =
    "qorai.wallet.ethereum_transactions.coin_type_migrated";
// Deprecated 12/2023.
constexpr char kQoraiWalletDeprecateEthereumTestNetworksMigrated[] =
    "qorai.wallet.deprecated_ethereum_test_networks_migrated";
// Deprecated 12/2023.
constexpr char kQoraiWalletUserAssetsAddIsSpamMigrated[] =
    "qorai.wallet.user.assets.add_is_spam_migrated";
// Deprecated 12/2023.
constexpr char kQoraiWalletUserAssetsAddIsERC1155Migrated[] =
    "qorai.wallet.user.assets.add_is_erc1155_migrated";

// Deprecated 07/2024
constexpr char kPinnedNFTAssetsMigrated[] = "qorai.wallet.user_pin_data";
// Deprecated 07/2024
constexpr char kAutoPinEnabledMigrated[] = "qorai.wallet.auto_pin_enabled";
// Deprecated 01/2025
constexpr char kQoraiWalletDefaultHiddenNetworksVersion[] =
    "qorai.wallet.user.assets.default_hidden_networks_version";
// Deprecated 02/2025
inline constexpr char kQoraiWalletCustomNetworksFantomMainnetMigrated[] =
    "qorai.wallet.custom_networks.fantom_mainnet_migrated";
// Deprecated 02/2025
inline constexpr char kQoraiWalletTransactions[] = "qorai.wallet.transactions";
// Deprecated 02/2025
inline constexpr char kQoraiWalletTransactionsDBFormatMigrated[] =
    "qorai.wallet.transactions_db_format_migrated";

base::Value::Dict GetDefaultSelectedNetworks() {
  base::Value::Dict selected_networks;
  selected_networks.Set(kEthereumPrefKey, mojom::kMainnetChainId);
  selected_networks.Set(kSolanaPrefKey, mojom::kSolanaMainnet);
  selected_networks.Set(kFilecoinPrefKey, mojom::kFilecoinMainnet);
  selected_networks.Set(kBitcoinPrefKey, mojom::kBitcoinMainnet);
  selected_networks.Set(kZCashPrefKey, mojom::kZCashMainnet);

  return selected_networks;
}

base::Value::Dict GetDefaultSelectedNetworksPerOrigin() {
  base::Value::Dict selected_networks;
  selected_networks.Set(kEthereumPrefKey, base::Value::Dict());
  selected_networks.Set(kSolanaPrefKey, base::Value::Dict());
  selected_networks.Set(kFilecoinPrefKey, base::Value::Dict());
  selected_networks.Set(kBitcoinPrefKey, base::Value::Dict());
  selected_networks.Set(kZCashPrefKey, base::Value::Dict());

  return selected_networks;
}

base::Value::Dict GetDefaultHiddenNetworks() {
  base::Value::Dict hidden_networks;

  base::Value::List eth_hidden;
  eth_hidden.Append(mojom::kSepoliaChainId);
  eth_hidden.Append(mojom::kLocalhostChainId);
  eth_hidden.Append(mojom::kFilecoinEthereumTestnetChainId);
  hidden_networks.Set(kEthereumPrefKey, std::move(eth_hidden));

  base::Value::List fil_hidden;
  fil_hidden.Append(mojom::kFilecoinTestnet);
  fil_hidden.Append(mojom::kLocalhostChainId);
  hidden_networks.Set(kFilecoinPrefKey, std::move(fil_hidden));

  base::Value::List sol_hidden;
  sol_hidden.Append(mojom::kSolanaDevnet);
  sol_hidden.Append(mojom::kSolanaTestnet);
  sol_hidden.Append(mojom::kLocalhostChainId);
  hidden_networks.Set(kSolanaPrefKey, std::move(sol_hidden));

  base::Value::List btc_hidden;
  btc_hidden.Append(mojom::kBitcoinTestnet);
  hidden_networks.Set(kBitcoinPrefKey, std::move(btc_hidden));

  base::Value::List zec_hidden;
  zec_hidden.Append(mojom::kZCashTestnet);
  hidden_networks.Set(kZCashPrefKey, std::move(zec_hidden));

  base::Value::List cardano_hidden;
  cardano_hidden.Append(mojom::kCardanoTestnet);
  hidden_networks.Set(kCardanoPrefKey, std::move(cardano_hidden));

  base::Value::List polkadot_hidden;
  polkadot_hidden.Append(mojom::kPolkadotTestnet);
  hidden_networks.Set(kPolkadotPrefKey, std::move(polkadot_hidden));

  return hidden_networks;
}

void RegisterProfilePrefsDeprecatedMigrationFlags(
    user_prefs::PrefRegistrySyncable* registry) {
  // Deprecated 12/2023
  registry->RegisterBooleanPref(kQoraiWalletUserAssetEthContractAddressMigrated,
                                false);
  // Deprecated 12/2023
  registry->RegisterBooleanPref(
      kQoraiWalletUserAssetsAddPreloadingNetworksMigrated, false);
  // Deprecated 12/2023
  registry->RegisterBooleanPref(kQoraiWalletUserAssetsAddIsNFTMigrated, false);
  // Deprecated 12/2023
  registry->RegisterBooleanPref(
      kQoraiWalletEthereumTransactionsCoinTypeMigrated, false);
  // Deprecated 12/2023
  registry->RegisterBooleanPref(
      kQoraiWalletDeprecateEthereumTestNetworksMigrated, false);
  // Deprecated 12/2023
  registry->RegisterBooleanPref(kQoraiWalletUserAssetsAddIsSpamMigrated, false);
  // Deprecated 12/2023
  registry->RegisterBooleanPref(kQoraiWalletUserAssetsAddIsERC1155Migrated,
                                false);
  // Deprecated 01/2025.
  registry->RegisterIntegerPref(kQoraiWalletDefaultHiddenNetworksVersion, 0);
  // Deprecated 02/2025.
  registry->RegisterBooleanPref(kQoraiWalletCustomNetworksFantomMainnetMigrated,
                                false);
  // Deprecated 02/2025
  registry->RegisterBooleanPref(kQoraiWalletTransactionsDBFormatMigrated,
                                false);
}

void RegisterDeprecatedIpfsPrefs(user_prefs::PrefRegistrySyncable* registry) {
  // Deprecated 05/2024
  registry->RegisterDictionaryPref(kPinnedNFTAssetsMigrated);
  // Deprecated 05/2024
  registry->RegisterBooleanPref(kAutoPinEnabledMigrated, false);
}

void ClearDeprecatedProfilePrefsMigrationFlags(PrefService* prefs) {
  // Deprecated 12/2023
  prefs->ClearPref(kQoraiWalletUserAssetEthContractAddressMigrated);
  // Deprecated 12/2023
  prefs->ClearPref(kQoraiWalletUserAssetsAddPreloadingNetworksMigrated);
  // Deprecated 12/2023
  prefs->ClearPref(kQoraiWalletUserAssetsAddIsNFTMigrated);
  // Deprecated 12/2023
  prefs->ClearPref(kQoraiWalletEthereumTransactionsCoinTypeMigrated);
  // Deprecated 12/2023
  prefs->ClearPref(kQoraiWalletDeprecateEthereumTestNetworksMigrated);
  // Deprecated 12/2023
  prefs->ClearPref(kQoraiWalletUserAssetsAddIsSpamMigrated);
  // Deprecated 12/2023
  prefs->ClearPref(kQoraiWalletUserAssetsAddIsERC1155Migrated);
  // Deprecated 01/2025.
  prefs->ClearPref(kQoraiWalletDefaultHiddenNetworksVersion);
  // Deprecated 02/2025.
  prefs->ClearPref(kQoraiWalletCustomNetworksFantomMainnetMigrated);
  // Deprecated 02/2025.
  prefs->ClearPref(kQoraiWalletTransactionsDBFormatMigrated);
}

}  // namespace

void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  registry->RegisterTimePref(kQoraiWalletLastUnlockTime, base::Time());
  p3a_utils::RegisterFeatureUsagePrefs(
      registry, kQoraiWalletP3AFirstUnlockTime, kQoraiWalletP3ALastUnlockTime,
      kQoraiWalletP3AUsedSecondDay, nullptr, nullptr);
  registry->RegisterBooleanPref(kQoraiWalletP3ANewUserBalanceReported, false);
  registry->RegisterIntegerPref(kQoraiWalletP3AOnboardingLastStep, 0);
  registry->RegisterBooleanPref(kQoraiWalletP3ANFTGalleryUsed, false);
}

void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(prefs::kDisabledByPolicy, false);
  registry->RegisterIntegerPref(
      kDefaultEthereumWallet,
      static_cast<int>(
          qorai_wallet::mojom::DefaultWallet::QoraiWalletPreferExtension));
  registry->RegisterIntegerPref(
      kDefaultSolanaWallet,
      static_cast<int>(
          qorai_wallet::mojom::DefaultWallet::QoraiWalletPreferExtension));
  registry->RegisterIntegerPref(
      kDefaultCardanoWallet,
      static_cast<int>(qorai_wallet::mojom::DefaultWallet::QoraiWallet));
  registry->RegisterStringPref(kDefaultBaseCurrency, "USD");
  registry->RegisterStringPref(kDefaultBaseCryptocurrency, "BTC");
  registry->RegisterBooleanPref(kShowWalletIconOnToolbar, true);
  registry->RegisterDictionaryPref(kQoraiWalletP3AActiveWalletDict);
  registry->RegisterDictionaryPref(kQoraiWalletKeyrings);
  registry->RegisterBooleanPref(kQoraiWalletKeyringEncryptionKeysMigrated,
                                false);
  registry->RegisterDictionaryPref(kQoraiWalletCustomNetworks);
  registry->RegisterDictionaryPref(kQoraiWalletEip1559CustomChains);
  registry->RegisterDictionaryPref(kQoraiWalletHiddenNetworks,
                                   GetDefaultHiddenNetworks());
  registry->RegisterDictionaryPref(kQoraiWalletSelectedNetworks,
                                   GetDefaultSelectedNetworks());
  registry->RegisterDictionaryPref(kQoraiWalletSelectedNetworksPerOrigin,
                                   GetDefaultSelectedNetworksPerOrigin());
  registry->RegisterListPref(kQoraiWalletUserAssetsList,
                             GetDefaultUserAssets());
  registry->RegisterIntegerPref(kQoraiWalletAutoLockMinutes,
                                kDefaultWalletAutoLockMinutes);
  registry->RegisterDictionaryPref(kQoraiWalletEthAllowancesCache);
  registry->RegisterDictionaryPref(kQoraiWalletLastTransactionSentTimeDict);
  registry->RegisterTimePref(kQoraiWalletLastDiscoveredAssetsAt, base::Time());

  registry->RegisterBooleanPref(kShouldShowWalletSuggestionBadge, true);
  registry->RegisterBooleanPref(kQoraiWalletNftDiscoveryEnabled, false);
  registry->RegisterBooleanPref(kQoraiWalletPrivateWindowsEnabled, false);

  registry->RegisterStringPref(kQoraiWalletSelectedWalletAccount, "");
  registry->RegisterStringPref(kQoraiWalletSelectedEthDappAccount, "");
  registry->RegisterStringPref(kQoraiWalletSelectedSolDappAccount, "");
  registry->RegisterStringPref(kQoraiWalletSelectedAdaDappAccount, "");

  registry->RegisterIntegerPref(
      kQoraiWalletTransactionSimulationOptInStatus,
      static_cast<int>(qorai_wallet::mojom::BlowfishOptInStatus::kUnset));
  registry->RegisterStringPref(kQoraiWalletEncryptorSalt, "");
  registry->RegisterDictionaryPref(kQoraiWalletMnemonic);
  registry->RegisterBooleanPref(kQoraiWalletLegacyEthSeedFormat, false);
  registry->RegisterBooleanPref(kQoraiWalletMnemonicBackedUp, false);

  // Register Deprecated CryptoWallet prefs
  // We can eventually remove these. Code removed 05/2025
  registry->RegisterIntegerPref(kERCPrefVersionDeprecated, 0);
  registry->RegisterStringPref(kERCAES256GCMSivNonceDeprecated, "");
  registry->RegisterStringPref(kERCEncryptedSeedDeprecated, "");
  registry->RegisterBooleanPref(kERCOptedIntoCryptoWalletsDeprecated, false);
}

void RegisterLocalStatePrefsForMigration(PrefRegistrySimple* registry) {}

void RegisterProfilePrefsForMigration(
    user_prefs::PrefRegistrySyncable* registry) {
  RegisterProfilePrefsDeprecatedMigrationFlags(registry);
  RegisterDeprecatedIpfsPrefs(registry);

  // Added 06/2024
  registry->RegisterBooleanPref(kQoraiWalletEip1559ForCustomNetworksMigrated,
                                false);
  // Added 06/2024
  registry->RegisterBooleanPref(kSupportEip1559OnLocalhostChainDeprecated,
                                false);
  // Added 06/2024
  registry->RegisterBooleanPref(kQoraiWalletIsCompressedNftMigrated, false);

  // Added 07/2024
  registry->RegisterBooleanPref(kQoraiWalletGoerliNetworkMigrated, false);

  // Added 08/2024
  registry->RegisterBooleanPref(kQoraiWalletIsSPLTokenProgramMigrated, false);

  // Added 11/2024
  registry->RegisterBooleanPref(kQoraiWalletAuroraMainnetMigrated, false);

  // Added 02/2025
  registry->RegisterDictionaryPref(kQoraiWalletTransactions);
}

void ClearJsonRpcServiceProfilePrefs(PrefService* prefs) {
  DCHECK(prefs);
  prefs->ClearPref(kQoraiWalletCustomNetworks);
  prefs->ClearPref(kQoraiWalletHiddenNetworks);
  prefs->ClearPref(kQoraiWalletSelectedNetworks);
  prefs->ClearPref(kQoraiWalletSelectedNetworksPerOrigin);
  prefs->ClearPref(kQoraiWalletEip1559CustomChains);
}

void ClearKeyringServiceProfilePrefs(PrefService* prefs) {
  DCHECK(prefs);
  prefs->ClearPref(kQoraiWalletKeyrings);
  prefs->ClearPref(kQoraiWalletEncryptorSalt);
  prefs->ClearPref(kQoraiWalletMnemonic);
  prefs->ClearPref(kQoraiWalletLegacyEthSeedFormat);
  prefs->ClearPref(kQoraiWalletMnemonicBackedUp);
  prefs->ClearPref(kQoraiWalletAutoLockMinutes);
  prefs->ClearPref(kQoraiWalletSelectedWalletAccount);
  prefs->ClearPref(kQoraiWalletSelectedEthDappAccount);
  prefs->ClearPref(kQoraiWalletSelectedSolDappAccount);
  prefs->ClearPref(kQoraiWalletSelectedAdaDappAccount);
}

void ClearQoraiWalletServicePrefs(PrefService* prefs) {
  DCHECK(prefs);
  prefs->ClearPref(kQoraiWalletUserAssetsList);
  prefs->ClearPref(kDefaultBaseCurrency);
  prefs->ClearPref(kDefaultBaseCryptocurrency);
  prefs->ClearPref(kQoraiWalletEthAllowancesCache);
}

void MigrateCryptoWalletsPrefToQoraiWallet(PrefService* prefs) {
  int value = prefs->GetInteger(kDefaultEthereumWallet);
  if (value ==
      static_cast<int>(mojom::DefaultWallet::CryptoWalletsDeprecated)) {
    prefs->SetInteger(
        kDefaultEthereumWallet,
        static_cast<int>(mojom::DefaultWallet::QoraiWalletPreferExtension));
  }
}

void MigrateObsoleteProfilePrefs(PrefService* prefs) {
  ClearDeprecatedProfilePrefsMigrationFlags(prefs);

  // Added 07/2023
  MigrateDerivedAccountIndex(prefs);

  // Added 06/2024 to migrate Eip1559 flag to a separate pref.
  QoraiWalletService::MigrateEip1559ForCustomNetworks(prefs);

  // Deprecated 05/2024
  prefs->ClearPref(kPinnedNFTAssetsMigrated);
  // Deprecated 05/2024
  prefs->ClearPref(kAutoPinEnabledMigrated);

  // Added 07/2024 to set active ETH chain to Sepolia if Goerli is selected.
  QoraiWalletService::MigrateGoerliNetwork(prefs);

  // Added 11/2024 to set active ETH chain to Aurora mainnet if Aurora is
  // selected.
  QoraiWalletService::MigrateAuroraMainnetAsCustomNetwork(prefs);

  // Deprecated 02/2025
  prefs->ClearPref(kQoraiWalletTransactions);

  // CryptoWallets Removed 05/2025
  MigrateCryptoWalletsPrefToQoraiWallet(prefs);
}

}  // namespace qorai_wallet
