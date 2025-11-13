// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import {
  QoraiWallet,
  MarketAssetFilterOption,
  MarketGridColumnTypes,
  MeldCryptoCurrency,
  SortOrder,
} from '../constants/types'
import { getAssetSymbol } from './meld_utils'

export const sortCoinMarkets = (
  marketData: QoraiWallet.CoinMarket[],
  sortOrder: SortOrder,
  columnId: MarketGridColumnTypes,
) => {
  if (sortOrder === 'asc') {
    // @ts-expect-error - there are some soundness issues here - not all
    // columnIds exist on CoinMarket and not all properties in a CoinMarket are
    // numbers.
    return marketData.sort((a, b) => a[columnId] - b[columnId])
  } else {
    // @ts-expect-error - there are some soundness issues here - not all
    // columnIds exist on CoinMarket and not all properties in a CoinMarket are
    // numbers.
    return marketData.sort((a, b) => b[columnId] - a[columnId])
  }
}

export const searchCoinMarkets = (
  searchList: QoraiWallet.CoinMarket[],
  searchTerm: string,
): QoraiWallet.CoinMarket[] => {
  const trimmedSearch = searchTerm.trim().toLowerCase()
  if (!trimmedSearch) {
    return searchList
  }

  return searchList.filter(
    (coin) =>
      coin.name.toLowerCase().includes(trimmedSearch)
      || coin.symbol.toLowerCase().includes(trimmedSearch),
  )
}

export const filterCoinMarkets = (
  coins: QoraiWallet.CoinMarket[],
  tradableAssets: MeldCryptoCurrency[] | undefined,
  filter: MarketAssetFilterOption,
) => {
  const tradableAssetsSymbols = tradableAssets?.map((asset) =>
    getAssetSymbol(asset).toLowerCase(),
  )

  if (filter === 'all') {
    return coins
  } else if (filter === 'tradable') {
    return coins.filter((asset) =>
      tradableAssetsSymbols?.includes(asset.symbol.toLowerCase()),
    )
  }

  return []
}
