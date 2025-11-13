// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Combine
import Foundation
import XCTest

@testable import QoraiWallet

class UserAssetsStoreTests: XCTestCase {

  private var cancellables: Set<AnyCancellable> = .init()

  let nonNativeTokenVisibleAssets: [QoraiWallet.BlockchainToken] = [
    .mockERC721NFTToken.copy(asVisibleAsset: true),
    .mockSpdToken.copy(asVisibleAsset: true),
  ]
  let tokenRegistry: [QoraiWallet.CoinType: [QoraiWallet.BlockchainToken]] = [
    .eth: [.mockUSDCToken.copy(asVisibleAsset: false)]
  ]

  private func setupServices() -> (
    QoraiWallet.TestKeyringService, QoraiWallet.TestJsonRpcService,
    QoraiWallet.TestBlockchainRegistry, QoraiWallet.TestAssetRatioService,
    QoraiWallet.TestQoraiWalletService, WalletUserAssetManagerType
  ) {
    let keyringService = QoraiWallet.TestKeyringService()
    keyringService._addObserver = { _ in }

    let rpcService = MockJsonRpcService()

    let blockchainRegistry = QoraiWallet.TestBlockchainRegistry()
    blockchainRegistry._allTokens = { chainId, coin, completion in
      completion((self.tokenRegistry[coin] ?? []).filter { $0.chainId == chainId })
    }

    let assetRatioService = QoraiWallet.TestAssetRatioService()

    let walletService = QoraiWallet.TestQoraiWalletService()
    walletService._addObserver = { _ in }

    let mockAssetManager = TestableWalletUserAssetManager()
    mockAssetManager._getAllUserAssetsInNetworkAssets = { networks, _ in
      var result: [NetworkAssets] = []
      for (index, network) in networks.enumerated() {
        result.append(
          NetworkAssets(
            network: network,
            tokens: [network.nativeToken.copy(asVisibleAsset: true)]
              + self.nonNativeTokenVisibleAssets.filter { $0.chainId == network.chainId },
            sortOrder: index
          )
        )
      }
      return result
    }

    return (
      keyringService, rpcService, blockchainRegistry, assetRatioService, walletService,
      mockAssetManager
    )
  }

  func testUpdate() {
    let (
      keyringService, rpcService, blockchainRegistry, assetRatioService, walletService, assetManager
    ) =
      setupServices()

    let userAssetsStore = UserAssetsStore(
      blockchainRegistry: blockchainRegistry,
      rpcService: rpcService,
      keyringService: keyringService,
      assetRatioService: assetRatioService,
      walletService: walletService,
      ipfsApi: TestIpfsAPI(),
      userAssetManager: assetManager
    )

    let assetStoresException = expectation(description: "userAssetsStore-assetStores")
    userAssetsStore.$assetStores
      .dropFirst()
      .sink { assetStores in
        defer { assetStoresException.fulfill() }
        XCTAssertEqual(assetStores.count, 9)

        XCTAssertEqual(
          assetStores[0].token.symbol,
          QoraiWallet.NetworkInfo.mockSolana.nativeToken.symbol
        )
        XCTAssertTrue(assetStores[0].token.visible)
        XCTAssertEqual(assetStores[0].network, QoraiWallet.NetworkInfo.mockSolana)

        XCTAssertEqual(assetStores[1].token.symbol, QoraiWallet.BlockchainToken.mockSpdToken.symbol)
        XCTAssertTrue(assetStores[1].token.visible)
        XCTAssertEqual(assetStores[1].network, QoraiWallet.NetworkInfo.mockSolana)

        XCTAssertEqual(
          assetStores[2].token.symbol,
          QoraiWallet.NetworkInfo.mockMainnet.nativeToken.symbol
        )
        XCTAssertTrue(assetStores[2].token.visible)
        XCTAssertEqual(assetStores[2].network, QoraiWallet.NetworkInfo.mockMainnet)

        XCTAssertEqual(
          assetStores[3].token.symbol,
          QoraiWallet.BlockchainToken.mockERC721NFTToken.symbol
        )
        XCTAssertTrue(assetStores[3].token.visible)
        XCTAssertEqual(assetStores[3].network, QoraiWallet.NetworkInfo.mockMainnet)

        XCTAssertEqual(
          assetStores[4].token.symbol,
          QoraiWallet.BlockchainToken.mockUSDCToken.symbol
        )
        XCTAssertFalse(assetStores[4].token.visible)
        XCTAssertEqual(assetStores[4].network, QoraiWallet.NetworkInfo.mockMainnet)

        XCTAssertEqual(
          assetStores[5].token.symbol,
          QoraiWallet.NetworkInfo.mockPolygon.nativeToken.symbol
        )
        XCTAssertTrue(assetStores[5].token.visible)
        XCTAssertEqual(assetStores[5].network, QoraiWallet.NetworkInfo.mockPolygon)

        XCTAssertEqual(
          assetStores[6].token.symbol,
          QoraiWallet.NetworkInfo.mockFilecoinMainnet.nativeToken.symbol
        )
        XCTAssertTrue(assetStores[6].token.visible)
        XCTAssertEqual(assetStores[6].network, QoraiWallet.NetworkInfo.mockFilecoinMainnet)

        XCTAssertEqual(
          assetStores[7].token.symbol,
          QoraiWallet.NetworkInfo.mockBitcoinMainnet.nativeToken.symbol
        )
        XCTAssertTrue(assetStores[7].token.visible)
        XCTAssertEqual(assetStores[7].network, QoraiWallet.NetworkInfo.mockBitcoinMainnet)

        XCTAssertEqual(
          assetStores[8].token.symbol,
          QoraiWallet.NetworkInfo.mockZcashMainnet.nativeToken.symbol
        )
        XCTAssertTrue(assetStores[8].token.visible)
        XCTAssertEqual(assetStores[8].network, QoraiWallet.NetworkInfo.mockZcashMainnet)
      }
      .store(in: &cancellables)

    userAssetsStore.update()

    waitForExpectations(timeout: 1) { error in
      XCTAssertNil(error)
    }
  }

  @MainActor func testUpdateWithNetworkFilter() async {
    let (
      keyringService, rpcService, blockchainRegistry, assetRatioService, walletService, assetManager
    ) =
      setupServices()

    let userAssetsStore = UserAssetsStore(
      blockchainRegistry: blockchainRegistry,
      rpcService: rpcService,
      keyringService: keyringService,
      assetRatioService: assetRatioService,
      walletService: walletService,
      ipfsApi: TestIpfsAPI(),
      userAssetManager: assetManager
    )

    // Initial update() with all networks
    let setupException = expectation(description: "setup")
    userAssetsStore.$assetStores
      .dropFirst()  // initial
      .sink { _ in
        setupException.fulfill()
      }.store(in: &cancellables)
    userAssetsStore.update()
    await fulfillment(of: [setupException], timeout: 1)
    cancellables.removeAll()

    let assetStoresException = expectation(description: "userAssetsStore-assetStores")
    userAssetsStore.$assetStores
      .dropFirst()
      .sink { assetStores in
        defer { assetStoresException.fulfill() }
        XCTAssertEqual(assetStores.count, 3)

        XCTAssertEqual(
          assetStores[0].token.symbol,
          QoraiWallet.NetworkInfo.mockMainnet.nativeToken.symbol
        )
        XCTAssertTrue(assetStores[0].token.visible)
        XCTAssertEqual(assetStores[0].network, QoraiWallet.NetworkInfo.mockMainnet)

        XCTAssertEqual(
          assetStores[1].token.symbol,
          QoraiWallet.BlockchainToken.mockERC721NFTToken.symbol
        )
        XCTAssertTrue(assetStores[1].token.visible)
        XCTAssertEqual(assetStores[1].network, QoraiWallet.NetworkInfo.mockMainnet)

        XCTAssertEqual(
          assetStores[2].token.symbol,
          QoraiWallet.BlockchainToken.mockUSDCToken.symbol
        )
        XCTAssertFalse(assetStores[2].token.visible)
        XCTAssertEqual(assetStores[2].network, QoraiWallet.NetworkInfo.mockMainnet)
      }
      .store(in: &cancellables)

    // network filter assignment should call `update()` and update `assetStores`
    userAssetsStore.networkFilters = [.init(isSelected: true, model: .mockMainnet)]

    await fulfillment(of: [assetStoresException], timeout: 1)
  }
}
