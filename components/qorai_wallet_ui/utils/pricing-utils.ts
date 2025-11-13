// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

// Types/constants
import { SKIP_PRICE_LOOKUP_COINGECKO_ID } from '../common/constants/magics'
import {
  QoraiWallet,
  externalWalletProviders,
  SupportedTestNetworks,
} from '../constants/types'

// Utils
import Amount from './amount'

export const getTokenPriceFromRegistry = (
  registry: QoraiWallet.AssetPrice[] | undefined,
  token: Pick<
    QoraiWallet.BlockchainToken,
    'coin' | 'chainId' | 'contractAddress'
  >,
): QoraiWallet.AssetPrice | undefined => {
  if (!registry) {
    return undefined
  }

  return registry.find(
    (p) =>
      p.coin === token.coin
      && p.chainId === token.chainId
      && p.address.toLowerCase()
        === (token.contractAddress?.toLowerCase() || ''),
  )
}

export const getTokenPriceAmountFromRegistry = (
  registry: QoraiWallet.AssetPrice[] | undefined,
  token: Pick<
    QoraiWallet.BlockchainToken,
    'coin' | 'chainId' | 'contractAddress'
  >,
) => {
  const value = getTokenPriceFromRegistry(registry, token)
  return value ? new Amount(value.price) : Amount.zero()
}

export const computeFiatAmount = ({
  spotPrices,
  value,
  token,
}: {
  spotPrices: QoraiWallet.AssetPrice[] | undefined
  value: string
  token: Pick<
    QoraiWallet.BlockchainToken,
    'coin' | 'chainId' | 'contractAddress' | 'decimals'
  >
}): Amount => {
  if (!spotPrices && value === '0') {
    return Amount.zero()
  }

  if (!spotPrices || !value) {
    return Amount.empty()
  }

  const price = getTokenPriceFromRegistry(spotPrices, token)
  if (!price) {
    return Amount.zero()
  }

  return new Amount(value)
    .divideByDecimals(token.decimals) // Wei → ETH conversion
    .times(price.price)
}

export const computeFiatAmountToAssetValue = ({
  spotPrices,
  value,
  token,
}: {
  spotPrices?: QoraiWallet.AssetPrice[]
  value: string
  token: Pick<
    QoraiWallet.BlockchainToken,
    'coin' | 'chainId' | 'contractAddress' | 'decimals'
  >
}): Amount => {
  if (!spotPrices || !value) {
    return Amount.empty()
  }

  const priceInfo = getTokenPriceFromRegistry(spotPrices, token)
  if (!priceInfo) {
    return Amount.zero()
  }

  return new Amount(value).div(priceInfo.price).times(1)
}

export const getPriceIdForToken = (
  token: Pick<
    QoraiWallet.BlockchainToken,
    'contractAddress' | 'symbol' | 'coingeckoId' | 'chainId' | 'isShielded'
  >,
) => {
  if (token?.coingeckoId) {
    return token.coingeckoId.toLowerCase()
  }

  // Skip price of testnet tokens
  if (SupportedTestNetworks.includes(token.chainId)) {
    return SKIP_PRICE_LOOKUP_COINGECKO_ID
  }

  const isEthereumNetwork = token.chainId === QoraiWallet.MAINNET_CHAIN_ID
  if (
    (isEthereumNetwork || externalWalletProviders.includes(token.chainId))
    && token.contractAddress
  ) {
    return token.contractAddress.toLowerCase()
  }

  return token.symbol.toLowerCase()
}

const getPriceRequestForToken = (
  token: Pick<
    QoraiWallet.BlockchainToken,
    'coin' | 'chainId' | 'contractAddress'
  >,
): QoraiWallet.AssetPriceRequest | undefined => {
  return {
    coin: token.coin,
    chainId: token.chainId,
    address: token.contractAddress || undefined,
  } satisfies QoraiWallet.AssetPriceRequest
}

export const getPriceRequestsForTokens = (
  tokens: (
    | Pick<QoraiWallet.BlockchainToken, 'coin' | 'chainId' | 'contractAddress'>
    | undefined
  )[],
): QoraiWallet.AssetPriceRequest[] => {
  return tokens
    .filter((token) => token !== undefined)
    .map(getPriceRequestForToken)
    .filter((request) => request !== undefined)
}
