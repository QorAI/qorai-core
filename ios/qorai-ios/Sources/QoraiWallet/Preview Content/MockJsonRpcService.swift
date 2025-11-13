// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Foundation

#if DEBUG

/// JsonRpcService implementation used for previews and unit tests.
/// Implements default responses for commonly used functions to avoid unimplemented crashes.
/// Override `_*` functions to implement unit test specific responses as needed.
class MockJsonRpcService: QoraiWallet.TestJsonRpcService {
  static let allKnownNetworks: [QoraiWallet.NetworkInfo] = [
    .mockMainnet, .mockPolygon, .mockSepolia,
    .mockSolana, .mockSolanaTestnet,
    .mockFilecoinMainnet, .mockFilecoinTestnet,
    .mockBitcoinMainnet, .mockBitcoinTestnet,
    .mockZcashMainnet, .mockZcashTestnet,
  ]

  var selectedNetworkForCoin: [QoraiWallet.CoinType: QoraiWallet.NetworkInfo] = [
    .eth: .mockMainnet,
    .sol: .mockSolana,
    .fil: .mockFilecoinMainnet,
    .btc: .mockBitcoinMainnet,
    .zec: .mockZcashMainnet,
  ]

  var allCustomNetworks: [QoraiWallet.NetworkInfo] = []
  var hiddenNetworks: [QoraiWallet.NetworkInfo] = [
    .mockSepolia,
    .mockSolanaTestnet,
    .mockFilecoinTestnet,
    .mockBitcoinTestnet,
  ]

  override init() {
    super.init()
    self._addObserver = { _ in }
    self._allNetworks = { [weak self] completion in
      guard let self else {
        completion(Self.allKnownNetworks)
        return
      }
      completion(Self.allKnownNetworks + self.allCustomNetworks)
    }
    self._hiddenNetworks = { [weak self] _, completion in
      guard let self else {
        completion([])
        return
      }
      completion(self.hiddenNetworks.map(\.chainId))
    }
    self._addHiddenNetwork = { _, _, completion in
      completion(true)
    }
    self._removeHiddenNetwork = { _, _, completion in
      completion(true)
    }
    self._knownNetworks = { coin, completion in
      completion(Self.allKnownNetworks.filter({ $0.coin == coin }).map(\.chainId))
    }
    self._customNetworks = { [weak self] _, completion in
      guard let self else {
        completion([])
        return
      }
      completion(self.allCustomNetworks.map(\.chainId))
    }
    self._addChain = { [weak self] network, completion in
      guard let self else {
        completion("", .internalError, "Internal error")
        return
      }
      self.allCustomNetworks.append(network)
      completion(network.chainId, .success, "")
    }
    self._network = { [weak self] coin, _, completion in
      guard let self, let network = self.selectedNetworkForCoin[coin] else {
        assertionFailure("Selected network for \(coin.localizedTitle) not available.")
        return
      }
      completion(network)
    }
    self._chainIdForOrigin = { [weak self] coin, _, completion in
      guard let self, let network = self.selectedNetworkForCoin[coin] else {
        assertionFailure("Selected network for \(coin.localizedTitle) not available.")
        return
      }
      completion(network.chainId)
    }
    self._setNetwork = { [weak self] chainId, coin, _, completion in
      guard let self,
        let network = (Self.allKnownNetworks + self.allCustomNetworks).first(where: {
          $0.chainId == chainId
        })
      else {
        assertionFailure(
          "Set network for \(coin.localizedTitle) unavailable. Use addChain or add network to `allKnownNetworks`."
        )
        return
      }
      self.selectedNetworkForCoin[coin] = network
      completion(true)
    }
    self._balance = { _, coin, chainId, completion in
      completion("0", .success, "")
    }
    self._erc20TokenBalance = { _, _, _, completion in
      completion("0", .success, "")
    }
    self._erc20TokenBalances = { contractAddresses, _, _, completion in
      let erc20BalanceResults = contractAddresses.map { contractAddress in
        QoraiWallet.ERC20BalanceResult(contractAddress: contractAddress, balance: "0")
      }
      completion(erc20BalanceResults, .success, "")
    }
    self._erc20TokenAllowance = { _, _, _, _, completion in
      completion("0", .success, "")
    }
    self._solanaBalance = { accountAddress, chainId, completion in
      completion(0, .success, "")
    }
    self._splTokenAccountBalance = { _, tokenMintAddress, _, completion in
      completion("0", 0, "", .success, "")
    }
    self._splTokenBalances = { _, _, completion in
      completion([], .success, "")
    }
    self._ethTokenInfo = { _, _, completion in
      completion(nil, .resourceNotFound, "Token not found.")
    }
    self._nftMetadatas = { _, completion in
      completion([], "Error Message")
    }
    self._nftBalances = { _, _, completion in
      completion([0], "")
    }
  }
}

extension QoraiWallet.NetworkInfo {
  static let mockMainnet: QoraiWallet.NetworkInfo = .init(
    chainId: QoraiWallet.MainnetChainId,
    chainName: "Mainnet",
    blockExplorerUrls: ["https://etherscan.io"],
    iconUrls: [],
    activeRpcEndpointIndex: 0,
    rpcEndpoints: [URL(string: "https://rpc.mockchain.com")!],
    symbol: "ETH",
    symbolName: "Ethereum",
    decimals: 18,
    coin: .eth,
    supportedKeyrings: [QoraiWallet.KeyringId.default.rawValue].map(NSNumber.init(value:))
  )
  static let mockSepolia: QoraiWallet.NetworkInfo = .init(
    chainId: QoraiWallet.SepoliaChainId,
    chainName: "Sepolia",
    blockExplorerUrls: ["https://sepolia.etherscan.io"],
    iconUrls: [],
    activeRpcEndpointIndex: 0,
    rpcEndpoints: [URL(string: "https://rpc.mockchain.com")!],
    symbol: "ETH",
    symbolName: "Ethereum",
    decimals: 18,
    coin: .eth,
    supportedKeyrings: [QoraiWallet.KeyringId.default.rawValue].map(NSNumber.init(value:))
  )
  static let mockPolygon: QoraiWallet.NetworkInfo = .init(
    chainId: QoraiWallet.PolygonMainnetChainId,
    chainName: "Polygon Mainnet",
    blockExplorerUrls: [""],
    iconUrls: [],
    activeRpcEndpointIndex: 0,
    rpcEndpoints: [URL(string: "https://rpc.mockchain.com")!],
    symbol: "MATIC",
    symbolName: "MATIC",
    decimals: 18,
    coin: .eth,
    supportedKeyrings: [QoraiWallet.KeyringId.default.rawValue].map(NSNumber.init(value:))
  )
  static let mockSolana: QoraiWallet.NetworkInfo = .init(
    chainId: QoraiWallet.SolanaMainnet,
    chainName: "Solana Mainnet",
    blockExplorerUrls: [""],
    iconUrls: [],
    activeRpcEndpointIndex: 0,
    rpcEndpoints: [URL(string: "https://rpc.mockchain.com")!],
    symbol: "SOL",
    symbolName: "Solana",
    decimals: 9,
    coin: .sol,
    supportedKeyrings: [QoraiWallet.KeyringId.solana.rawValue].map(NSNumber.init(value:))
  )
  static let mockSolanaTestnet: QoraiWallet.NetworkInfo = .init(
    chainId: QoraiWallet.SolanaTestnet,
    chainName: "Solana Testnet",
    blockExplorerUrls: [""],
    iconUrls: [],
    activeRpcEndpointIndex: 0,
    rpcEndpoints: [URL(string: "https://rpc.mockchain.com")!],
    symbol: "SOL",
    symbolName: "Solana",
    decimals: 9,
    coin: .sol,
    supportedKeyrings: [QoraiWallet.KeyringId.solana.rawValue].map(NSNumber.init(value:))
  )
  static let mockFilecoinMainnet: QoraiWallet.NetworkInfo = .init(
    chainId: QoraiWallet.FilecoinMainnet,
    chainName: "Filecoin Mainnet",
    blockExplorerUrls: [""],
    iconUrls: [],
    activeRpcEndpointIndex: 0,
    rpcEndpoints: [URL(string: "https://rpc.ankr.com/filecoin")!],
    symbol: "FIL",
    symbolName: "Filecoin",
    decimals: 18,
    coin: .fil,
    supportedKeyrings: [QoraiWallet.KeyringId.filecoin.rawValue].map(NSNumber.init(value:))
  )
  static let mockFilecoinTestnet: QoraiWallet.NetworkInfo = .init(
    chainId: QoraiWallet.FilecoinTestnet,
    chainName: "Filecoin Testnet",
    blockExplorerUrls: [""],
    iconUrls: [],
    activeRpcEndpointIndex: 0,
    rpcEndpoints: [URL(string: "https://rpc.ankr.com/filecoin_testnet")!],
    symbol: "FIL",
    symbolName: "Filecoin",
    decimals: 18,
    coin: .fil,
    supportedKeyrings: [QoraiWallet.KeyringId.filecoinTestnet.rawValue].map(NSNumber.init(value:))
  )
  static let mockBitcoinMainnet: QoraiWallet.NetworkInfo = .init(
    chainId: QoraiWallet.BitcoinMainnet,
    chainName: "Bitcoin Mainnet",
    blockExplorerUrls: ["https://bitcoin.explorer"],
    iconUrls: [],
    activeRpcEndpointIndex: 0,
    rpcEndpoints: [URL(string: "https://bitcoin.rpc")!],
    symbol: "BTC",
    symbolName: "Bitcoin",
    decimals: 8,
    coin: .btc,
    supportedKeyrings: [QoraiWallet.KeyringId.bitcoin84.rawValue].map(NSNumber.init(value:))
  )
  static let mockBitcoinTestnet: QoraiWallet.NetworkInfo = .init(
    chainId: QoraiWallet.BitcoinTestnet,
    chainName: "Bitcoin Testnet",
    blockExplorerUrls: ["https://bitcoin.explorer"],
    iconUrls: [],
    activeRpcEndpointIndex: 0,
    rpcEndpoints: [URL(string: "https://bitcoin.rpc/test")!],
    symbol: "BTC",
    symbolName: "Bitcoin",
    decimals: 8,
    coin: .btc,
    supportedKeyrings: [QoraiWallet.KeyringId.bitcoin84Testnet.rawValue].map(NSNumber.init(value:))
  )
  static let mockZcashMainnet: QoraiWallet.NetworkInfo = .init(
    chainId: QoraiWallet.ZCashMainnet,
    chainName: "Zcash Mainnet",
    blockExplorerUrls: ["https://zcashblockexplorer.com/"],
    iconUrls: [],
    activeRpcEndpointIndex: 0,
    rpcEndpoints: [URL(string: "https://mainnet.lightwalletd.com/")!],
    symbol: "ZEC",
    symbolName: "Zcash",
    decimals: 8,
    coin: .zec,
    supportedKeyrings: [QoraiWallet.KeyringId.zCashMainnet.rawValue].map(NSNumber.init(value:))
  )
  static let mockZcashTestnet: QoraiWallet.NetworkInfo = .init(
    chainId: QoraiWallet.ZCashTestnet,
    chainName: "Zcash Testnet",
    blockExplorerUrls: ["https://testnet.zcashblockexplorer.com/"],
    iconUrls: [],
    activeRpcEndpointIndex: 0,
    rpcEndpoints: [URL(string: "https://testnet.lightwalletd.com")!],
    symbol: "ZEC",
    symbolName: "Zcash",
    decimals: 8,
    coin: .zec,
    supportedKeyrings: [QoraiWallet.KeyringId.zCashTestnet.rawValue].map(NSNumber.init(value:))
  )
}

#endif
