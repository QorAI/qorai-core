// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { NativeAssetBalanceRegistry } from '../common/constants/mocks'
import { TokenBalancesRegistry } from '../common/slices/entities/token-balance.entity'
import { QoraiWallet, RewardsExternalWallet } from './types'

export interface WalletApiDataOverrides {
  selectedCoin?: QoraiWallet.CoinType
  selectedAccountId?: QoraiWallet.AccountId
  chainIdsForCoins?: Record<QoraiWallet.CoinType, string>
  networks?: QoraiWallet.NetworkInfo[]
  defaultBaseCurrency?: string
  transactionInfos?: QoraiWallet.TransactionInfo[]
  blockchainTokens?: QoraiWallet.BlockchainToken[]
  userAssets?: QoraiWallet.BlockchainToken[]
  accountInfos?: QoraiWallet.AccountInfo[]
  nativeBalanceRegistry?: NativeAssetBalanceRegistry
  tokenBalanceRegistry?: TokenBalancesRegistry
  simulationOptInStatus?: QoraiWallet.BlowfishOptInStatus
  evmSimulationResponse?: QoraiWallet.EVMSimulationResponse | null
  svmSimulationResponse?: QoraiWallet.SolanaSimulationResponse | null
  signSolTransactionsRequests?: QoraiWallet.SignSolTransactionsRequest[]
  signCardanoTransactionRequests?: QoraiWallet.SignCardanoTransactionRequest[]
}

export type QoraiRewardsProxyOverrides = Partial<{
  rewardsEnabled: boolean
  balance: number
  externalWallet: RewardsExternalWallet | null
}>
