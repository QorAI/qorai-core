// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

// types
import { QoraiWallet, WalletState } from '../../constants/types'

// mocks
import { networkEntityAdapter } from '../../common/slices/entities/network.entity'

export const mockWalletState: WalletState = {
  addUserAssetError: false,
  hasInitialized: true,
  isBitcoinEnabled: true,
  isBitcoinImportEnabled: true,
  isBitcoinLedgerEnabled: true,
  isZCashEnabled: true,
  isAnkrBalancesFeatureEnabled: false,
  allowedNewWalletAccountTypeNetworkIds: [
    networkEntityAdapter.selectId({
      chainId: QoraiWallet.FILECOIN_MAINNET,
      coin: QoraiWallet.CoinType.FIL,
    }),
    networkEntityAdapter.selectId({
      chainId: QoraiWallet.FILECOIN_TESTNET,
      coin: QoraiWallet.CoinType.FIL,
    }),
    networkEntityAdapter.selectId({
      chainId: QoraiWallet.BITCOIN_MAINNET,
      coin: QoraiWallet.CoinType.BTC,
    }),
    networkEntityAdapter.selectId({
      chainId: QoraiWallet.BITCOIN_TESTNET,
      coin: QoraiWallet.CoinType.BTC,
    }),
    networkEntityAdapter.selectId({
      chainId: QoraiWallet.Z_CASH_MAINNET,
      coin: QoraiWallet.CoinType.ZEC,
    }),
    networkEntityAdapter.selectId({
      chainId: QoraiWallet.Z_CASH_TESTNET,
      coin: QoraiWallet.CoinType.ZEC,
    }),
    networkEntityAdapter.selectId({
      chainId: QoraiWallet.SOLANA_MAINNET,
      coin: QoraiWallet.CoinType.SOL,
    }),
    networkEntityAdapter.selectId({
      chainId: QoraiWallet.MAINNET_CHAIN_ID,
      coin: QoraiWallet.CoinType.ETH,
    }),
  ],
  isWalletCreated: false,
  isWalletLocked: false,
  passwordAttempts: 0,
  assetAutoDiscoveryCompleted: false,
  isRefreshingNetworksAndTokens: false,
  isZCashShieldedTransactionsEnabled: false,
  isCardanoEnabled: true,
  isCardanoDappSupportEnabled: true,
  isPolkadotEnabled: true,
}
