// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import { assertNotReached } from 'chrome://resources/js/assert.js'
import { getLocale } from '../../common/locale'

// types
import {
  QoraiWallet,
  BitcoinMainnetKeyringIds,
  BitcoinTestnetKeyringIds,
  ZCashTestnetKeyringIds,
  CardanoTestnetKeyringIds,
} from '../constants/types'

// constants
import registry from '../common/constants/registry'

// utils
import { reduceAddress } from './reduce-address'
import { EntityState } from '@reduxjs/toolkit'

export const sortAccountsByName = (accounts: QoraiWallet.AccountInfo[]) => {
  return [...accounts].sort(function (
    a: QoraiWallet.AccountInfo,
    b: QoraiWallet.AccountInfo,
  ) {
    if (a.name < b.name) {
      return -1
    }

    if (a.name > b.name) {
      return 1
    }

    return 0
  })
}

export const groupAccountsById = (
  accounts: QoraiWallet.AccountInfo[],
  key: string,
) => {
  return accounts.reduce<Record<string, QoraiWallet.AccountInfo[]>>(
    (result, obj) => {
      const resultKey: any = obj[key as keyof QoraiWallet.AccountInfo]
      ;(result[resultKey] = result[resultKey] || []).push(obj)
      return result
    },
    {},
  )
}

export const findAccountByUniqueKey = <
  T extends { accountId: { uniqueKey: string } },
>(
  accounts: T[],
  uniqueKey: string | undefined,
): T | undefined => {
  if (!uniqueKey) {
    return
  }

  return accounts.find((account) => uniqueKey === account.accountId.uniqueKey)
}

export const entityIdFromAccountId = (
  accountId: Pick<QoraiWallet.AccountId, 'uniqueKey'>,
) => {
  return accountId.uniqueKey
}

export const findAccountByAddress = (
  address: string,
  accounts: EntityState<QoraiWallet.AccountInfo> | undefined,
): QoraiWallet.AccountInfo | undefined => {
  if (!address || !accounts) return undefined
  for (const id of accounts.ids) {
    if (
      accounts.entities[id]?.address.toLowerCase() === address.toLowerCase()
    ) {
      return accounts.entities[id]
    }
  }
  return undefined
}

export const findAccountByAccountId = (
  accountId: Pick<QoraiWallet.AccountId, 'uniqueKey'>,
  accounts: EntityState<QoraiWallet.AccountInfo> | undefined,
): QoraiWallet.AccountInfo | undefined => {
  if (!accounts) {
    return undefined
  }

  return accounts.entities[entityIdFromAccountId(accountId)]
}

export const getAddressLabel = (
  address: string,
  accounts?: EntityState<QoraiWallet.AccountInfo>,
): string => {
  if (!accounts) {
    return (
      registry[address.toLowerCase() as keyof typeof registry]
      ?? reduceAddress(address)
    )
  }
  return (
    registry[address.toLowerCase() as keyof typeof registry]
    ?? findAccountByAddress(address, accounts)?.name
    ?? reduceAddress(address)
  )
}

export const getAccountLabel = (
  accountId: QoraiWallet.AccountId,
  accounts: EntityState<QoraiWallet.AccountInfo>,
): string => {
  return (
    findAccountByAccountId(accountId, accounts)?.name
    ?? reduceAddress(accountId.address)
  )
}

export function isHardwareAccount(account: QoraiWallet.AccountId) {
  return account.kind === QoraiWallet.AccountKind.kHardware
}

export const keyringIdForNewAccount = (
  coin: QoraiWallet.CoinType,
  chainId?: string | undefined,
) => {
  if (coin === QoraiWallet.CoinType.ETH) {
    return QoraiWallet.KeyringId.kDefault
  }

  if (coin === QoraiWallet.CoinType.SOL) {
    return QoraiWallet.KeyringId.kSolana
  }

  if (coin === QoraiWallet.CoinType.FIL) {
    if (
      chainId === QoraiWallet.FILECOIN_MAINNET
      || chainId === QoraiWallet.LOCALHOST_CHAIN_ID
    ) {
      return QoraiWallet.KeyringId.kFilecoin
    }
    if (chainId === QoraiWallet.FILECOIN_TESTNET) {
      return QoraiWallet.KeyringId.kFilecoinTestnet
    }
  }

  if (coin === QoraiWallet.CoinType.BTC) {
    if (chainId === QoraiWallet.BITCOIN_MAINNET) {
      return QoraiWallet.KeyringId.kBitcoin84
    }
    if (chainId === QoraiWallet.BITCOIN_TESTNET) {
      return QoraiWallet.KeyringId.kBitcoin84Testnet
    }
  }

  if (coin === QoraiWallet.CoinType.ZEC) {
    if (chainId === QoraiWallet.Z_CASH_MAINNET) {
      return QoraiWallet.KeyringId.kZCashMainnet
    }
    if (chainId === QoraiWallet.Z_CASH_TESTNET) {
      return QoraiWallet.KeyringId.kZCashTestnet
    }
  }

  if (coin === QoraiWallet.CoinType.ADA) {
    if (chainId === QoraiWallet.CARDANO_MAINNET) {
      return QoraiWallet.KeyringId.kCardanoMainnet
    }
    if (chainId === QoraiWallet.CARDANO_TESTNET) {
      return QoraiWallet.KeyringId.kCardanoTestnet
    }
  }

  if (coin === QoraiWallet.CoinType.DOT) {
    if (chainId === QoraiWallet.POLKADOT_MAINNET) {
      return QoraiWallet.KeyringId.kPolkadotMainnet
    }
    if (chainId === QoraiWallet.POLKADOT_TESTNET) {
      return QoraiWallet.KeyringId.kPolkadotTestnet
    }
  }

  assertNotReached(`Unknown coin ${coin} and chainId ${chainId}`)
}

export const getAccountTypeDescription = (accountId: QoraiWallet.AccountId) => {
  switch (accountId.coin) {
    case QoraiWallet.CoinType.ETH:
      return getLocale('qoraiWalletETHAccountDescription')
    case QoraiWallet.CoinType.SOL:
      return getLocale('qoraiWalletSOLAccountDescription')
    case QoraiWallet.CoinType.FIL:
      return getLocale('qoraiWalletFILAccountDescription')
    case QoraiWallet.CoinType.BTC:
      if (BitcoinTestnetKeyringIds.includes(accountId.keyringId)) {
        return getLocale('qoraiWalletBTCTestnetAccountDescription')
      }
      return getLocale('qoraiWalletBTCMainnetAccountDescription')
    case QoraiWallet.CoinType.ZEC:
      if (ZCashTestnetKeyringIds.includes(accountId.keyringId)) {
        return getLocale('qoraiWalletZECTestnetAccountDescription')
      }
      return getLocale('qoraiWalletZECAccountDescription')
    case QoraiWallet.CoinType.ADA:
      if (CardanoTestnetKeyringIds.includes(accountId.keyringId)) {
        return getLocale('qoraiWalletCardanoTestnetAccountDescription')
      }
      return getLocale('qoraiWalletCardanoAccountDescription')
    case QoraiWallet.CoinType.DOT:
      return getLocale('qoraiWalletPolkadotMainnetAccountDescription')
    default:
      assertNotReached(`Unknown coin ${accountId.coin}`)
  }
}

export const isFVMAccount = (
  account: QoraiWallet.AccountInfo,
  network: QoraiWallet.NetworkInfo,
) => {
  return (
    (network.chainId === QoraiWallet.FILECOIN_ETHEREUM_MAINNET_CHAIN_ID
      && account.accountId.keyringId === QoraiWallet.KeyringId.kFilecoin)
    || (network.chainId === QoraiWallet.FILECOIN_ETHEREUM_TESTNET_CHAIN_ID
      && account.accountId.keyringId === QoraiWallet.KeyringId.kFilecoinTestnet)
  )
}

export const getAccountsForNetwork = (
  network: Pick<QoraiWallet.NetworkInfo, 'chainId' | 'coin'>,
  accounts: QoraiWallet.AccountInfo[],
) => {
  if (network.chainId === QoraiWallet.BITCOIN_MAINNET) {
    return accounts.filter((account) =>
      BitcoinMainnetKeyringIds.includes(account.accountId.keyringId),
    )
  }
  if (network.chainId === QoraiWallet.BITCOIN_TESTNET) {
    return accounts.filter((account) =>
      BitcoinTestnetKeyringIds.includes(account.accountId.keyringId),
    )
  }
  if (network.chainId === QoraiWallet.Z_CASH_MAINNET) {
    return accounts.filter(
      (account) =>
        account.accountId.keyringId === QoraiWallet.KeyringId.kZCashMainnet,
    )
  }
  if (network.chainId === QoraiWallet.Z_CASH_TESTNET) {
    return accounts.filter(
      (account) =>
        account.accountId.keyringId === QoraiWallet.KeyringId.kZCashTestnet,
    )
  }
  if (network.chainId === QoraiWallet.FILECOIN_MAINNET) {
    return accounts.filter(
      (account) =>
        account.accountId.keyringId === QoraiWallet.KeyringId.kFilecoin,
    )
  }
  if (network.chainId === QoraiWallet.FILECOIN_TESTNET) {
    return accounts.filter(
      (account) =>
        account.accountId.keyringId === QoraiWallet.KeyringId.kFilecoinTestnet,
    )
  }
  return accounts.filter((account) => account.accountId.coin === network.coin)
}
