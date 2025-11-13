// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import { assertNotReached } from 'chrome://resources/js/assert.js'

// types
import { QoraiWallet, SerializableSolanaTxData } from '../constants/types'

export const emptyNetwork: QoraiWallet.NetworkInfo = {
  chainId: '',
  chainName: '',
  activeRpcEndpointIndex: 0,
  rpcEndpoints: [],
  blockExplorerUrls: [],
  iconUrls: [],
  symbol: '',
  symbolName: '',
  decimals: 0,
  coin: QoraiWallet.CoinType.ETH,
  supportedKeyrings: [],
}

export const getNetworkInfo = (
  chainId: string,
  coin: QoraiWallet.CoinType,
  list: QoraiWallet.NetworkInfo[],
) => {
  for (let it of list) {
    if (it.chainId === chainId && it.coin === coin) {
      return it
    }
  }
  return emptyNetwork
}

export const networkSupportsAccount = (
  network: Pick<QoraiWallet.NetworkInfo, 'coin' | 'supportedKeyrings'>,
  accountId: QoraiWallet.AccountId,
) => {
  return (
    network.coin === accountId.coin
    && network.supportedKeyrings.includes(accountId.keyringId)
  )
}

export const filterNetworksForAccount = (
  networks: QoraiWallet.NetworkInfo[],
  accountId: QoraiWallet.AccountId,
): QoraiWallet.NetworkInfo[] => {
  if (!networks) {
    return []
  }
  return networks.filter((network) =>
    networkSupportsAccount(network, accountId),
  )
}

export const getTokensNetwork = (
  networks: QoraiWallet.NetworkInfo[],
  token: QoraiWallet.BlockchainToken,
): QoraiWallet.NetworkInfo => {
  if (!networks) {
    return emptyNetwork
  }

  const network = networks.filter((n) => n.chainId === token.chainId)
  if (network.length > 1) {
    return (
      network?.find(
        (n) => n.symbol.toLowerCase() === token.symbol.toLowerCase(),
      ) ?? emptyNetwork
    )
  }

  return network[0] ?? emptyNetwork
}

export type TxDataPresence = {
  ethTxData?: Partial<QoraiWallet.TxDataUnion['ethTxData']> | undefined
  ethTxData1559?: Partial<QoraiWallet.TxDataUnion['ethTxData1559']> | undefined
  solanaTxData?:
    | Partial<QoraiWallet.TxDataUnion['solanaTxData']>
    | SerializableSolanaTxData
    | undefined
  filTxData?: Partial<QoraiWallet.TxDataUnion['filTxData']> | undefined
  btcTxData?: Partial<QoraiWallet.TxDataUnion['btcTxData']> | undefined
  zecTxData?: Partial<QoraiWallet.TxDataUnion['zecTxData']> | undefined
  cardanoTxData?: Partial<QoraiWallet.TxDataUnion['cardanoTxData']> | undefined
  polkadotTxData?:
    | Partial<QoraiWallet.TxDataUnion['polkadotTxData']>
    | undefined
}

export const getCoinFromTxDataUnion = <T extends TxDataPresence>(
  txDataUnion: T,
): QoraiWallet.CoinType => {
  if (txDataUnion.ethTxData || txDataUnion.ethTxData1559) {
    return QoraiWallet.CoinType.ETH
  }
  if (txDataUnion.filTxData) {
    return QoraiWallet.CoinType.FIL
  }
  if (txDataUnion.solanaTxData) {
    return QoraiWallet.CoinType.SOL
  }
  if (txDataUnion.btcTxData) {
    return QoraiWallet.CoinType.BTC
  }
  if (txDataUnion.zecTxData) {
    return QoraiWallet.CoinType.ZEC
  }
  if (txDataUnion.cardanoTxData) {
    return QoraiWallet.CoinType.ADA
  }
  if (txDataUnion.polkadotTxData) {
    return QoraiWallet.CoinType.DOT
  }

  assertNotReached('Unknown transaction coin')
}

export const reduceNetworkDisplayName = (name?: string) => {
  if (!name) {
    return ''
  }
  return name.split(' ')[0]
}
