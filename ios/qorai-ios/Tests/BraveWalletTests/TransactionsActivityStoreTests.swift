// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Combine
import Preferences
import XCTest

@testable import QoraiWallet

class TransactionsActivityStoreTests: XCTestCase {

  private var cancellables: Set<AnyCancellable> = .init()

  let networks: [QoraiWallet.CoinType: [QoraiWallet.NetworkInfo]] = [
    .eth: [.mockMainnet],
    .sol: [.mockSolana],
    .fil: [.mockFilecoinMainnet, .mockFilecoinTestnet],
  ]
  let visibleAssetsForCoins: [QoraiWallet.CoinType: [QoraiWallet.BlockchainToken]] = [
    .eth: [
      QoraiWallet.NetworkInfo.mockMainnet.nativeToken.copy(asVisibleAsset: true),
      .mockERC721NFTToken.copy(asVisibleAsset: true),
      .mockUSDCToken.copy(asVisibleAsset: true),
    ],
    .sol: [
      QoraiWallet.NetworkInfo.mockSolana.nativeToken.copy(asVisibleAsset: true),
      .mockSolanaNFTToken.copy(asVisibleAsset: true),
      .mockSpdToken.copy(asVisibleAsset: true),
    ],
    .fil: [
      QoraiWallet.NetworkInfo.mockFilecoinMainnet.nativeToken.copy(asVisibleAsset: true),
      QoraiWallet.NetworkInfo.mockFilecoinTestnet.nativeToken.copy(asVisibleAsset: true),
    ],
  ]
  let tokenRegistry: [QoraiWallet.CoinType: [QoraiWallet.BlockchainToken]] = [:]
  let mockAssetPrices: [QoraiWallet.AssetPrice] = [
    .init(
      coin: .eth,
      chainId: QoraiWallet.MainnetChainId,
      address: "",
      price: "3059.99",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    ),
    .init(
      coin: .eth,
      chainId: QoraiWallet.SepoliaChainId,
      address: "",
      price: "3059.99",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    ),
    .init(
      coin: .eth,
      chainId: QoraiWallet.MainnetChainId,
      address: QoraiWallet.BlockchainToken.mockUSDCToken.contractAddress,
      price: "1.00",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    ),
    .init(
      coin: .sol,
      chainId: QoraiWallet.SolanaMainnet,
      address: "",
      price: "2.00",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    ),
    .init(
      coin: .sol,
      chainId: QoraiWallet.SolanaTestnet,
      address: "",
      price: "2.00",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    ),
    .init(
      coin: .sol,
      chainId: QoraiWallet.SolanaMainnet,
      address: QoraiWallet.BlockchainToken.mockSpdToken.contractAddress,
      price: "0.50",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    ),
    .init(
      coin: .fil,
      chainId: QoraiWallet.FilecoinMainnet,
      address: "",
      price: "4.00",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    ),
    .init(
      coin: .fil,
      chainId: QoraiWallet.FilecoinTestnet,
      address: "",
      price: "4.00",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    ),
  ]

  func testUpdate() {
    let keyringService = QoraiWallet.TestKeyringService()
    keyringService._addObserver = { _ in }
    keyringService._allAccounts = {
      $0(.mock)
    }

    let rpcService = MockJsonRpcService()
    rpcService.hiddenNetworks.removeAll()
    rpcService._nftMetadatas = { _, completion in
      let metadata: QoraiWallet.NftMetadata = .init(
        name: "mock.nft.name",
        description: "mock.nft.description",
        image: "mock.nft.image",
        imageData: "mock.nft.image.data",
        externalUrl: "mock.nft.external.url",
        attributes: [],
        backgroundColor: "mock.nft.background.color",
        animationUrl: "mock.nft.animation.url",
        youtubeUrl: "mock.youtube.url",
        collection: "moc.nft.collection"
      )
      completion([metadata], "")
    }

    let walletService = QoraiWallet.TestQoraiWalletService()
    walletService._addObserver = { _ in }
    walletService._defaultBaseCurrency = { $0(CurrencyCode.usd.code) }

    let assetRatioService = QoraiWallet.TestAssetRatioService()
    assetRatioService._price = { _, _, completion in
      completion(true, self.mockAssetPrices)
    }

    let blockchainRegistry = QoraiWallet.TestBlockchainRegistry()
    blockchainRegistry._allTokens = { chainId, coin, completion in
      completion(self.tokenRegistry[coin] ?? [])
    }

    // Monday, November 8, 2021 7:27:51 PM
    let firstTransactionDate = Date(timeIntervalSince1970: 1_636_399_671)
    // default in mainnet
    let ethNFTSendTxCopy =
      QoraiWallet.TransactionInfo.previewERC721Send.copy() as! QoraiWallet.TransactionInfo
    // default in mainnet
    let ethSendTxCopy =
      QoraiWallet.TransactionInfo.previewConfirmedSend.copy() as! QoraiWallet.TransactionInfo
    let sepoliaSwapTxCopy =
      QoraiWallet.TransactionInfo.previewConfirmedSwap.copy() as! QoraiWallet.TransactionInfo
    sepoliaSwapTxCopy.chainId = QoraiWallet.SepoliaChainId
    let solSendTxCopy =
      QoraiWallet.TransactionInfo.previewConfirmedSolSystemTransfer.copy()
      as! QoraiWallet.TransactionInfo  // default in mainnet
    let solTestnetSendTxCopy =
      QoraiWallet.TransactionInfo.previewConfirmedSolTokenTransfer.copy()
      as! QoraiWallet.TransactionInfo
    solTestnetSendTxCopy.chainId = QoraiWallet.SolanaTestnet
    let filSendTxCopy =
      QoraiWallet.TransactionInfo.mockFilUnapprovedSend.copy() as! QoraiWallet.TransactionInfo
    let filTestnetSendTxCopy =
      QoraiWallet.TransactionInfo.mockFilUnapprovedSend.copy() as! QoraiWallet.TransactionInfo
    filTestnetSendTxCopy.chainId = QoraiWallet.FilecoinTestnet
    let txs: [QoraiWallet.TransactionInfo] = [
      ethNFTSendTxCopy, ethSendTxCopy, sepoliaSwapTxCopy,
      solSendTxCopy, solTestnetSendTxCopy,
      filSendTxCopy, filTestnetSendTxCopy,
    ]
    var timeIntervalIncrement: TimeInterval = 0
    let mockTxs: [QoraiWallet.TransactionInfo] = txs.enumerated().map { (index, tx) in
      tx.txStatus = .unapproved
      // transactions sorted by created time, make sure they are in-order
      timeIntervalIncrement += TimeInterval(index)
      if index % 2 == 0 {  // 2 transactions per day
        timeIntervalIncrement += 1.days
      }
      tx.createdTime = firstTransactionDate.addingTimeInterval(timeIntervalIncrement)
      return tx
    }

    let txService = QoraiWallet.TestTxService()
    txService._addObserver = { _ in }
    txService._allTransactionInfo = { coin, chainId, address, completion in
      completion(mockTxs.filter({ $0.chainId == chainId && $0.coin == coin }))
    }

    let solTxManagerProxy = QoraiWallet.TestSolanaTxManagerProxy()
    solTxManagerProxy._solanaTxFeeEstimation = { _, _, completion in
      completion(
        QoraiWallet.SolanaFeeEstimation(
          baseFee: UInt64(1),
          computeUnits: UInt32(0),
          feePerComputeUnit: UInt64(0)
        ),
        .success,
        ""
      )
    }

    let mockUserManager = TestableWalletUserAssetManager()
    mockUserManager._getAllUserAssetsInNetworkAssets = { [weak self] networks, _ in
      var networkAssets: [NetworkAssets] = []
      for network in networks {
        networkAssets.append(
          NetworkAssets(
            network: network,
            tokens: self?.visibleAssetsForCoins[network.coin] ?? [],
            sortOrder: 0
          )
        )
      }
      return networkAssets
    }

    let store = TransactionsActivityStore(
      keyringService: keyringService,
      rpcService: rpcService,
      walletService: walletService,
      assetRatioService: assetRatioService,
      blockchainRegistry: blockchainRegistry,
      txService: txService,
      solTxManagerProxy: solTxManagerProxy,
      ipfsApi: TestIpfsAPI(),
      userAssetManager: mockUserManager
    )

    let transactionsExpectation = expectation(description: "transactionsExpectation")
    store.$transactionSections
      .dropFirst()
      .collect(3)
      .sink { transactionSectionsUpdates in
        defer { transactionsExpectation.fulfill() }
        guard let transactionSectionsWithoutPrices = transactionSectionsUpdates.first,
          let transactionSectionsWithPrices = transactionSectionsUpdates[safe: 1],
          let transactionSectionsWithNFTMetadata = transactionSectionsUpdates[safe: 2]
        else {
          XCTFail("Expected 3 updates to transactionSummaries")
          return
        }
        let expectedTransactions = mockTxs
        // verify all transactions from supported coin types are shown
        XCTAssertEqual(
          transactionSectionsWithoutPrices.flatMap(\.transactions).count,
          expectedTransactions.count
        )
        XCTAssertEqual(
          transactionSectionsWithPrices.flatMap(\.transactions).count,
          expectedTransactions.count
        )
        // verify sections sorted by `createdTime`
        XCTAssertEqual(
          transactionSectionsWithoutPrices.map(\.date),
          transactionSectionsWithoutPrices.map(\.date).sorted(by: { $0 > $1 })
        )
        XCTAssertEqual(
          transactionSectionsWithPrices.map(\.date),
          transactionSectionsWithPrices.map(\.date).sorted(by: { $0 > $1 })
        )
        // verify transactions sorted by `createdTime`
        let expectedSortedOrder = expectedTransactions.sorted(by: {
          $0.createdTime > $1.createdTime
        })
        XCTAssertEqual(
          transactionSectionsWithoutPrices.flatMap(\.transactions).map(\.transaction.txHash),
          expectedSortedOrder.map(\.txHash)
        )
        XCTAssertEqual(
          transactionSectionsWithPrices.flatMap(\.transactions).map(\.transaction.txHash),
          expectedSortedOrder.map(\.txHash)
        )

        // verify transactions are populated with correct ParsedTransaction
        // Day 1 Transaction 1
        XCTAssertEqual(
          transactionSectionsWithoutPrices[safe: 0]?.transactions[safe: 0]?.transaction,
          filTestnetSendTxCopy
        )
        XCTAssertEqual(
          transactionSectionsWithoutPrices[safe: 0]?.transactions[safe: 0]?.transaction.chainId,
          filTestnetSendTxCopy.chainId
        )
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 0]?.transactions[safe: 0]?.transaction,
          filTestnetSendTxCopy
        )
        // Day 2 Transaction 1
        XCTAssertEqual(
          transactionSectionsWithoutPrices[safe: 1]?.transactions[safe: 0]?.transaction,
          filSendTxCopy
        )
        XCTAssertEqual(
          transactionSectionsWithoutPrices[safe: 1]?.transactions[safe: 0]?.transaction.chainId,
          filSendTxCopy.chainId
        )
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 1]?.transactions[safe: 0]?.transaction,
          filSendTxCopy
        )
        // Day 2 Transaction 2
        XCTAssertEqual(
          transactionSectionsWithoutPrices[safe: 1]?.transactions[safe: 1]?.transaction,
          solTestnetSendTxCopy
        )
        XCTAssertEqual(
          transactionSectionsWithoutPrices[safe: 1]?.transactions[safe: 1]?.transaction.chainId,
          solTestnetSendTxCopy.chainId
        )
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 1]?.transactions[safe: 1]?.transaction,
          solTestnetSendTxCopy
        )
        // Day 3 Transaction 1
        XCTAssertEqual(
          transactionSectionsWithoutPrices[safe: 2]?.transactions[safe: 0]?.transaction,
          solSendTxCopy
        )
        XCTAssertEqual(
          transactionSectionsWithoutPrices[safe: 2]?.transactions[safe: 0]?.transaction.chainId,
          solSendTxCopy.chainId
        )
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 2]?.transactions[safe: 0]?.transaction,
          solSendTxCopy
        )
        // Day 3 Transaction 2
        XCTAssertEqual(
          transactionSectionsWithoutPrices[safe: 2]?.transactions[safe: 1]?.transaction,
          sepoliaSwapTxCopy
        )
        XCTAssertEqual(
          transactionSectionsWithoutPrices[safe: 2]?.transactions[safe: 1]?.transaction.chainId,
          sepoliaSwapTxCopy.chainId
        )
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 2]?.transactions[safe: 1]?.transaction,
          sepoliaSwapTxCopy
        )
        // Day 4 Transaction 1
        XCTAssertEqual(
          transactionSectionsWithoutPrices[safe: 3]?.transactions[safe: 0]?.transaction,
          ethSendTxCopy
        )
        XCTAssertEqual(
          transactionSectionsWithoutPrices[safe: 3]?.transactions[safe: 0]?.transaction.chainId,
          ethSendTxCopy.chainId
        )
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 3]?.transactions[safe: 0]?.transaction,
          ethSendTxCopy
        )
        // Day 4 Transaction 2
        let parsedNFTTransaction = transactionSectionsWithNFTMetadata[safe: 3]?.transactions[
          safe: 1
        ]
        XCTAssertEqual(
          parsedNFTTransaction?.transaction,
          ethNFTSendTxCopy
        )
        XCTAssertEqual(
          parsedNFTTransaction?.transaction.chainId,
          ethNFTSendTxCopy.chainId
        )
        XCTAssertEqual(
          parsedNFTTransaction?.transaction,
          ethNFTSendTxCopy
        )
        if case .erc721Transfer(let details) = parsedNFTTransaction?.details {
          XCTAssertNotNil(details.nftMetadata)
        } else {
          XCTFail("Expected to find nft metadata")
        }

        XCTAssertNil(transactionSectionsWithPrices[safe: 4])

        // verify gas fee fiat
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 0]?.transactions[safe: 0]?.gasFee?.fiat,
          "$0.000000623"
        )
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 1]?.transactions[safe: 0]?.gasFee?.fiat,
          "$0.000000623"
        )
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 1]?.transactions[safe: 1]?.gasFee?.fiat,
          "$0.000000002"
        )
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 2]?.transactions[safe: 0]?.gasFee?.fiat,
          "$0.000000002"
        )
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 2]?.transactions[safe: 1]?.gasFee?.fiat,
          "$255.04"
        )
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 3]?.transactions[safe: 0]?.gasFee?.fiat,
          "$10.41"
        )
        XCTAssertEqual(
          transactionSectionsWithPrices[safe: 3]?.transactions[safe: 1]?.gasFee?.fiat,
          "$10.20"
        )
      }
      .store(in: &cancellables)

    store.update()

    waitForExpectations(timeout: 1) { error in
      XCTAssertNil(error)
    }
  }
}
