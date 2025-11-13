// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { QoraiWallet, MeldCryptoCurrency } from '../constants/types'

export const getAssetSymbol = (asset: MeldCryptoCurrency) => {
  return asset.currencyCode.replace(`_${asset.chainCode}`, '')
}

export const getAssetPriceId = (asset: MeldCryptoCurrency) => {
  if (asset.coingeckoId) {
    return asset.coingeckoId
  }
  const isEthereumNetwork =
    asset.chainId?.toLowerCase() === QoraiWallet.MAINNET_CHAIN_ID.toLowerCase()
  if (isEthereumNetwork && asset.contractAddress) {
    return asset.contractAddress.toLowerCase()
  }

  return getAssetSymbol(asset)?.toLowerCase() ?? ''
}

export const getAssetIdKey = (asset: MeldCryptoCurrency) => {
  return `0x${parseInt(asset.chainId ?? '').toString(16)}-${
    asset.currencyCode
  }-${asset.contractAddress}`
}

export const getMeldTokensCoinType = (
  asset: Pick<MeldCryptoCurrency, 'chainCode'>,
) => {
  switch (asset.chainCode) {
    case 'BTC':
      return QoraiWallet.CoinType.BTC
    case 'FIL':
      return QoraiWallet.CoinType.FIL
    case 'ZEC':
      return QoraiWallet.CoinType.ZEC
    case 'SOLANA':
      return QoraiWallet.CoinType.SOL
    default:
      return QoraiWallet.CoinType.ETH
  }
}

export const getMeldTokensChainId = (
  asset: Pick<MeldCryptoCurrency, 'chainId' | 'chainCode'>,
) => {
  switch (asset.chainCode) {
    case 'BTC':
      return QoraiWallet.BITCOIN_MAINNET
    case 'FIL':
      return QoraiWallet.FILECOIN_MAINNET
    case 'ZEC':
      return QoraiWallet.Z_CASH_MAINNET
    default:
      return asset.chainId
  }
}
