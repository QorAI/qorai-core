/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_PREF_NAMES_H_

inline constexpr char kShouldShowWalletSuggestionBadge[] =
    "qorai.wallet.should_show_wallet_suggestion_badge";
inline constexpr char kDefaultEthereumWallet[] = "qorai.wallet.default_wallet2";
inline constexpr char kDefaultSolanaWallet[] =
    "qorai.wallet.default_solana_wallet";
inline constexpr char kDefaultCardanoWallet[] =
    "qorai.wallet.default_cardano_wallet";
inline constexpr char kDefaultBaseCurrency[] =
    "qorai.wallet.default_base_currency";
inline constexpr char kDefaultBaseCryptocurrency[] =
    "qorai.wallet.default_base_cryptocurrency";
inline constexpr char kShowWalletIconOnToolbar[] =
    "qorai.wallet.show_wallet_icon_on_toolbar";
inline constexpr char kQoraiWalletLastUnlockTime[] =
    "qorai.wallet.wallet_last_unlock_time_v2";
inline constexpr char kQoraiWalletPingReportedUnlockTime[] =
    "qorai.wallet.wallet_report_unlock_time_ping";
inline constexpr char kQoraiWalletP3ANFTGalleryUsed[] =
    "qorai.wallet.wallet_p3a_nft_gallery_used";
inline constexpr char kQoraiWalletP3ANewUserBalanceReported[] =
    "qorai.wallet.p3a_new_user_balance_reported";
inline constexpr char kQoraiWalletP3AActiveWalletDict[] =
    "qorai.wallet.wallet_p3a_active_wallets";
inline constexpr char kQoraiWalletCustomNetworks[] =
    "qorai.wallet.custom_networks";
inline constexpr char kQoraiWalletEip1559CustomChains[] =
    "qorai.wallet.eip1559_chains";
inline constexpr char kQoraiWalletHiddenNetworks[] =
    "qorai.wallet.hidden_networks";
inline constexpr char kQoraiWalletSelectedNetworks[] =
    "qorai.wallet.selected_networks";
inline constexpr char kQoraiWalletSelectedNetworksPerOrigin[] =
    "qorai.wallet.selected_networks_origin";
inline constexpr char kQoraiWalletSelectedWalletAccount[] =
    "qorai.wallet.selected_wallet_account";
inline constexpr char kQoraiWalletSelectedEthDappAccount[] =
    "qorai.wallet.selected_eth_dapp_account";
inline constexpr char kQoraiWalletSelectedSolDappAccount[] =
    "qorai.wallet.selected_sol_dapp_account";
inline constexpr char kQoraiWalletSelectedAdaDappAccount[] =
    "qorai.wallet.selected_ada_dapp_account";
inline constexpr char kQoraiWalletKeyrings[] = "qorai.wallet.keyrings";
inline constexpr char kQoraiWalletUserAssetsList[] =
    "qorai.wallet.wallet_user_assets_list";
inline constexpr char kQoraiWalletEthAllowancesCache[] =
    "qorai.wallet.eth_allowances_cache";
inline constexpr char kQoraiWalletAutoLockMinutes[] =
    "qorai.wallet.auto_lock_minutes";
inline constexpr char kQoraiWalletP3AFirstUnlockTime[] =
    "qorai.wallet.p3a_first_unlock_time";
inline constexpr char kQoraiWalletP3ALastUnlockTime[] =
    "qorai.wallet.p3a_last_unlock_time";
inline constexpr char kQoraiWalletP3AUsedSecondDay[] =
    "qorai.wallet.p3a_used_second_day";
inline constexpr char kQoraiWalletP3AOnboardingLastStep[] =
    "qorai.wallet.p3a_last_onboarding_step";
inline constexpr char kQoraiWalletKeyringEncryptionKeysMigrated[] =
    "qorai.wallet.keyring_encryption_keys_migrated";
inline constexpr char kQoraiWalletLastTransactionSentTimeDict[] =
    "qorai.wallet.last_transaction_sent_time_dict";
inline constexpr char kQoraiWalletNftDiscoveryEnabled[] =
    "qorai.wallet.nft_discovery_enabled";
inline constexpr char kQoraiWalletLastDiscoveredAssetsAt[] =
    "qorai.wallet.last_discovered_assets_at";
inline constexpr char kQoraiWalletPrivateWindowsEnabled[] =
    "qorai.wallet.private_windows_enabled";
inline constexpr char kQoraiWalletTransactionSimulationOptInStatus[] =
    "qorai.wallet.transaction_simulation_opt_in_status";
inline constexpr char kQoraiWalletEncryptorSalt[] =
    "qorai.wallet.encryptor_salt";
inline constexpr char kQoraiWalletMnemonic[] =
    "qorai.wallet.encrypted_mnemonic";
inline constexpr char kQoraiWalletLegacyEthSeedFormat[] =
    "qorai.wallet.legacy_eth_seed_format";
inline constexpr char kQoraiWalletMnemonicBackedUp[] =
    "qorai.wallet.mnemonic_backed_up";

// Added 06/2024 to migrate Eip1559 flag to a separate pref.
inline constexpr char kQoraiWalletEip1559ForCustomNetworksMigrated[] =
    "qorai.wallet.eip1559_chains_migrated";
// 06/2024 to mark existing compressed Solana NFTs as compressed.
inline constexpr char kQoraiWalletIsCompressedNftMigrated[] =
    "qorai.wallet.is_compressed_nft_migrated";
// Added 11/2024 to mark Aurora mainnet as migrated.
inline constexpr char kQoraiWalletAuroraMainnetMigrated[] =
    "qorai.wallet.aurora_mainnet_migrated";

// 08/2024 to mark fix existing SPL tokens marked as unsupported
inline constexpr char kQoraiWalletIsSPLTokenProgramMigrated[] =
    "qorai.wallet.is_spl_token_program_migrated";

// 06/2024 migrated to kQoraiWalletEip1559CustomChains.
inline constexpr char kSupportEip1559OnLocalhostChainDeprecated[] =
    "qorai.wallet.support_eip1559_on_localhost_chain";
// Added 07/2024 to remove Goerli mainnet, previously a preloaded network.
inline constexpr char kQoraiWalletGoerliNetworkMigrated[] =
    "qorai.wallet.custom_networks.goerli_migrated";

// CryptoWallets prefs
// Deprecated 05/2025
inline constexpr char kERCAES256GCMSivNonceDeprecated[] =
    "qorai.wallet.aes_256_gcm_siv_nonce";
inline constexpr char kERCEncryptedSeedDeprecated[] =
    "qorai.wallet.encrypted_seed";
inline constexpr char kERCPrefVersionDeprecated[] = "qorai.wallet.pref_version";
inline constexpr char kERCOptedIntoCryptoWalletsDeprecated[] =
    "qorai.wallet.opted_in";

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_PREF_NAMES_H_
