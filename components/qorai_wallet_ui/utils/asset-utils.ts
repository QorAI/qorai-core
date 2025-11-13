/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// Types
import {
  AssetIdsByCollectionNameRegistry,
  QoraiWallet,
} from '../constants/types'
import {
  TokenBalancesRegistry, //
} from '../common/slices/entities/token-balance.entity'

// utils
import Amount from './amount'
import { getRampNetworkPrefix } from './string-utils'
import { getNetworkLogo, makeNativeAssetLogo } from '../options/asset-options'
import { LOCAL_STORAGE_KEYS } from '../common/constants/local-storage-keys'
import { getBalance } from './balance-utils'

export const getUniqueAssets = (assets: QoraiWallet.BlockchainToken[]) => {
  return assets.filter((asset, index) => {
    return (
      index
      === assets.findIndex((item) => {
        return (
          item.contractAddress.toLowerCase()
            === asset.contractAddress.toLowerCase()
          && item.chainId === asset.chainId
        )
      })
    )
  })
}

export const isSelectedAssetInAssetOptions = (
  selectedAsset: QoraiWallet.BlockchainToken,
  assetOptions: QoraiWallet.BlockchainToken[],
) => {
  return (
    assetOptions.findIndex((asset) => {
      return (
        asset.contractAddress.toLowerCase()
          === selectedAsset?.contractAddress.toLowerCase()
        && asset.chainId === selectedAsset.chainId
        && asset.symbol.toLowerCase() === selectedAsset.symbol.toLowerCase()
      )
    }) !== -1
  )
}

export const getRampAssetSymbol = (
  asset: QoraiWallet.BlockchainToken,
  isOfframp?: boolean,
) => {
  if (
    asset.symbol.toUpperCase() === 'QOR'
    && asset.chainId === QoraiWallet.MAINNET_CHAIN_ID
  ) {
    // QOR is the only token on Ethereum Mainnet with a prefix on Ramp.Network
    return 'ETH_QOR'
  }

  if (
    asset.chainId === QoraiWallet.AVALANCHE_MAINNET_CHAIN_ID
    && asset.contractAddress === ''
  ) {
    return isOfframp ? 'AVAX_AVAX' : asset.symbol // AVAX native token has no prefix for buy
  }

  const rampNetworkPrefix = getRampNetworkPrefix(asset.chainId, isOfframp)
  return rampNetworkPrefix !== ''
    ? `${rampNetworkPrefix}_${asset.symbol.toUpperCase()}`
    : asset.symbol
}

export const addChainIdToToken = (
  token: QoraiWallet.BlockchainToken,
  chainId: string,
) => {
  try {
    token.chainId = chainId
    return token
  } catch {
    // the token object was immutable, return a new token object
    return {
      ...token,
      chainId: chainId,
    }
  }
}

export const addLogoToToken = (
  token: QoraiWallet.BlockchainToken,
  logo: string,
) => {
  try {
    token.logo = logo
    return token
  } catch {
    // the token object was immutable, return a new token object
    return {
      ...token,
      logo: logo,
    }
  }
}

export const QORSymbols = ['QOR', 'wQOR', 'QOR.e'] as const
export type QORSymbols = (typeof QORSymbols)[number]

export const isQOR = ({
  symbol,
}: Pick<QoraiWallet.BlockchainToken, 'symbol'>) => {
  return QORSymbols.includes(symbol.toLowerCase() as QORSymbols)
}

/**
 * alphabetically sorts tokens in this order:
 *  1. Gas
 *  2. QOR
 *  3. non-gas, non-QOR
 */
export const sortNativeAndAndQORAssetsToTop = (
  tokenList: QoraiWallet.BlockchainToken[],
) => {
  return [...tokenList].sort((a, b) => {
    // check if Gas/Fee token
    const nativeSort = Number(isNativeAsset(b)) - Number(isNativeAsset(a))
    if (nativeSort !== 0) {
      return nativeSort
    }

    // check if QOR
    const QORSort = Number(isQOR(b)) - Number(isQOR(a))
    if (QORSort !== 0) {
      return QORSort
    }

    // sort alphabetically
    return a.name.localeCompare(b.name)
  })
}

export type GetBlockchainTokenIdArg = Pick<
  QoraiWallet.BlockchainToken,
  | 'coin'
  | 'chainId'
  | 'contractAddress'
  | 'isErc721'
  | 'tokenId'
  | 'isNft'
  | 'isShielded'
>

/**
 * @param asset The token to get an id for
 * @returns an id that can be used as a react element key
 */
export const getAssetIdKey = (
  asset: Pick<
    GetBlockchainTokenIdArg,
    'contractAddress' | 'chainId' | 'tokenId' | 'coin' | 'isShielded'
  >,
) => {
  return asset.tokenId
    ? `${asset.coin}-${asset.contractAddress.toLowerCase()}-${asset.tokenId}-${
        asset.chainId
      }`
    : asset.isShielded
      ? `${asset.coin}-${asset.contractAddress.toLowerCase()}-${
          asset.chainId
        }-shielded`
      : `${asset.coin}-${asset.contractAddress.toLowerCase()}-${asset.chainId}`
}

export const findTokenByContractAddress = <
  T extends Pick<QoraiWallet.BlockchainToken, 'contractAddress'>,
>(
  contractAddress: string,
  tokensList: T[],
): T | undefined => {
  return tokensList.find(
    (token) =>
      token.contractAddress.toLowerCase() === contractAddress.toLowerCase(),
  )
}

export const findTokenBySymbol = (
  tokenSymbol: string,
  tokensList: QoraiWallet.BlockchainToken[],
) => {
  return tokensList.find(
    (token) => token.symbol.toLowerCase() === tokenSymbol.toLowerCase(),
  )
}

export const findTokenByAssetId = <
  T extends Pick<
    QoraiWallet.BlockchainToken,
    'contractAddress' | 'chainId' | 'tokenId' | 'coin' | 'isShielded'
  >,
>(
  assetId: string,
  tokensList: T[],
) => {
  return tokensList.find((t) => getAssetIdKey(t) === assetId)
}

export const isNativeAsset = (
  token: Pick<QoraiWallet.BlockchainToken, 'contractAddress' | 'isShielded'>,
) => token.contractAddress === ''

export const formatTokenBalance = (
  tokenBalanceString: string | undefined,
  selectedAsset:
    | Pick<QoraiWallet.BlockchainToken, 'decimals' | 'symbol'>
    | undefined,
  decimalPlaces?: number,
): string => {
  return tokenBalanceString
    ? new Amount(tokenBalanceString ?? '')
        .divideByDecimals(selectedAsset?.decimals ?? 18)
        .formatAsAsset(decimalPlaces ?? 6, selectedAsset?.symbol ?? '')
    : ''
}

export const checkIfTokensMatch = (
  tokenOne: QoraiWallet.BlockchainToken,
  tokenTwo: QoraiWallet.BlockchainToken,
): boolean => {
  return (
    tokenOne.symbol.toLowerCase() === tokenTwo.symbol.toLowerCase()
    && tokenOne.contractAddress.toLowerCase()
      === tokenTwo.contractAddress.toLowerCase()
    && tokenOne.chainId === tokenTwo.chainId
    && tokenOne.tokenId === tokenTwo.tokenId
  )
}

export function filterTokensByNetworks(
  assets: QoraiWallet.BlockchainToken[],
  networks: QoraiWallet.NetworkInfo[],
) {
  return assets.filter((asset) =>
    networks.some(
      (network) =>
        asset.chainId === network.chainId && asset.coin === network.coin,
    ),
  )
}

export const checkIfTokenNeedsNetworkIcon = (
  network: Pick<QoraiWallet.NetworkInfo, 'chainId' | 'symbol'>,
  contractAddress: string,
) => {
  return (
    contractAddress !== ''  // non-native asset
    // Checks if the network is not the official Ethereum network,
    // but uses ETH as gas.
    || getNetworkLogo(network.chainId, network.symbol)
      !== makeNativeAssetLogo(network.symbol, network.chainId)
  )
}

/**
 * Evaluates support for stripe
 * @returns Boolean indicating stripe support
 */
export const isStripeSupported = () =>
  navigator.language.toLowerCase() === 'en-us'

const idWithHashRegexp = new RegExp(/#(\d+)$/)
const idWithSpaceRegexp = new RegExp(/ (\d+)$/)

/** Attempts to remove the token-Id from the NFT name. Useful fro grouping NFTS
 * into like-kinds */
export function tokenNameToNftCollectionName(
  token: QoraiWallet.BlockchainToken,
) {
  if (token.name.match(idWithHashRegexp)) {
    return token.name.replace(idWithHashRegexp, '')
  }

  if (token.name.match(idWithSpaceRegexp)) {
    return token.name.replace(idWithSpaceRegexp, '')
  }

  return token.name || token.symbol
}

export const getHiddenTokenIds = (): string[] => {
  return JSON.parse(
    localStorage.getItem(LOCAL_STORAGE_KEYS.USER_HIDDEN_TOKEN_IDS) || '[]',
  )
}

export const getDeletedTokenIds = (): string[] => {
  return JSON.parse(
    localStorage.getItem(LOCAL_STORAGE_KEYS.USER_DELETED_TOKEN_IDS) || '[]',
  )
}

export const getHiddenOrDeletedTokenIdsList = () => {
  return getDeletedTokenIds().concat(getHiddenTokenIds())
}

export const isTokenIdRemoved = (tokenId: string, removedIds: string[]) => {
  return removedIds.includes(tokenId)
}

export function makeCountCollectionAssetsInRegistry(
  collectionAssetsRegistry: Record<
    string, // collection name
    QoraiWallet.BlockchainToken[]
  >,
): (
  total: number,
  currentCollectionToken: QoraiWallet.BlockchainToken,
  currentIndex: number,
  array: QoraiWallet.BlockchainToken[],
) => number {
  return (acc, collection) => {
    return acc + (collectionAssetsRegistry[collection.name]?.length ?? 0)
  }
}

export function groupSpamAndNonSpamNfts(nfts: QoraiWallet.BlockchainToken[]) {
  const results: {
    visibleUserNonSpamNfts: QoraiWallet.BlockchainToken[]
    visibleUserMarkedSpamNfts: QoraiWallet.BlockchainToken[]
  } = {
    visibleUserNonSpamNfts: [],
    visibleUserMarkedSpamNfts: [],
  }
  for (const nft of nfts) {
    if (nft.isSpam) {
      results.visibleUserMarkedSpamNfts.push(nft)
    } else {
      if (nft.visible) {
        results.visibleUserNonSpamNfts.push(nft)
      }
    }
  }
  return results
}

export function getAllSpamNftsAndIds(
  userNonSpamNftIds: string[],
  hiddenNftsIds: string[],
  deletedTokenIds: string[],
  simpleHashSpamNfts: QoraiWallet.BlockchainToken[],
  visibleUserMarkedSpamNfts: QoraiWallet.BlockchainToken[],
) {
  // filter out NFTs user has marked not spam
  // hidden NFTs, and deleted NFTs
  const excludedNftIds = userNonSpamNftIds
    .concat(hiddenNftsIds)
    .concat(deletedTokenIds)
  const simpleHashList = simpleHashSpamNfts.filter(
    (nft) => !excludedNftIds.includes(getAssetIdKey(nft)),
  )
  const simpleHashListIds = simpleHashList.map((nft) => getAssetIdKey(nft))
  // add NFTs user has marked as NFT if they are not in the list
  // to avoid duplicates
  const fullSpamList = simpleHashList.concat(
    visibleUserMarkedSpamNfts.filter(
      (nft) => !simpleHashListIds.includes(getAssetIdKey(nft)),
    ),
  )

  return [fullSpamList, fullSpamList.map((nft) => getAssetIdKey(nft))] as const
}

export const compareTokensByName = (
  a: Pick<QoraiWallet.BlockchainToken, 'name'>,
  b: Pick<QoraiWallet.BlockchainToken, 'name'>,
) => a.name.localeCompare(b.name)

export function isTokenWatchOnly(
  token: QoraiWallet.BlockchainToken,
  allAccounts: QoraiWallet.AccountInfo[],
  tokenBalancesRegistry: TokenBalancesRegistry | null | undefined,
  spamTokenBalancesRegistry: TokenBalancesRegistry | null | undefined,
) {
  return !allAccounts.some((account) => {
    const balance = getBalance(account.accountId, token, tokenBalancesRegistry)
    const spamBalance = getBalance(
      account.accountId,
      token,
      spamTokenBalancesRegistry,
    )
    return (balance && balance !== '0') || (spamBalance && spamBalance !== '0')
  })
}

export function getTokensWithBalanceForAccounts(
  tokens: QoraiWallet.BlockchainToken[],
  filteredAccounts: QoraiWallet.AccountInfo[],
  allAccounts: QoraiWallet.AccountInfo[],
  tokenBalancesRegistry: TokenBalancesRegistry | null | undefined,
  spamTokenBalancesRegistry: TokenBalancesRegistry | null | undefined,
  hideUnowned?: boolean,
) {
  if (hideUnowned) {
    return tokens.filter((token) => {
      return filteredAccounts.some((account) => {
        const balance = getBalance(
          account.accountId,
          token,
          tokenBalancesRegistry,
        )
        const spamBalance = getBalance(
          account.accountId,
          token,
          spamTokenBalancesRegistry,
        )
        return (
          (balance && balance !== '0') || (spamBalance && spamBalance !== '0')
        )
      })
    })
  }

  // skip balance checks if all accounts are selected
  if (filteredAccounts.length === allAccounts.length) {
    return tokens
  }

  return tokens.filter((token) => {
    return (
      filteredAccounts.some((account) => {
        const balance = getBalance(
          account.accountId,
          token,
          tokenBalancesRegistry,
        )
        const spamBalance = getBalance(
          account.accountId,
          token,
          spamTokenBalancesRegistry,
        )
        return (
          (balance && balance !== '0') || (spamBalance && spamBalance !== '0')
        )
      })
      // not owned by any account
      || !allAccounts.some((account) => {
        const balance = getBalance(
          account.accountId,
          token,
          tokenBalancesRegistry,
        )
        const spamBalance = getBalance(
          account.accountId,
          token,
          spamTokenBalancesRegistry,
        )
        return (
          (balance && balance !== '0') || (spamBalance && spamBalance !== '0')
        )
      })
    )
  })
}

export const searchNfts = (
  searchValue: string,
  items: QoraiWallet.BlockchainToken[],
) => {
  if (searchValue === '') {
    return items
  }

  return items.filter((item) => {
    const tokenId = new Amount(item.tokenId).toNumber().toString()
    const searchValueLower = searchValue.toLowerCase()
    return (
      item.name.toLocaleLowerCase().includes(searchValueLower)
      || item.symbol.toLocaleLowerCase().includes(searchValueLower)
      || tokenId.includes(searchValueLower)
    )
  })
}

export const searchNftCollectionsAndGetTotalNftsFound = (
  searchValue: string,
  collections: QoraiWallet.BlockchainToken[],
  collectionAssetsRegistry: Record<
    string, // collection name
    QoraiWallet.BlockchainToken[]
  >,
): {
  foundCollections: QoraiWallet.BlockchainToken[]
  totalNftsFound: number
} => {
  const searchValueLower = searchValue.toLowerCase().trim()

  const countCollectionAssets = makeCountCollectionAssetsInRegistry(
    collectionAssetsRegistry,
  )

  if (searchValueLower === '') {
    return {
      foundCollections: collections,
      // count all nfts in categories
      totalNftsFound: collections.reduce(countCollectionAssets, 0),
    }
  }

  const foundCollections = collections.filter((collection) => {
    // search collection name first
    if (collection.name.toLocaleLowerCase().includes(searchValueLower)) {
      return true
    }

    // search collection assets and count how many NFTs were found
    return collectionAssetsRegistry[collection.name]?.some((asset) => {
      const tokenId = new Amount(asset.tokenId).toNumber().toString()
      return (
        asset.name.toLocaleLowerCase().includes(searchValueLower)
        || asset.symbol.toLocaleLowerCase().includes(searchValueLower)
        || tokenId.includes(searchValueLower)
        || asset.contractAddress
          .toLocaleLowerCase()
          .startsWith(searchValueLower)
      )
    })
  })

  return {
    foundCollections,
    totalNftsFound: foundCollections.reduce(countCollectionAssets, 0),
  }
}

export function getTokenCollectionName(
  collectionNames: string[],
  assetIdsByCollectionNameRegistry:
    | AssetIdsByCollectionNameRegistry
    | undefined,
  token: QoraiWallet.BlockchainToken,
) {
  if (!assetIdsByCollectionNameRegistry) {
    return tokenNameToNftCollectionName(token)
  }

  return (
    collectionNames.find((collectionName) => {
      return assetIdsByCollectionNameRegistry[collectionName].includes(
        // token id is not used in the collection name registry to reduce size
        getAssetIdKey({ ...token, tokenId: '' }),
      )
    }) || tokenNameToNftCollectionName(token)
  )
}

export function getCoinTypeName(coin: QoraiWallet.CoinType) {
  switch (coin) {
    case QoraiWallet.CoinType.FIL:
      return 'Filecoin'
    case QoraiWallet.CoinType.ETH:
      return 'Ethereum'
    case QoraiWallet.CoinType.SOL:
      return 'Solana'
    case QoraiWallet.CoinType.BTC:
      return 'Bitcoin'
    case QoraiWallet.CoinType.ZEC:
      return 'ZCash'
  }
  return ''
}

export const getDoesCoinSupportSwapOrBridge = (coin: QoraiWallet.CoinType) => {
  return [QoraiWallet.CoinType.ETH, QoraiWallet.CoinType.SOL].includes(coin)
}
