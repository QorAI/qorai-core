// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// magics
import { SKIP_PRICE_LOOKUP_COINGECKO_ID } from '../common/constants/magics'

// types
import { QoraiWallet, SupportedTestNetworks } from '../constants/types'

// options
import { AllNetworksOption } from './network-filter-options'

// icons
import {
  ArbIcon,
  AuroraIcon,
  BaseIcon,
  CeloIcon,
  FtmIcon,
  NeonIcon,
  OpIcon,
  AVAXIcon,
  BNBIcon,
  BTCIcon,
  ETHIcon,
  FILECOINIcon,
  MATICIcon,
  SOLIcon,
  ZECIcon,
  CardanoIcon,
  PolkadotIcon,
} from '../assets/network_token_icons/network_token_icons'

export const getNetworkLogo = (chainId: string, symbol: string): string => {
  if (chainId === QoraiWallet.AURORA_MAINNET_CHAIN_ID) return AuroraIcon
  if (chainId === QoraiWallet.OPTIMISM_MAINNET_CHAIN_ID) return OpIcon
  if (chainId === QoraiWallet.POLYGON_MAINNET_CHAIN_ID) return MATICIcon
  if (chainId === QoraiWallet.BNB_SMART_CHAIN_MAINNET_CHAIN_ID) return BNBIcon
  if (chainId === QoraiWallet.AVALANCHE_MAINNET_CHAIN_ID) return AVAXIcon
  if (chainId === QoraiWallet.FANTOM_MAINNET_CHAIN_ID) return FtmIcon
  if (chainId === QoraiWallet.CELO_MAINNET_CHAIN_ID) return CeloIcon
  if (chainId === QoraiWallet.ARBITRUM_MAINNET_CHAIN_ID) return ArbIcon
  if (chainId === QoraiWallet.NEON_EVM_MAINNET_CHAIN_ID) return NeonIcon
  if (chainId === QoraiWallet.BASE_MAINNET_CHAIN_ID) return BaseIcon
  if (chainId === AllNetworksOption.chainId)
    return AllNetworksOption.iconUrls[0]

  switch (symbol.toUpperCase()) {
    case 'SOL':
      return SOLIcon
    case 'ETH':
      return ETHIcon
    case 'FIL':
      return FILECOINIcon
    case 'BTC':
      return BTCIcon
    case 'ZEC':
      return ZECIcon
    case 'ADA':
      return CardanoIcon
    case 'DOT':
      return PolkadotIcon
  }

  return ''
}

export const makeNativeAssetLogo = (symbol: string, chainId: string) => {
  return getNetworkLogo(
    symbol.toUpperCase() === 'ETH' ? QoraiWallet.MAINNET_CHAIN_ID : chainId,
    symbol,
  )
}

type UndefinedIf<R, T> = T extends undefined ? undefined : R
export const makeNetworkAsset = <
  T extends QoraiWallet.NetworkInfo | undefined | null,
>(
  network: T,
): UndefinedIf<QoraiWallet.BlockchainToken, T> => {
  if (!network) {
    return undefined as UndefinedIf<QoraiWallet.BlockchainToken, T>
  }

  return {
    contractAddress: '',
    name: network.symbolName,
    symbol: network.symbol,
    logo: makeNativeAssetLogo(network.symbol, network.chainId),
    isErc20: false,
    isErc721: false,
    isErc1155: false,
    isNft: false,
    isSpam: false,
    decimals: network.decimals,
    visible: true,
    tokenId: '',
    coingeckoId:
      // skip getting prices of known testnet tokens
      SupportedTestNetworks.includes(network.chainId)
        ? SKIP_PRICE_LOOKUP_COINGECKO_ID
        : '',
    chainId: network.chainId,
    coin: network.coin,
  } as UndefinedIf<QoraiWallet.BlockchainToken, T>
}
