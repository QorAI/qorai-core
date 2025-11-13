// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import { QoraiWallet, NetworkFilterType } from '../constants/types'
import { getLocale } from '../../common/locale'
import AllNetworksIcon from '../assets/svg-icons/all-networks-icon.svg'
import { getNetworkId } from '../common/slices/entities/network.entity'

export const AllNetworksOption: QoraiWallet.NetworkInfo = {
  blockExplorerUrls: [],
  chainId: 'all',
  chainName: getLocale('qoraiWalletNetworkFilterAll'),
  coin: 0,
  decimals: 0,
  iconUrls: [AllNetworksIcon],
  activeRpcEndpointIndex: 0,
  rpcEndpoints: [],
  symbol: 'all',
  symbolName: 'all',
  supportedKeyrings: [],
}

export const AllNetworksOptionNetworkId = getNetworkId(AllNetworksOption)

export const AllNetworksOptionDefault: NetworkFilterType = {
  chainId: 'all',
  coin: 0,
}

export const SupportedTopLevelChainIds = [
  QoraiWallet.MAINNET_CHAIN_ID,
  QoraiWallet.SOLANA_MAINNET,
  QoraiWallet.FILECOIN_MAINNET,
  QoraiWallet.BITCOIN_MAINNET,
  QoraiWallet.Z_CASH_MAINNET,
  QoraiWallet.CARDANO_MAINNET,
  QoraiWallet.POLKADOT_MAINNET,
]
