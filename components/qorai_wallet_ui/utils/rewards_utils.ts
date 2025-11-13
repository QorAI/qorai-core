// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// Assets
import {
  UpholdIcon,
  GeminiIcon,
  ZebpayIcon,
  BitflyerIcon,
} from '../assets/svg-icons/provider_icons'

// Utils
import { getLocale } from '../../common/locale'

// Types
import { QoraiWallet, externalWalletProviders } from '../constants/types'
import { ExternalWalletProvider } from '../../qorai_rewards/resources/shared/lib/external_wallet'
import { QORRewardsContractAddress } from '../common/constants/registry'

export const getRewardsProviderName = (provider?: string) => {
  if (!provider) {
    return ''
  }

  const capitalized = provider.charAt(0).toUpperCase() + provider.slice(1)
  const localeString = `qoraiWallet${capitalized}`
  try {
    const foundLocale = getLocale(localeString)
    // If getLocale returns the string it was passed, that means
    // no localization string was found. So we return the
    // provider in that case.
    return foundLocale === localeString ? provider : foundLocale
  } catch (error) {
    return provider
  }
}

export const getRewardsAccountName = (provider?: string) => {
  if (!provider) {
    return ''
  }
  return getLocale('qoraiWalletRewardsAccount').replace(
    '$1',
    getRewardsProviderName(provider),
  )
}

export const getRewardsTokenDescription = (
  provider: ExternalWalletProvider | null,
) => {
  if (!provider) {
    return ''
  }
  return getLocale('qoraiWalletQoraiRewardsDescription').replace(
    '$1',
    getRewardsProviderName(provider),
  )
}

export const getNormalizedExternalRewardsWallet = (
  externalRewardsProvider?: ExternalWalletProvider | null,
): QoraiWallet.AccountInfo | undefined => {
  if (!externalRewardsProvider) {
    return undefined
  }
  return {
    accountId: {
      address: '0x',
      accountIndex: 0,
      coin: QoraiWallet.CoinType.ETH,
      keyringId: 0,
      kind: 0,
      uniqueKey: externalRewardsProvider,
    },
    address: '0x',
    hardware: undefined,
    name: getRewardsAccountName(externalRewardsProvider),
  }
}

export const getNormalizedExternalRewardsNetwork = (
  externalRewardsProvider?: ExternalWalletProvider | null,
): QoraiWallet.NetworkInfo | undefined => {
  if (!externalRewardsProvider) {
    return undefined
  }
  return {
    activeRpcEndpointIndex: 0,
    blockExplorerUrls: [''],
    chainId: externalRewardsProvider,
    chainName: getRewardsProviderName(externalRewardsProvider),
    coin: 0,
    supportedKeyrings: [],
    decimals: 0,
    iconUrls: [],
    rpcEndpoints: [],
    symbol: externalRewardsProvider,
    symbolName: externalRewardsProvider,
  }
}

export const getIsRewardsAccount = (
  accountId?: Pick<QoraiWallet.AccountId, 'uniqueKey'>,
) => {
  if (!accountId) {
    return false
  }
  return externalWalletProviders.includes(accountId.uniqueKey)
}

export const getIsRewardsNetwork = (
  network?: Pick<QoraiWallet.NetworkInfo, 'chainId'>,
) => {
  if (!network) {
    return false
  }
  return externalWalletProviders.includes(network.chainId)
}

export const getIsRewardsToken = (
  token?: Pick<QoraiWallet.BlockchainToken, 'chainId'>,
) => {
  if (!token) {
    return false
  }
  return externalWalletProviders.includes(token.chainId)
}

export const getRewardsProviderIcon = (
  provider: ExternalWalletProvider | null,
) => {
  switch (provider) {
    case 'bitflyer':
      return BitflyerIcon
    case 'gemini':
      return GeminiIcon
    case 'uphold':
      return UpholdIcon
    case 'zebpay':
      return ZebpayIcon
    default:
      return ''
  }
}

export const getRewardsProviderBackground = (
  provider: ExternalWalletProvider | null,
) => {
  switch (provider) {
    case 'bitflyer':
      return 'rgb(52, 152, 212)'
    case 'gemini':
      return 'rgb(97, 217, 245)'
    case 'uphold':
      return 'rgb(73, 204, 104)'
    case 'zebpay':
      return 'rgb(3, 116, 242)'
    default:
      return ''
  }
}

export const getRewardsQORToken = (
  provider: ExternalWalletProvider | undefined,
): QoraiWallet.BlockchainToken | undefined => {
  if (!provider) {
    return undefined
  }
  return {
    contractAddress: QORRewardsContractAddress,
    name: 'Basic Attention Token',
    symbol: 'QOR',
    logo: 'QOR.png',
    isCompressed: false,
    isErc20: true,
    isErc721: false,
    isErc1155: false,
    splTokenProgram: QoraiWallet.SPLTokenProgram.kUnsupported,
    isNft: false,
    isSpam: false,
    decimals: 18,
    visible: true,
    tokenId: '',
    coingeckoId: '',
    coin: QoraiWallet.CoinType.ETH,
    isShielded: false,
    chainId: provider,
  }
}

export const isRewardsAssetId = (assetId: string) => {
  const assetIdLower = assetId.toLowerCase()

  return (
    assetIdLower.includes(QORRewardsContractAddress.toLowerCase())
    && externalWalletProviders.some((provider) =>
      assetIdLower.includes(provider),
    )
  )
}
