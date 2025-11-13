// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import { QoraiWallet } from '../../constants/types'
import {
  ETHIcon,
  FILECOINIcon,
  SOLIcon,
  BTCIcon,
  BNBIcon,
} from '../../assets/network_token_icons/network_token_icons'

export const mockEthMainnet: QoraiWallet.NetworkInfo = {
  activeRpcEndpointIndex: 0,
  blockExplorerUrls: ['https://etherscan.io', 'https://etherchain.org'],
  chainId: QoraiWallet.MAINNET_CHAIN_ID,
  chainName: 'Ethereum Mainnet',
  coin: QoraiWallet.CoinType.ETH,
  supportedKeyrings: [QoraiWallet.KeyringId.kDefault],
  decimals: 18,
  iconUrls: [ETHIcon],
  rpcEndpoints: [{ url: 'https://mainnet.infura.io/v3/' }],
  symbol: 'ETH',
  symbolName: 'Ethereum',
}

export const mockSepolia: QoraiWallet.NetworkInfo = {
  activeRpcEndpointIndex: 0,
  blockExplorerUrls: ['https://sepolia.etherscan.io'],
  chainId: QoraiWallet.SEPOLIA_CHAIN_ID,
  chainName: 'Sepolia Test Network',
  coin: 60,
  supportedKeyrings: [QoraiWallet.KeyringId.kDefault],
  decimals: 18,
  iconUrls: [ETHIcon],
  rpcEndpoints: [{ url: 'https://sepolia-infura.qorai.com' }],
  symbol: 'ETH',
  symbolName: 'Ethereum',
}

export const mockEthLocalhost: QoraiWallet.NetworkInfo = {
  activeRpcEndpointIndex: 0,
  blockExplorerUrls: ['http://localhost:7545/'],
  chainId: QoraiWallet.LOCALHOST_CHAIN_ID,
  chainName: 'Localhost',
  coin: 60,
  supportedKeyrings: [QoraiWallet.KeyringId.kDefault],
  decimals: 18,
  iconUrls: [ETHIcon],
  rpcEndpoints: [{ url: 'http://localhost:7545/' }],
  symbol: 'ETH',
  symbolName: 'Ethereum',
}

export const mockFilecoinMainnetNetwork: QoraiWallet.NetworkInfo = {
  chainId: 'f',
  chainName: 'Filecoin Mainnet',
  activeRpcEndpointIndex: 0,
  rpcEndpoints: [{ url: 'https://calibration.node.glif.io/rpc/v0' }],
  blockExplorerUrls: ['https://filscan.io/tipset/message-detail'],
  symbol: 'FIL',
  symbolName: 'Filecoin',
  decimals: 18,
  iconUrls: [FILECOINIcon],
  coin: QoraiWallet.CoinType.FIL,
  supportedKeyrings: [QoraiWallet.KeyringId.kFilecoin],
}

export const mockFilecoinTestnetNetwork: QoraiWallet.NetworkInfo = {
  chainId: 't',
  chainName: 'Filecoin Testnet',
  activeRpcEndpointIndex: 0,
  rpcEndpoints: [{ url: 'https://solana-mainnet.wallet.qorai.com' }],
  blockExplorerUrls: ['https://calibration.filscan.io/tipset/message-detail'],
  symbol: 'FIL',
  symbolName: 'Filecoin',
  decimals: 18,
  iconUrls: [FILECOINIcon],
  coin: QoraiWallet.CoinType.FIL,
  supportedKeyrings: [QoraiWallet.KeyringId.kFilecoinTestnet],
}

export const mockSolanaMainnetNetwork: QoraiWallet.NetworkInfo = {
  activeRpcEndpointIndex: 0,
  blockExplorerUrls: ['https://explorer.solana.com'],
  chainId: '0x65',
  chainName: 'Solana Mainnet Beta',
  coin: QoraiWallet.CoinType.SOL,
  supportedKeyrings: [QoraiWallet.KeyringId.kSolana],
  decimals: 9,
  iconUrls: [SOLIcon],
  rpcEndpoints: [{ url: 'https://api.testnet.solana.com' }],
  symbol: 'SOL',
  symbolName: 'Solana',
}

export const mockSolanaTestnetNetwork: QoraiWallet.NetworkInfo = {
  chainId: '0x66',
  chainName: 'Solana Testnet',
  activeRpcEndpointIndex: 0,
  rpcEndpoints: [{ url: 'https://api.testnet.solana.com' }],
  blockExplorerUrls: ['https://explorer.solana.com?cluster=testnet'],
  symbol: 'SOL',
  symbolName: 'Solana',
  decimals: 9,
  iconUrls: [SOLIcon],
  coin: QoraiWallet.CoinType.SOL,
  supportedKeyrings: [QoraiWallet.KeyringId.kSolana],
}

export const mockBitcoinMainnet: QoraiWallet.NetworkInfo = {
  activeRpcEndpointIndex: 0,
  blockExplorerUrls: ['https://bitcoin.explorer'],
  chainId: 'bitcoin_mainnet',
  chainName: 'Bitcoin Mainnet',
  coin: QoraiWallet.CoinType.BTC,
  supportedKeyrings: [QoraiWallet.KeyringId.kBitcoin84],
  decimals: 8,
  iconUrls: [BTCIcon],
  rpcEndpoints: [{ url: 'https://bitcoin.rpc' }],
  symbol: 'BTC',
  symbolName: 'Bitcoin',
}

export const mockBitcoinTestnet: QoraiWallet.NetworkInfo = {
  activeRpcEndpointIndex: 0,
  blockExplorerUrls: ['https://bitcoin.explorer'],
  chainId: 'bitcoin_testnet',
  chainName: 'Bitcoin Testnet',
  coin: QoraiWallet.CoinType.BTC,
  supportedKeyrings: [QoraiWallet.KeyringId.kBitcoin84Testnet],
  decimals: 8,
  iconUrls: [BTCIcon],
  rpcEndpoints: [{ url: 'https://bitcoin.rpc/test' }],
  symbol: 'BTC',
  symbolName: 'Bitcoin',
}

export const mockBNBChainNetwork: QoraiWallet.NetworkInfo = {
  chainId: '0x38',
  chainName: 'BNB Smart Chain Mainnet',
  activeRpcEndpointIndex: 0,
  rpcEndpoints: [{ url: 'https://bsc-mainnet.wallet.qorai.com/' }],
  blockExplorerUrls: ['https://bscscan.com'],
  symbol: 'BNB',
  symbolName: 'BNB',
  decimals: 18,
  iconUrls: [BNBIcon],
  coin: QoraiWallet.CoinType.ETH,
  supportedKeyrings: [QoraiWallet.KeyringId.kDefault],
}

export const mockCardanoMainnetNetwork: QoraiWallet.NetworkInfo = {
  chainId: 'cardano_mainnet',
  chainName: 'Cardano Mainnet',
  activeRpcEndpointIndex: 0,
  rpcEndpoints: [{ url: 'https://cardano-mainnet.wallet.qorai.com/' }],
  blockExplorerUrls: ['https://cexplorer.io'],
  symbol: 'ADA',
  symbolName: 'Cardano',
  decimals: 6,
  iconUrls: [],
  coin: QoraiWallet.CoinType.ADA,
  supportedKeyrings: [QoraiWallet.KeyringId.kCardanoMainnet],
}

export const mockNetworks: QoraiWallet.NetworkInfo[] = [
  mockEthMainnet,
  mockSepolia,
  mockFilecoinMainnetNetwork,
  mockFilecoinTestnetNetwork,
  mockSolanaMainnetNetwork,
  mockSolanaTestnetNetwork,
  mockEthLocalhost,
  mockBitcoinMainnet,
  mockBNBChainNetwork,
  mockCardanoMainnetNetwork,
]
