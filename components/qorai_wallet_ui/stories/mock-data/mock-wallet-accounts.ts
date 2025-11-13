// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import {
  AccountFromDevice,
  EthLedgerLiveHardwareImportScheme,
} from '../../common/hardware/types'
import { QoraiWallet } from '../../constants/types'

export const mockEthAccount = {
  name: 'Account 1',
  address: '0x7d66c9ddAED3115d93Bd1790332f3Cd06Cf52B14',
  nativeBalanceRegistry: {
    '0x1': '311780000000000000',
  },
  tokenBalanceRegistry: {},
  accountId: {
    coin: QoraiWallet.CoinType.ETH,
    keyringId: QoraiWallet.KeyringId.kDefault,
    kind: QoraiWallet.AccountKind.kDerived,
    address: '0x7d66c9ddAED3115d93Bd1790332f3Cd06Cf52B14',
    accountIndex: 0,
    uniqueKey: 'mockEthAccount_uniqueKey',
  },
  hardware: undefined,
}

export const mockBitcoinAccount = {
  address: '',
  accountId: {
    coin: 0,
    keyringId: QoraiWallet.KeyringId.kBitcoin84,
    kind: QoraiWallet.AccountKind.kDerived,
    address: '',
    accountIndex: 0,
    uniqueKey: 'mockBitcoinAccount_uniqueKey',
  },
  name: 'Bitcoin Account',
  tokenBalanceRegistry: {},
  nativeBalanceRegistry: {
    [QoraiWallet.BITCOIN_MAINNET]: '123456789',
  },
  hardware: undefined,
}

export const mockCardanoAccount = {
  address: '',
  accountId: {
    coin: QoraiWallet.CoinType.ADA,
    keyringId: QoraiWallet.KeyringId.kCardanoMainnet,
    kind: QoraiWallet.AccountKind.kDerived,
    address: '',
    accountIndex: 0,
    uniqueKey: 'mockCardanoAccount_uniqueKey',
  },
  name: 'Cardano Account',
  tokenBalanceRegistry: {},
  nativeBalanceRegistry: {
    [QoraiWallet.CARDANO_MAINNET]: '123456789',
  },
  hardware: undefined,
}

export const mockPolkadotAccount = {
  address: '',
  accountId: {
    coin: QoraiWallet.CoinType.DOT,
    keyringId: QoraiWallet.KeyringId.kPolkadotMainnet,
    kind: QoraiWallet.AccountKind.kDerived,
    address: '',
    accountIndex: 0,
    uniqueKey: 'mockPolkadotAccount_uniqueKey',
  },
  name: 'Polkadot Account',
  tokenBalanceRegistry: {},
  nativeBalanceRegistry: {
    [QoraiWallet.POLKADOT_MAINNET]: '123456789',
  },
  hardware: undefined,
}

export const mockAccounts: QoraiWallet.AccountInfo[] = [
  mockEthAccount,
  {
    name: 'Account 2',
    address: '0x73A29A1da97149722eB09c526E4eAd698895bDCf',
    accountId: {
      coin: QoraiWallet.CoinType.ETH,
      keyringId: QoraiWallet.KeyringId.kDefault,
      kind: QoraiWallet.AccountKind.kDerived,
      address: '0x73A29A1da97149722eB09c526E4eAd698895bDCf',
      accountIndex: 0,
      uniqueKey: '2',
    },
    hardware: undefined,
  },
  {
    name: 'Account 3',
    address: '0x3f29A1da97149722eB09c526E4eAd698895b426',
    accountId: {
      coin: QoraiWallet.CoinType.ETH,
      keyringId: QoraiWallet.KeyringId.kDefault,
      kind: QoraiWallet.AccountKind.kDerived,
      address: '0x3f29A1da97149722eB09c526E4eAd698895b426',
      accountIndex: 0,
      uniqueKey: '3',
    },
    hardware: undefined,
  },
  {
    address: '9RaoGw6VQM1SFgX8wtfUL1acv5uuLNaySELJV2orEZbN',
    accountId: {
      coin: 501,
      keyringId: QoraiWallet.KeyringId.kSolana,
      kind: QoraiWallet.AccountKind.kDerived,
      address: '9RaoGw6VQM1SFgX8wtfUL1acv5uuLNaySELJV2orEZbN',
      accountIndex: 0,
      uniqueKey: '9RaoGw6VQM1SFgX8wtfUL1acv5uuLNaySELJV2orEZbN',
    },
    name: 'Solana Account',
    hardware: undefined,
  },
  mockBitcoinAccount,
  mockCardanoAccount,
]

export const mockAccountsFromDevice: AccountFromDevice[] = [
  {
    address: '0x7d66c9ddAED3115d93Bd1790332f3Cd06Cf52B14',
    derivationPath: EthLedgerLiveHardwareImportScheme.pathTemplate(0),
  },
  {
    address: '0x73A29A1da97149722eB09c526E4eAd698895bDCf',
    derivationPath: EthLedgerLiveHardwareImportScheme.pathTemplate(1),
  },
]

export const mockedTransactionAccounts: QoraiWallet.AccountInfo[] = [
  {
    name: 'Account 1',
    address: '1',
    accountId: {
      coin: QoraiWallet.CoinType.ETH,
      keyringId: QoraiWallet.KeyringId.kDefault,
      kind: QoraiWallet.AccountKind.kDerived,
      address: '1',
      accountIndex: 0,
      uniqueKey: '1',
    },
    hardware: undefined,
  },
]
