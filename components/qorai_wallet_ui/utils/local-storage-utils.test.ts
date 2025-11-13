// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { QoraiWallet } from '../constants/types'
import {
  parseJSONFromLocalStorage,
  makeInitialFilteredOutNetworkKeys,
} from './local-storage-utils'
import { networkEntityAdapter } from '../common/slices/entities/network.entity'
import { LOCAL_STORAGE_KEYS } from '../common/constants/local-storage-keys'

const mockInitialFilteredOutNetworkKeys = [
  networkEntityAdapter
    .selectId({
      chainId: QoraiWallet.SEPOLIA_CHAIN_ID,
      coin: QoraiWallet.CoinType.ETH,
    })
    .toString(),
  networkEntityAdapter
    .selectId({
      chainId: QoraiWallet.SOLANA_DEVNET,
      coin: QoraiWallet.CoinType.SOL,
    })
    .toString(),
  networkEntityAdapter
    .selectId({
      chainId: QoraiWallet.SOLANA_TESTNET,
      coin: QoraiWallet.CoinType.SOL,
    })
    .toString(),
  networkEntityAdapter
    .selectId({
      chainId: QoraiWallet.FILECOIN_TESTNET,
      coin: QoraiWallet.CoinType.FIL,
    })
    .toString(),
  networkEntityAdapter
    .selectId({
      chainId: QoraiWallet.FILECOIN_ETHEREUM_TESTNET_CHAIN_ID,
      coin: QoraiWallet.CoinType.ETH,
    })
    .toString(),
  networkEntityAdapter
    .selectId({
      chainId: QoraiWallet.BITCOIN_TESTNET,
      coin: QoraiWallet.CoinType.BTC,
    })
    .toString(),
  networkEntityAdapter
    .selectId({
      chainId: QoraiWallet.Z_CASH_TESTNET,
      coin: QoraiWallet.CoinType.ZEC,
    })
    .toString(),
  networkEntityAdapter
    .selectId({
      chainId: QoraiWallet.CARDANO_TESTNET,
      coin: QoraiWallet.CoinType.ADA,
    })
    .toString(),
  networkEntityAdapter
    .selectId({
      chainId: QoraiWallet.POLKADOT_TESTNET,
      coin: QoraiWallet.CoinType.DOT,
    })
    .toString(),
  networkEntityAdapter
    .selectId({
      chainId: QoraiWallet.LOCALHOST_CHAIN_ID,
      coin: QoraiWallet.CoinType.ETH,
    })
    .toString(),
  networkEntityAdapter
    .selectId({
      chainId: QoraiWallet.LOCALHOST_CHAIN_ID,
      coin: QoraiWallet.CoinType.SOL,
    })
    .toString(),
  networkEntityAdapter
    .selectId({
      chainId: QoraiWallet.LOCALHOST_CHAIN_ID,
      coin: QoraiWallet.CoinType.FIL,
    })
    .toString(),
]

describe('Test parseJSONFromLocalStorage', () => {
  const key = 'FILTERED_OUT_PORTFOLIO_NETWORK_KEYS'
  const initialNetworkKeys = makeInitialFilteredOutNetworkKeys()
  const mockValue = JSON.stringify(initialNetworkKeys)
  let mockLocalStorageGet = jest.fn()
  Object.defineProperty(window, 'localStorage', {
    value: {
      getItem: mockLocalStorageGet,
    },
  })
  it('getItem be called and the value should be correctly parsed', () => {
    mockLocalStorageGet.mockReturnValue(mockValue)
    expect(parseJSONFromLocalStorage(key, mockValue)).toEqual(
      initialNetworkKeys,
    )
    expect(window.localStorage.getItem).toHaveBeenCalledWith(
      LOCAL_STORAGE_KEYS[key],
    )
    expect(jest.isMockFunction(window.localStorage.getItem)).toBe(true)
    expect(mockLocalStorageGet.mock.results[0].value).toBe(mockValue)
  })
  it('getItem should return null, fallback should be returned', () => {
    mockLocalStorageGet.mockReturnValue(null)
    expect(parseJSONFromLocalStorage(key, initialNetworkKeys)).toEqual(
      initialNetworkKeys,
    )
    expect(window.localStorage.getItem).toHaveBeenCalledWith(
      LOCAL_STORAGE_KEYS[key],
    )
    expect(jest.isMockFunction(window.localStorage.getItem)).toBe(true)
    expect(mockLocalStorageGet.mock.results[0].value).toBe(null)
  })
})

describe('Test makeInitialFilteredOutNetworkKeys', () => {
  it('Should construct a string array of test network keys', () => {
    expect(makeInitialFilteredOutNetworkKeys()).toEqual(
      mockInitialFilteredOutNetworkKeys,
    )
  })
})
