// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import { QoraiWallet, CreateAccountOptionsType } from '../constants/types'
import { getLocale } from '../../common/locale'
import { getNetworkLogo } from './asset-options'

export const CreateAccountOptions = (options: {
  visibleNetworks: QoraiWallet.NetworkInfo[]
  isBitcoinEnabled: boolean
  isZCashEnabled: boolean
  isCardanoEnabled: boolean
  isPolkadotEnabled: boolean
}): CreateAccountOptionsType[] => {
  const isNetworkVisible = (coin: QoraiWallet.CoinType, chaiId: string) => {
    return !!options.visibleNetworks.find(
      (n) => n.coin === coin && n.chainId === chaiId,
    )
  }

  const accounts: CreateAccountOptionsType[] = []
  const testnetAccounts: CreateAccountOptionsType[] = []

  accounts.push({
    description: getLocale('qoraiWalletCreateAccountEthereumDescription'),
    name: 'Ethereum',
    coin: QoraiWallet.CoinType.ETH,
    icon: getNetworkLogo(QoraiWallet.MAINNET_CHAIN_ID, 'ETH'),
    chainIcons: ['eth-color', 'matic-color', 'op-color', 'aurora-color'],
  })

  accounts.push({
    description: getLocale('qoraiWalletCreateAccountSolanaDescription'),
    name: 'Solana',
    coin: QoraiWallet.CoinType.SOL,
    icon: getNetworkLogo(QoraiWallet.SOLANA_MAINNET, 'SOL'),
    chainIcons: ['sol-color'],
  })

  accounts.push({
    description: getLocale('qoraiWalletCreateAccountFilecoinDescription'),
    name: 'Filecoin',
    coin: QoraiWallet.CoinType.FIL,
    fixedNetwork: QoraiWallet.FILECOIN_MAINNET,
    icon: getNetworkLogo(QoraiWallet.FILECOIN_MAINNET, 'FIL'),
    chainIcons: ['filecoin-color'],
  })
  if (
    isNetworkVisible(QoraiWallet.CoinType.FIL, QoraiWallet.FILECOIN_TESTNET)
  ) {
    testnetAccounts.push({
      description: getLocale(
        'qoraiWalletCreateAccountFilecoinTestnetDescription',
      ),
      name: 'Filecoin Testnet',
      coin: QoraiWallet.CoinType.FIL,
      fixedNetwork: QoraiWallet.FILECOIN_TESTNET,
      icon: getNetworkLogo(QoraiWallet.FILECOIN_TESTNET, 'FIL'),
      chainIcons: ['filecoin-color'],
    })
  }

  if (options.isBitcoinEnabled) {
    accounts.push({
      description: getLocale('qoraiWalletCreateAccountBitcoinDescription'),
      name: 'Bitcoin',
      fixedNetwork: QoraiWallet.BITCOIN_MAINNET,
      coin: QoraiWallet.CoinType.BTC,
      icon: getNetworkLogo(QoraiWallet.BITCOIN_MAINNET, 'BTC'),
      chainIcons: ['btc-color'],
    })
    if (
      isNetworkVisible(QoraiWallet.CoinType.BTC, QoraiWallet.BITCOIN_TESTNET)
    ) {
      testnetAccounts.push({
        description: getLocale(
          'qoraiWalletCreateAccountBitcoinTestnetDescription',
        ),
        name: 'Bitcoin Testnet',
        fixedNetwork: QoraiWallet.BITCOIN_TESTNET,
        coin: QoraiWallet.CoinType.BTC,
        icon: getNetworkLogo(QoraiWallet.BITCOIN_TESTNET, 'BTC'),
        chainIcons: ['btc-color'],
      })
    }
  }

  if (options.isZCashEnabled) {
    accounts.push({
      description: getLocale('qoraiWalletCreateAccountZCashDescription'),
      name: 'Zcash',
      fixedNetwork: QoraiWallet.Z_CASH_MAINNET,
      coin: QoraiWallet.CoinType.ZEC,
      icon: getNetworkLogo(QoraiWallet.Z_CASH_MAINNET, 'ZEC'),
      chainIcons: [],
    })
    if (
      isNetworkVisible(QoraiWallet.CoinType.ZEC, QoraiWallet.Z_CASH_TESTNET)
    ) {
      testnetAccounts.push({
        description: getLocale(
          'qoraiWalletCreateAccountZCashTestnetDescription',
        ),
        name: 'Zcash Testnet',
        fixedNetwork: QoraiWallet.Z_CASH_TESTNET,
        coin: QoraiWallet.CoinType.ZEC,
        icon: getNetworkLogo(QoraiWallet.Z_CASH_TESTNET, 'ZEC'),
        chainIcons: [],
      })
    }
  }

  if (options.isCardanoEnabled) {
    accounts.push({
      description: getLocale('qoraiWalletCreateAccountCardanoDescription'),
      name: 'Cardano',
      fixedNetwork: QoraiWallet.CARDANO_MAINNET,
      coin: QoraiWallet.CoinType.ADA,
      icon: getNetworkLogo(QoraiWallet.CARDANO_MAINNET, 'ADA'),
      chainIcons: ['ada-color'],
    })
    if (
      isNetworkVisible(QoraiWallet.CoinType.ADA, QoraiWallet.CARDANO_TESTNET)
    ) {
      testnetAccounts.push({
        description: getLocale(
          'qoraiWalletCreateAccountCardanoTestnetDescription',
        ),
        name: 'Cardano Testnet',
        fixedNetwork: QoraiWallet.CARDANO_TESTNET,
        coin: QoraiWallet.CoinType.ADA,
        icon: getNetworkLogo(QoraiWallet.CARDANO_TESTNET, 'ADA'),
        chainIcons: ['ada-color'],
      })
    }
  }

  if (options.isPolkadotEnabled) {
    accounts.push({
      description: getLocale('qoraiWalletCreateAccountPolkadotDescription'),
      name: 'Polkadot',
      coin: QoraiWallet.CoinType.DOT,
      icon: getNetworkLogo(QoraiWallet.POLKADOT_MAINNET, 'DOT'),
      chainIcons: ['dot-color'],
    })

    if (
      isNetworkVisible(QoraiWallet.CoinType.DOT, QoraiWallet.POLKADOT_TESTNET)
    ) {
      testnetAccounts.push({
        description: getLocale(
          'qoraiWalletCreateAccountPolkadotTestnetDescription',
        ),
        name: 'Polkadot Westend',
        fixedNetwork: QoraiWallet.POLKADOT_TESTNET,
        coin: QoraiWallet.CoinType.DOT,
        icon: getNetworkLogo(QoraiWallet.POLKADOT_TESTNET, 'DOT'),
        chainIcons: ['dot-color'],
      })
    }
  }

  return accounts.concat(testnetAccounts)
}
