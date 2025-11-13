// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import { QoraiWallet, CoinTypes } from '../../constants/types'

const s = 1000

export const maxBatchSizePrice = 200
export const maxConcurrentPriceRequests = 2
export const querySubscriptionOptions60s = {
  refetchOnFocus: true,
  pollingInterval: 60 * s,
  refetchOnMountOrArgChange: 60 * s,
  refetchOnReconnect: true,
}
export const querySubscriptionOptions5m = {
  refetchOnFocus: true,
  pollingInterval: 300 * s,
  refetchOnMountOrArgChange: 300 * s,
  refetchOnReconnect: true,
}
export const defaultQuerySubscriptionOptions = {
  refetchOnFocus: true,
  pollingInterval: 15 * s,
  refetchOnMountOrArgChange: 15 * s,
  refetchOnReconnect: true,
}

export const coinTypesMapping = {
  [QoraiWallet.CoinType.SOL]: CoinTypes.SOL,
  [QoraiWallet.CoinType.ETH]: CoinTypes.ETH,
  [QoraiWallet.CoinType.FIL]: CoinTypes.FIL,
  [QoraiWallet.CoinType.BTC]: CoinTypes.BTC,
  [QoraiWallet.CoinType.ZEC]: CoinTypes.ZEC,
  [QoraiWallet.CoinType.ADA]: CoinTypes.ADA,
  [QoraiWallet.CoinType.DOT]: CoinTypes.DOT,
}
