// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Combine
import XCTest

@testable import QoraiWallet

class AssetDetailStoreTests: XCTestCase {
  private var cancellables: Set<AnyCancellable> = .init()

  let mockCryptoCurrencies: [QoraiWallet.MeldCryptoCurrency] = [
    .init(
      currencyCode: "ETH",
      name: "Ethereum",
      chainCode: "ETH",
      chainName: "Ethereum",
      chainId: "0x1",
      contractAddress: nil,
      symbolImageUrl: "https://images-currency.meld.io/crypto/ETH/symbol.png"
    ),
    .init(
      currencyCode: "SOL",
      name: "Solana",
      chainCode: "SOLANA",
      chainName: "Solana",
      chainId: "0x65",
      contractAddress: nil,
      symbolImageUrl: "https://images-currency.meld.io/crypto/SOL/symbol.png"
    ),
  ]

  func testUpdateWithBlockchainToken() {
    let formatter = WalletAmountFormatter(decimalFormatStyle: .decimals(precision: 18))

    let assetRatioService = QoraiWallet.TestAssetRatioService()
    assetRatioService._price = { _, _, completion in
      completion(
        true,
        [
          .init(
            coin: .eth,
            chainId: QoraiWallet.MainnetChainId,
            address: QoraiWallet.BlockchainToken.previewToken.contractAddress,
            price: "1",
            vsCurrency: "usd",
            cacheStatus: .hit,
            source: .coingecko,
            percentageChange24h: "1"
          )
        ]
      )
    }
    assetRatioService._priceHistory = { _, _, _, completion in
      completion(true, [.init(date: Date(), price: "0.99")])
    }

    let keyringService = QoraiWallet.TestKeyringService()
    keyringService._allAccounts = { completion in
      completion(.mock)
    }
    keyringService._addObserver = { _ in }

    let mockEthBalance: Double = 1
    let ethBalanceWei =
      formatter.weiString(
        from: mockEthBalance,
        radix: .hex,
        decimals: Int(QoraiWallet.BlockchainToken.previewToken.decimals)
      ) ?? ""
    let rpcService = MockJsonRpcService()
    rpcService._balance = { _, _, _, completion in
      completion(ethBalanceWei, .success, "")
    }

    let walletService = QoraiWallet.TestQoraiWalletService()
    walletService._defaultBaseCurrency = {
      $0("usd")
    }
    walletService._addObserver = { _ in }

    let mockAssetManager = TestableWalletUserAssetManager()
    mockAssetManager._getAllUserAssetsInNetworkAssets = { _, _ in
      [NetworkAssets(network: .mockMainnet, tokens: [.previewToken], sortOrder: 0)]
    }

    let txService = QoraiWallet.TestTxService()
    txService._allTransactionInfo = {
      $3([.previewConfirmedSend])
    }
    txService._addObserver = { _ in }

    let blockchainRegistry = QoraiWallet.TestBlockchainRegistry()
    blockchainRegistry._buyTokens = {
      $2([.previewToken])
    }
    blockchainRegistry._allTokens = {
      $2([.previewToken])
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

    let swapService = QoraiWallet.TestSwapService()
    swapService._isSwapSupported = {
      $1(true)
    }

    let bitcoinWalletService = QoraiWallet.TestBitcoinWalletService()
    let zcashWalletService = QoraiWallet.TestZCashWalletService()
    let meldIntegrationService = QoraiWallet.TestMeldIntegrationService()
    meldIntegrationService._cryptoCurrencies = { _, completion in
      completion(self.mockCryptoCurrencies, nil)
    }

    // setup store
    let store = AssetDetailStore(
      assetRatioService: assetRatioService,
      keyringService: keyringService,
      rpcService: rpcService,
      walletService: walletService,
      txService: txService,
      blockchainRegistry: blockchainRegistry,
      solTxManagerProxy: solTxManagerProxy,
      ipfsApi: TestIpfsAPI(),
      swapService: swapService,
      bitcoinWalletService: bitcoinWalletService,
      zcashWalletService: zcashWalletService,
      meldIntegrationService: meldIntegrationService,
      userAssetManager: mockAssetManager,
      assetDetailType: .blockchainToken(.previewToken)
    )

    let assetDetailException = expectation(description: "update-blockchainToken")
    assetDetailException.expectedFulfillmentCount = 13
    store.$network
      .dropFirst()
      .sink { network in
        defer { assetDetailException.fulfill() }
        XCTAssertEqual(network, .mockMainnet)
      }
      .store(in: &cancellables)
    store.$meldCryptoCurrency
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertNotNil($0)
      }
      .store(in: &cancellables)
    store.$isSendSupported
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertTrue($0)
      }
      .store(in: &cancellables)
    store.$isSwapSupported
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertTrue($0)
      }
      .store(in: &cancellables)
    store.$priceHistory
      .dropFirst()
      .sink { priceHistory in
        defer { assetDetailException.fulfill() }
        XCTAssertEqual(priceHistory.count, 1)
        XCTAssertEqual(priceHistory[0].price, "0.99")
      }
      .store(in: &cancellables)
    store.$price
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertEqual($0, 1.00)
      }
      .store(in: &cancellables)
    store.$priceIsDown
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertFalse($0)
      }
      .store(in: &cancellables)
    store.$priceDelta
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertEqual($0, "1%")
      }
      .store(in: &cancellables)
    store.$nonZeroBalanceAccounts
      .dropFirst()
      .sink { accounts in
        defer { assetDetailException.fulfill() }
        XCTAssertEqual(accounts.count, 1)
        XCTAssertEqual(accounts[0].account, .mockEthAccount)
        XCTAssertEqual(accounts[0].balance, String(format: "%.4f", mockEthBalance))
        XCTAssertEqual(accounts[0].fiatBalance, "$1.00")
      }
      .store(in: &cancellables)
    store.$transactionSections
      .dropFirst()
      .collect(3)
      .sink { updates in
        defer { assetDetailException.fulfill() }
        guard let txSections = updates.last else {
          XCTFail("Unexpected transactionSections")
          return
        }
        XCTAssertEqual(txSections.count, 1)
        XCTAssertEqual(txSections.first!.transactions.count, 1)
        XCTAssertEqual(
          txSections.first!.transactions.first!.transaction.id,
          QoraiWallet.TransactionInfo.previewConfirmedSend.id
        )
      }
      .store(in: &cancellables)
    store.$isLoadingPrice
      .dropFirst()
      .collect(2)
      .sink { values in
        defer { assetDetailException.fulfill() }
        guard let value = values.last
        else {
          XCTFail("Unexpected isLoadingPrice")
          return
        }
        XCTAssertFalse(value)
      }
      .store(in: &cancellables)
    store.$isInitialState
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertFalse($0)
      }
      .store(in: &cancellables)
    store.$isLoadingChart
      .dropFirst()
      .collect(2)
      .sink { values in
        defer { assetDetailException.fulfill() }
        guard let value = values.last
        else {
          XCTFail("Unexpected isLoadingChart")
          return
        }
        XCTAssertFalse(value)
      }
      .store(in: &cancellables)

    store.update()
    wait(for: [assetDetailException], timeout: 1)
    XCTAssertTrue(store.isBuySupported)
  }

  func testUpdateWithBlockchainTokenBitcoin() {
    let formatter = WalletAmountFormatter(decimalFormatStyle: .decimals(precision: 8))

    let assetRatioService = QoraiWallet.TestAssetRatioService()
    let mockBtcPrice: Double = 63503
    assetRatioService._price = { _, _, completion in
      completion(
        true,
        [
          .init(
            coin: .btc,
            chainId: QoraiWallet.BitcoinMainnet,
            address: "",
            price: "\(mockBtcPrice)",
            vsCurrency: "usd",
            cacheStatus: .hit,
            source: .coingecko,
            percentageChange24h: "-1.72"
          )
        ]
      )
    }
    assetRatioService._priceHistory = { _, _, _, completion in
      completion(true, [.init(date: Date(), price: "62391.63")])
    }

    let keyringService = QoraiWallet.TestKeyringService()
    keyringService._allAccounts = { completion in
      completion(.mock)
    }
    keyringService._addObserver = { _ in }

    let rpcService = MockJsonRpcService()

    let walletService = QoraiWallet.TestQoraiWalletService()
    walletService._defaultBaseCurrency = {
      $0("usd")
    }
    walletService._addObserver = { _ in }

    let mockAssetManager = TestableWalletUserAssetManager()
    mockAssetManager._getAllUserAssetsInNetworkAssets = { _, _ in
      [NetworkAssets(network: .mockBitcoinMainnet, tokens: [.mockBTCToken], sortOrder: 0)]
    }

    let txService = QoraiWallet.TestTxService()
    txService._allTransactionInfo = {
      $3([])
    }
    txService._addObserver = { _ in }

    let blockchainRegistry = QoraiWallet.TestBlockchainRegistry()
    blockchainRegistry._buyTokens = {
      $2([.mockBTCToken])
    }
    blockchainRegistry._allTokens = {
      $2([.mockBTCToken])
    }

    let solTxManagerProxy = QoraiWallet.TestSolanaTxManagerProxy()

    let swapService = QoraiWallet.TestSwapService()
    swapService._isSwapSupported = {
      $1(true)
    }

    let mockBtcBalance: Double = 0.0001
    let btcBalanceSatoshi =
      formatter.weiString(
        from: mockBtcBalance,
        radix: .decimal,
        decimals: Int(QoraiWallet.BlockchainToken.mockBTCToken.decimals)
      ) ?? ""
    let bitcoinWalletService = QoraiWallet.TestBitcoinWalletService()
    bitcoinWalletService._balance = {
      $1(
        .init(
          totalBalance: UInt64(btcBalanceSatoshi) ?? 0,
          availableBalance: UInt64(btcBalanceSatoshi) ?? 0,
          pendingBalance: 0,
          balances: [:]
        ),
        nil
      )
    }
    let zcashWalletService = QoraiWallet.TestZCashWalletService()
    let meldIntegrationService = QoraiWallet.TestMeldIntegrationService()
    meldIntegrationService._cryptoCurrencies = { _, completion in
      completion(self.mockCryptoCurrencies, nil)
    }

    // setup store
    let store = AssetDetailStore(
      assetRatioService: assetRatioService,
      keyringService: keyringService,
      rpcService: rpcService,
      walletService: walletService,
      txService: txService,
      blockchainRegistry: blockchainRegistry,
      solTxManagerProxy: solTxManagerProxy,
      ipfsApi: TestIpfsAPI(),
      swapService: swapService,
      bitcoinWalletService: bitcoinWalletService,
      zcashWalletService: zcashWalletService,
      meldIntegrationService: meldIntegrationService,
      userAssetManager: mockAssetManager,
      assetDetailType: .blockchainToken(.mockBTCToken)
    )

    let assetDetailException = expectation(description: "update-blockchainToken")
    assetDetailException.expectedFulfillmentCount = 12
    store.$network
      .dropFirst()
      .sink { network in
        defer { assetDetailException.fulfill() }
        XCTAssertEqual(network, .mockBitcoinMainnet)
      }
      .store(in: &cancellables)
    store.$meldCryptoCurrency
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertNil($0)
      }
      .store(in: &cancellables)
    store.$isSendSupported
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertTrue($0)
      }
      .store(in: &cancellables)
    store.$isSwapSupported
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertTrue($0)
      }
      .store(in: &cancellables)
    store.$priceHistory
      .dropFirst()
      .sink { priceHistory in
        defer { assetDetailException.fulfill() }
        XCTAssertEqual(priceHistory.count, 1)
        XCTAssertEqual(priceHistory[0].price, "62391.63")
      }
      .store(in: &cancellables)
    store.$price
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertEqual($0, 63_503.00)
      }
      .store(in: &cancellables)
    store.$priceIsDown
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertTrue($0)
      }
      .store(in: &cancellables)
    store.$priceDelta
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertEqual($0, "-1.72%")
      }
      .store(in: &cancellables)
    store.$nonZeroBalanceAccounts
      .dropFirst()
      .sink { accounts in
        defer { assetDetailException.fulfill() }
        XCTAssertEqual(accounts.count, 1)
        XCTAssertEqual(accounts[0].account, .mockBtcAccount)
        XCTAssertEqual(accounts[0].balance, String(format: "%.4f", mockBtcBalance))
        XCTAssertEqual(accounts[0].fiatBalance, "$6.35")
      }
      .store(in: &cancellables)
    store.$isLoadingPrice
      .dropFirst()
      .collect(2)
      .sink { values in
        defer { assetDetailException.fulfill() }
        guard let value = values.last
        else {
          XCTFail("Unexpected isLoadingPrice")
          return
        }
        XCTAssertFalse(value)
      }
      .store(in: &cancellables)
    store.$isInitialState
      .dropFirst()
      .sink {
        defer { assetDetailException.fulfill() }
        XCTAssertFalse($0)
      }
      .store(in: &cancellables)
    store.$isLoadingChart
      .dropFirst()
      .collect(2)
      .sink { values in
        defer { assetDetailException.fulfill() }
        guard let value = values.last
        else {
          XCTFail("Unexpected isLoadingChart")
          return
        }
        XCTAssertFalse(value)
      }
      .store(in: &cancellables)

    store.update()
    wait(for: [assetDetailException], timeout: 1)
    XCTAssertFalse(store.isBuySupported)
  }

  func testUpdateWithCoinMarket() {
    let formatter = WalletAmountFormatter(decimalFormatStyle: .decimals(precision: 18))

    let assetRatioService = QoraiWallet.TestAssetRatioService()
    assetRatioService._price = { _, _, completion in
      completion(
        true,
        [
          .init(
            coin: .btc,
            chainId: QoraiWallet.BitcoinMainnet,
            address: "",
            price: "100000",
            vsCurrency: "usd",
            cacheStatus: .hit,
            source: .coingecko,
            percentageChange24h: "0.58"
          )
        ]
      )
    }
    assetRatioService._priceHistory = { _, _, _, completion in
      completion(true, [.init(date: Date(), price: "0.99")])
    }

    let keyringService = QoraiWallet.TestKeyringService()
    keyringService._allAccounts = { completion in
      completion(.mock)
    }
    keyringService._addObserver = { _ in }

    let mockEthBalance: Double = 1
    let ethBalanceWei =
      formatter.weiString(
        from: mockEthBalance,
        radix: .hex,
        decimals: Int(QoraiWallet.BlockchainToken.previewToken.decimals)
      ) ?? ""
    let rpcService = MockJsonRpcService()
    rpcService._balance = { _, _, _, completion in
      completion(ethBalanceWei, .success, "")
    }

    let walletService = QoraiWallet.TestQoraiWalletService()
    walletService._defaultBaseCurrency = {
      $0("usd")
    }
    walletService._addObserver = { _ in }

    let mockAssetManager = TestableWalletUserAssetManager()
    mockAssetManager._getAllUserAssetsInNetworkAssets = { _, _ in
      [NetworkAssets(network: .mockMainnet, tokens: [.previewToken], sortOrder: 0)]
    }

    let txService = QoraiWallet.TestTxService()
    txService._addObserver = { _ in }

    let blockchainRegistry = QoraiWallet.TestBlockchainRegistry()
    blockchainRegistry._buyTokens = {
      $2([.previewToken])
    }
    blockchainRegistry._allTokens = {
      $2([.previewToken])
    }

    let solTxManagerProxy = QoraiWallet.TestSolanaTxManagerProxy()
    let swapService = QoraiWallet.TestSwapService()

    let bitcoinWalletService = QoraiWallet.TestBitcoinWalletService()
    let zcashWalletService = QoraiWallet.TestZCashWalletService()
    let meldIntegrationService = QoraiWallet.TestMeldIntegrationService()
    meldIntegrationService._cryptoCurrencies = { _, completion in
      completion(self.mockCryptoCurrencies, nil)
    }

    // setup store
    var store = AssetDetailStore(
      assetRatioService: assetRatioService,
      keyringService: keyringService,
      rpcService: rpcService,
      walletService: walletService,
      txService: txService,
      blockchainRegistry: blockchainRegistry,
      solTxManagerProxy: solTxManagerProxy,
      ipfsApi: TestIpfsAPI(),
      swapService: swapService,
      bitcoinWalletService: bitcoinWalletService,
      zcashWalletService: zcashWalletService,
      meldIntegrationService: meldIntegrationService,
      userAssetManager: mockAssetManager,
      assetDetailType: .coinMarket(.mockCoinMarketBitcoin)
    )

    let assetDetailBitcoinException = expectation(description: "update-coinMarket-bitcoin")
    assetDetailBitcoinException.expectedFulfillmentCount = 10
    store.$meldCryptoCurrency
      .dropFirst()
      .sink {
        defer { assetDetailBitcoinException.fulfill() }
        XCTAssertNil($0)
      }
      .store(in: &cancellables)
    store.$isSendSupported
      .dropFirst()
      .sink {
        defer { assetDetailBitcoinException.fulfill() }
        XCTAssertFalse($0)
      }
      .store(in: &cancellables)
    store.$isSwapSupported
      .dropFirst()
      .sink {
        defer { assetDetailBitcoinException.fulfill() }
        XCTAssertFalse($0)
      }
      .store(in: &cancellables)
    store.$priceHistory
      .dropFirst()
      .sink { priceHistory in
        defer { assetDetailBitcoinException.fulfill() }
        XCTAssertEqual(priceHistory.count, 1)
        XCTAssertEqual(priceHistory[0].price, "0.99")
      }
      .store(in: &cancellables)
    store.$price
      .dropFirst()
      .sink {
        defer { assetDetailBitcoinException.fulfill() }
        XCTAssertEqual($0, 28_324.00)
      }
      .store(in: &cancellables)
    store.$priceIsDown
      .dropFirst()
      .sink {
        defer { assetDetailBitcoinException.fulfill() }
        XCTAssertFalse($0)
      }
      .store(in: &cancellables)
    store.$priceDelta
      .dropFirst()
      .sink {
        defer { assetDetailBitcoinException.fulfill() }
        XCTAssertEqual($0, "0.58%")
      }
      .store(in: &cancellables)
    store.$isLoadingPrice
      .dropFirst()
      .collect(2)
      .sink { values in
        defer { assetDetailBitcoinException.fulfill() }
        guard let value = values.last
        else {
          XCTFail("Unexpected isLoadingPrice")
          return
        }
        XCTAssertFalse(value)
      }
      .store(in: &cancellables)
    store.$isInitialState
      .dropFirst()
      .sink {
        defer { assetDetailBitcoinException.fulfill() }
        XCTAssertFalse($0)
      }
      .store(in: &cancellables)
    store.$isLoadingChart
      .dropFirst()
      .collect(2)
      .sink { values in
        defer {
          XCTAssertNil(store.network)
          XCTAssertTrue(store.nonZeroBalanceAccounts.isEmpty)
          XCTAssertTrue(store.transactionSections.isEmpty)

          assetDetailBitcoinException.fulfill()
        }
        guard let value = values.last
        else {
          XCTFail("Unexpected isLoadingChart")
          return
        }
        XCTAssertFalse(value)
      }
      .store(in: &cancellables)

    store.update()
    wait(for: [assetDetailBitcoinException], timeout: 1)
    XCTAssertFalse(store.isBuySupported)
    cancellables.removeAll()

    // setup store
    store = AssetDetailStore(
      assetRatioService: assetRatioService,
      keyringService: keyringService,
      rpcService: rpcService,
      walletService: walletService,
      txService: txService,
      blockchainRegistry: blockchainRegistry,
      solTxManagerProxy: solTxManagerProxy,
      ipfsApi: TestIpfsAPI(),
      swapService: swapService,
      bitcoinWalletService: bitcoinWalletService,
      zcashWalletService: zcashWalletService,
      meldIntegrationService: meldIntegrationService,
      userAssetManager: mockAssetManager,
      assetDetailType: .coinMarket(.mockCoinMarketEth)
    )
    let assetDetailNonBitcoinException = expectation(description: "update-coinMarket-non-bitcoin")
    assetDetailNonBitcoinException.expectedFulfillmentCount = 10
    store.$meldCryptoCurrency
      .dropFirst()
      .sink {
        defer { assetDetailNonBitcoinException.fulfill() }
        XCTAssertNotNil($0)
      }
      .store(in: &cancellables)
    store.$isSendSupported
      .dropFirst()
      .sink {
        defer { assetDetailNonBitcoinException.fulfill() }
        XCTAssertFalse($0)
      }
      .store(in: &cancellables)
    store.$isSwapSupported
      .dropFirst()
      .sink {
        defer { assetDetailNonBitcoinException.fulfill() }
        XCTAssertFalse($0)
      }
      .store(in: &cancellables)
    store.$priceHistory
      .dropFirst()
      .sink { priceHistory in
        defer { assetDetailNonBitcoinException.fulfill() }
        XCTAssertEqual(priceHistory.count, 1)
        XCTAssertEqual(priceHistory[0].price, "0.99")
      }
      .store(in: &cancellables)
    store.$price
      .dropFirst()
      .sink {
        defer { assetDetailNonBitcoinException.fulfill() }
        XCTAssertEqual($0, 1_860.57)
      }
      .store(in: &cancellables)
    store.$priceIsDown
      .dropFirst()
      .sink {
        defer { assetDetailNonBitcoinException.fulfill() }
        XCTAssertTrue($0)
      }
      .store(in: &cancellables)
    store.$priceDelta
      .dropFirst()
      .sink {
        defer {
          XCTAssertNil(store.network)
          XCTAssertTrue(store.nonZeroBalanceAccounts.isEmpty)
          XCTAssertTrue(store.transactionSections.isEmpty)

          assetDetailNonBitcoinException.fulfill()
        }
        XCTAssertEqual($0, "-0.23%")
      }
      .store(in: &cancellables)
    store.$isLoadingPrice
      .dropFirst()
      .collect(2)
      .sink { values in
        defer { assetDetailNonBitcoinException.fulfill() }
        guard let value = values.last
        else {
          XCTFail("Unexpected isLoadingPrice")
          return
        }
        XCTAssertFalse(value)
      }
      .store(in: &cancellables)
    store.$isInitialState
      .dropFirst()
      .sink {
        defer { assetDetailNonBitcoinException.fulfill() }
        XCTAssertFalse($0)
      }
      .store(in: &cancellables)
    store.$isLoadingChart
      .dropFirst()
      .collect(2)
      .sink { values in
        defer {
          XCTAssertNil(store.network)
          XCTAssertTrue(store.nonZeroBalanceAccounts.isEmpty)
          XCTAssertTrue(store.transactionSections.isEmpty)

          assetDetailNonBitcoinException.fulfill()
        }
        guard let value = values.last
        else {
          XCTFail("Unexpected isLoadingChart")
          return
        }
        XCTAssertFalse(value)
      }
      .store(in: &cancellables)

    store.update()
    wait(for: [assetDetailNonBitcoinException], timeout: 1)
    XCTAssertTrue(store.isBuySupported)
  }
}
