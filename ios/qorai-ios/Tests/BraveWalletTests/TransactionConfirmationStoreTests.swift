// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Combine
import Preferences
import XCTest

@testable import QoraiWallet

class TransactionConfirmationStoreTests: XCTestCase {

  private var cancellables: Set<AnyCancellable> = .init()

  private func setupStore(
    accountInfos: [QoraiWallet.AccountInfo] = [
      .mockEthAccount, .mockSolAccount, .mockFilAccount, .mockBtcAccount,
    ],
    allTokens: [QoraiWallet.BlockchainToken] = [],
    transactions: [QoraiWallet.TransactionInfo] = [],
    gasEstimation: QoraiWallet.GasEstimation1559 = .init(),
    makeErc20ApproveDataSuccess: Bool = true,
    setDataForUnapprovedTransactionSuccess: Bool = true
  ) -> TransactionConfirmationStore {
    let mockEthAssetPrice: QoraiWallet.AssetPrice = .init(
      coin: .eth,
      chainId: QoraiWallet.MainnetChainId,
      address: "",
      price: "3059.99",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    )
    let mockSolAssetPrice: QoraiWallet.AssetPrice = .init(
      coin: .sol,
      chainId: QoraiWallet.SolanaMainnet,
      address: "",
      price: "39.57",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    )
    let mockFilAssetPrice: QoraiWallet.AssetPrice = .init(
      coin: .fil,
      chainId: QoraiWallet.FilecoinMainnet,
      address: "",
      price: "4.0",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    )
    let mockBtcAssetPrice: QoraiWallet.AssetPrice = .init(
      coin: .btc,
      chainId: QoraiWallet.BitcoinMainnet,
      address: "",
      price: "62117.0",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-57.23"
    )
    let mockZECAssetPrice: QoraiWallet.AssetPrice = .init(
      coin: .zec,
      chainId: QoraiWallet.ZCashMainnet,
      address: "",
      price: "36.24",
      vsCurrency: "usd",
      cacheStatus: .hit,
      source: .coingecko,
      percentageChange24h: "-0.13"
    )
    let formatter = WalletAmountFormatter(decimalFormatStyle: .decimals(precision: 18))
    let mockBalanceWei = formatter.weiString(from: 0.0896, radix: .hex, decimals: 18) ?? ""
    let mockFILBalanceWei = formatter.weiString(from: 1, decimals: 18) ?? ""
    // setup test services
    let assetRatioService = QoraiWallet.TestAssetRatioService()
    assetRatioService._price = { _, _, completion in
      completion(
        true,
        [
          mockEthAssetPrice,
          mockSolAssetPrice,
          mockFilAssetPrice,
          mockBtcAssetPrice,
          mockZECAssetPrice,
        ]
      )
    }
    let rpcService = MockJsonRpcService()
    rpcService.hiddenNetworks.removeAll()
    rpcService._balance = { _, coin, _, completion in
      if coin == .eth {
        completion(mockBalanceWei, .success, "")
      } else {  // .fil
        completion(mockFILBalanceWei, .success, "")
      }
    }
    rpcService._erc20TokenAllowance = { _, _, _, _, completion in
      completion("16345785d8a0000", .success, "")  // 0.1000
    }
    rpcService._code = { _, _, _, completion in
      completion("0x", .success, "")
    }
    let txService = QoraiWallet.TestTxService()
    txService._addObserver = { _ in }
    txService._allTransactionInfo = { coin, chainId, address, completion in
      let filteredTransactions = transactions.filter {
        if let chainId = chainId {
          return $0.coin == coin && $0.chainId == chainId
        } else {
          return $0.coin == coin
        }
      }
      completion(filteredTransactions)
    }
    txService._approveTransaction = { _, _, _, completion in
      completion(true, .init(providerError: .success), "")
    }
    let blockchainRegistry = QoraiWallet.TestBlockchainRegistry()
    blockchainRegistry._allTokens = { _, _, completion in
      completion(allTokens)
    }
    let walletService = QoraiWallet.TestQoraiWalletService()
    walletService._defaultBaseCurrency = { $0(CurrencyCode.usd.code) }
    walletService._addObserver = { _ in }
    let mockAssetManager = TestableWalletUserAssetManager()
    mockAssetManager._getAllUserAssetsInNetworkAssets = { _, _ in
      []
    }
    let ethTxManagerProxy = QoraiWallet.TestEthTxManagerProxy()
    ethTxManagerProxy._gasEstimation1559 = { _, completion in
      completion(gasEstimation)
    }
    ethTxManagerProxy._makeErc20ApproveData = { _, _, completion in
      completion(makeErc20ApproveDataSuccess, [])
    }
    ethTxManagerProxy._setDataForUnapprovedTransaction = { _, _, _, completion in
      completion(setDataForUnapprovedTransactionSuccess)
    }
    let keyringService = QoraiWallet.TestKeyringService()
    keyringService._allAccounts = {
      $0(
        .init(
          accounts: accountInfos,
          selectedAccount: accountInfos.first,
          ethDappSelectedAccount: accountInfos.first(where: { $0.coin == .eth }),
          solDappSelectedAccount: accountInfos.first(where: { $0.coin == .sol }),
          adaDappSelectedAccount: nil
        )
      )
    }

    let solTxManagerProxy = QoraiWallet.TestSolanaTxManagerProxy()
    let feeEstimation = QoraiWallet.SolanaFeeEstimation(
      baseFee: UInt64(0),
      computeUnits: UInt32(0),
      feePerComputeUnit: UInt64(0)
    )

    solTxManagerProxy._solanaTxFeeEstimation = { $2(feeEstimation, .success, "") }

    let bitcoinWalletService = QoraiWallet.TestBitcoinWalletService()
    bitcoinWalletService._balance = { accountId, completion in
      let bitcoinBalance: QoraiWallet.BitcoinBalance = .init(
        totalBalance: 100000,
        availableBalance: 100000,
        pendingBalance: 0,
        balances: [:]
      )
      completion(bitcoinBalance, "")
    }

    let zcashWalletService = QoraiWallet.TestZCashWalletService()

    return TransactionConfirmationStore(
      assetRatioService: assetRatioService,
      rpcService: rpcService,
      txService: txService,
      blockchainRegistry: blockchainRegistry,
      walletService: walletService,
      ethTxManagerProxy: ethTxManagerProxy,
      keyringService: keyringService,
      solTxManagerProxy: solTxManagerProxy,
      bitcoinWalletService: bitcoinWalletService,
      zcashWalletService: zcashWalletService,
      ipfsApi: TestIpfsAPI(),
      userAssetManager: mockAssetManager
    )
  }

  /// Test `prepare()`  update `state` data for symbol, value, isUnlimitedApprovalRequested.
  @MainActor func testPrepareSolSystemTransfer() async {
    let mockAllTokens: [QoraiWallet.BlockchainToken] = [.mockSolToken, .mockSpdToken]
    let mockTransaction: QoraiWallet.TransactionInfo = .previewConfirmedSolSystemTransfer
    let mockTransactions: [QoraiWallet.TransactionInfo] = [mockTransaction].map { tx in
      tx.txStatus = .unapproved
      return tx
    }
    let mockGasEstimation: QoraiWallet.GasEstimation1559 = .init()
    let store = setupStore(
      accountInfos: [.mockSolAccount],
      allTokens: mockAllTokens,
      transactions: mockTransactions,
      gasEstimation: mockGasEstimation
    )
    let prepareExpectation = expectation(description: "prepare")
    await store.prepare()
    store.$activeTransactionId
      .sink { id in
        defer { prepareExpectation.fulfill() }
        XCTAssertEqual(id, mockTransaction.id)
      }
      .store(in: &cancellables)

    store.$gasValue
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, "0")
      }
      .store(in: &cancellables)

    store.$gasSymbol
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, QoraiWallet.BlockchainToken.mockSolToken.symbol)
      }
      .store(in: &cancellables)
    store.$symbol
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, QoraiWallet.BlockchainToken.mockSolToken.symbol)
      }
      .store(in: &cancellables)
    store.$value
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, "0.1")
      }
      .store(in: &cancellables)
    store.$isUnlimitedApprovalRequested
      .dropFirst()
      .sink { value in
        XCTAssertFalse(value)  // .mockSpdToken has 6 decimals
      }
      .store(in: &cancellables)

    await fulfillment(of: [prepareExpectation], timeout: 1)
  }

  /// Test `prepare()`  update `state` data for symbol, value, isUnlimitedApprovalRequested.
  @MainActor func testPrepareSolTokenTransfer() async {
    let mockAllTokens: [QoraiWallet.BlockchainToken] = [.mockSolToken, .mockSpdToken]
    let mockTransaction: QoraiWallet.TransactionInfo = .previewConfirmedSolTokenTransfer
    let mockTransactions: [QoraiWallet.TransactionInfo] = [mockTransaction].map { tx in
      tx.txStatus = .unapproved
      return tx
    }
    let mockGasEstimation: QoraiWallet.GasEstimation1559 = .init()
    let store = setupStore(
      accountInfos: [.mockSolAccount],
      allTokens: mockAllTokens,
      transactions: mockTransactions,
      gasEstimation: mockGasEstimation
    )
    let prepareExpectation = expectation(description: "prepare")
    await store.prepare()
    store.$activeTransactionId
      .sink { id in
        defer { prepareExpectation.fulfill() }
        XCTAssertEqual(id, mockTransaction.id)
      }
      .store(in: &cancellables)

    store.$gasValue
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, "0")
      }
      .store(in: &cancellables)

    store.$gasSymbol
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, QoraiWallet.BlockchainToken.mockSolToken.symbol)
      }
      .store(in: &cancellables)
    store.$symbol
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, QoraiWallet.BlockchainToken.mockSpdToken.symbol)
      }
      .store(in: &cancellables)
    store.$value
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, "100")  // .mockSpdToken has 6 decimals
      }
      .store(in: &cancellables)
    store.$isUnlimitedApprovalRequested
      .dropFirst()
      .sink { value in
        XCTAssertFalse(value)  // .mockSpdToken has 6 decimals
      }
      .store(in: &cancellables)

    await fulfillment(of: [prepareExpectation], timeout: 1)
  }

  /// Test `prepare()`  update `state` data for symbol, value, isUnlimitedApprovalRequested.
  @MainActor func testPrepareERC20Approve() async {
    let mockAllTokens: [QoraiWallet.BlockchainToken] = [.previewToken, .daiToken]
    let mockTransaction: QoraiWallet.TransactionInfo = .previewConfirmedERC20Approve
    let mockTransactions: [QoraiWallet.TransactionInfo] = [mockTransaction].map { tx in
      tx.txStatus = .unapproved
      return tx
    }
    let mockGasEstimation: QoraiWallet.GasEstimation1559 = .init()
    let store = setupStore(
      accountInfos: [.mockEthAccount],
      allTokens: mockAllTokens,
      transactions: mockTransactions,
      gasEstimation: mockGasEstimation
    )
    let prepareExpectation = expectation(description: "prepare")
    await store.prepare()
    store.$activeTransactionId
      .sink { id in
        defer { prepareExpectation.fulfill() }
        XCTAssertEqual(id, mockTransaction.id)
      }
      .store(in: &cancellables)
    store.$gasSymbol
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, QoraiWallet.BlockchainToken.previewToken.symbol)
      }
      .store(in: &cancellables)
    store.$symbol
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, QoraiWallet.BlockchainToken.daiToken.symbol)
      }
      .store(in: &cancellables)
    store.$value
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, "Unlimited")
      }
      .store(in: &cancellables)
    store.$isUnlimitedApprovalRequested
      .dropFirst()
      .collect(2)
      .sink { values in
        XCTAssertNotNil(values.last)
        XCTAssertTrue(values.last!)
      }
      .store(in: &cancellables)
    store.$currentAllowance
      .dropFirst()
      .collect(5)
      .sink { values in
        XCTAssertNotNil(values.last)
        XCTAssertEqual(values.last!, "0.1000")
      }
      .store(in: &cancellables)

    await fulfillment(of: [prepareExpectation], timeout: 1)
  }

  /// Test that `nextTransaction` will update `activeTransactionId` property in order of transaction created time.
  @MainActor func testNextTransaction() async {
    // Monday, November 8, 2021 7:27:51 PM
    let firstTransactionDate = Date(timeIntervalSince1970: 1_636_399_671)
    let sendCopy =
      QoraiWallet.TransactionInfo.previewConfirmedSend.copy() as! QoraiWallet.TransactionInfo
    sendCopy.chainId = QoraiWallet.SepoliaChainId
    sendCopy.txStatus = .unapproved
    let swapCopy =
      QoraiWallet.TransactionInfo.previewConfirmedSwap.copy() as! QoraiWallet.TransactionInfo
    swapCopy.chainId = QoraiWallet.MainnetChainId
    swapCopy.txStatus = .unapproved
    let solanaSendCopy =
      QoraiWallet.TransactionInfo.previewConfirmedSolSystemTransfer.copy()
      as! QoraiWallet.TransactionInfo
    solanaSendCopy.chainId = QoraiWallet.SolanaMainnet
    let solanaSPLSendCopy =
      QoraiWallet.TransactionInfo.previewConfirmedSolTokenTransfer.copy()
      as! QoraiWallet.TransactionInfo
    solanaSPLSendCopy.chainId = QoraiWallet.SolanaTestnet
    let filecoinSendCopy =
      QoraiWallet.TransactionInfo.mockFilUnapprovedSend.copy() as! QoraiWallet.TransactionInfo
    filecoinSendCopy.chainId = QoraiWallet.FilecoinMainnet
    let pendingTransactions: [QoraiWallet.TransactionInfo] = [
      sendCopy, swapCopy, solanaSendCopy, solanaSPLSendCopy, filecoinSendCopy,
    ].enumerated().map { (index, tx) in
      tx.txStatus = .unapproved
      // transactions sorted by created time, make sure they are in-order
      tx.createdTime = firstTransactionDate.addingTimeInterval(TimeInterval(index))
      return tx
    }
    let allTokens: [QoraiWallet.BlockchainToken] = [.previewToken, .daiToken]
    let store = setupStore(
      allTokens: allTokens,
      transactions: pendingTransactions
    )
    let activeTransactionIdExpectation = expectation(description: "activeTransactionId-expectation")
    store.$activeTransactionId
      .dropFirst()
      .collect(5)  // collect all transactions
      .sink { activeTransactionIds in
        defer { activeTransactionIdExpectation.fulfill() }
        XCTAssertEqual(activeTransactionIds.count, 5)
        XCTAssertEqual(activeTransactionIds[safe: 0], pendingTransactions[safe: 4]?.id)
        XCTAssertEqual(activeTransactionIds[safe: 1], pendingTransactions[safe: 3]?.id)
        XCTAssertEqual(activeTransactionIds[safe: 2], pendingTransactions[safe: 2]?.id)
        XCTAssertEqual(activeTransactionIds[safe: 3], pendingTransactions[safe: 1]?.id)
        XCTAssertEqual(activeTransactionIds[safe: 4], pendingTransactions[safe: 0]?.id)
      }
      .store(in: &cancellables)

    await store.prepare()  // `sendCopy` on Sepolia Testnet
    store.nextTransaction()  // `swapCopy` on Ethereum Mainnet
    store.nextTransaction()  // `solanaSendCopy` on Solana Mainnet
    store.nextTransaction()  // `solanaSPLSendCopy` on Solana Testnet
    store.nextTransaction()  // `filecoinSendCopy` on filecoin mainnet
    await fulfillment(of: [activeTransactionIdExpectation], timeout: 1)
  }

  /// Test `editAllowance(txMetaId:spenderAddress:amount:completion)` will return false if we fail to make ERC20 approve data with `QoraiWalletEthTxManagerProxy`
  @MainActor func testEditAllowanceFailMakeERC20ApproveData() async {
    let mockAllTokens: [QoraiWallet.BlockchainToken] = [.previewToken, .daiToken]
    let mockTransaction: QoraiWallet.TransactionInfo = .previewConfirmedERC20Approve
    let mockTransactions: [QoraiWallet.TransactionInfo] = [mockTransaction].map { tx in
      tx.txStatus = .unapproved
      return tx
    }
    let mockGasEstimation: QoraiWallet.GasEstimation1559 = .init()
    let store = setupStore(
      accountInfos: [.mockEthAccount],
      allTokens: mockAllTokens,
      transactions: mockTransactions,
      gasEstimation: mockGasEstimation,
      makeErc20ApproveDataSuccess: false
    )

    let prepareExpectation = expectation(description: "prepare")
    await store.prepare()
    store.$activeTransactionId
      .sink { id in
        defer { prepareExpectation.fulfill() }
        XCTAssertEqual(id, mockTransaction.id)
      }
      .store(in: &cancellables)
    await fulfillment(of: [prepareExpectation], timeout: 1)

    let editExpectation = expectation(description: "edit allowance")
    store.editAllowance(
      transaction: mockTransaction,
      spenderAddress: mockTransaction.txArgs[safe: 0] ?? "",
      amount: "0x0",
      completion: { success in
        if !success {
          editExpectation.fulfill()
        }
      }
    )
    await fulfillment(of: [editExpectation], timeout: 1)
  }

  /// Test `editAllowance(txMetaId:spenderAddress:amount:completion)` will return false if we fail to set new ERC20 Approve data with `QoraiWalletEthTxManagerProxy`
  @MainActor func testEditAllowanceFailSetData() async {
    let mockAllTokens: [QoraiWallet.BlockchainToken] = [.previewToken, .daiToken]
    let mockTransaction: QoraiWallet.TransactionInfo = .previewConfirmedERC20Approve
    let mockTransactions: [QoraiWallet.TransactionInfo] = [mockTransaction].map { tx in
      tx.txStatus = .unapproved
      return tx
    }
    let mockGasEstimation: QoraiWallet.GasEstimation1559 = .init()
    let store = setupStore(
      accountInfos: [.mockEthAccount],
      allTokens: mockAllTokens,
      transactions: mockTransactions,
      gasEstimation: mockGasEstimation,
      makeErc20ApproveDataSuccess: true,
      setDataForUnapprovedTransactionSuccess: false
    )

    let prepareExpectation = expectation(description: "prepare")
    await store.prepare()
    store.$activeTransactionId
      .sink { id in
        defer { prepareExpectation.fulfill() }
        XCTAssertEqual(id, mockTransaction.id)
      }
      .store(in: &cancellables)
    await fulfillment(of: [prepareExpectation], timeout: 1)

    let editExpectation = expectation(description: "edit allowance")
    store.editAllowance(
      transaction: mockTransaction,
      spenderAddress: mockTransaction.txArgs[safe: 0] ?? "",
      amount: "0x0",
      completion: { success in
        if !success {
          editExpectation.fulfill()
        }
      }
    )
    await fulfillment(of: [editExpectation], timeout: 1)
  }

  /// Test `editAllowance(txMetaId:spenderAddress:amount:completion)` will return true if we suceed in creating and setting ERC20 Approve data with `QoraiWalletEthTxManagerProxy`
  @MainActor func testEditAllowanceSuccess() async {
    let mockAllTokens: [QoraiWallet.BlockchainToken] = [.previewToken, .daiToken]
    let mockTransaction: QoraiWallet.TransactionInfo = .previewConfirmedERC20Approve
    let mockTransactions: [QoraiWallet.TransactionInfo] = [mockTransaction].map { tx in
      tx.txStatus = .unapproved
      return tx
    }
    let mockGasEstimation: QoraiWallet.GasEstimation1559 = .init()
    let store = setupStore(
      accountInfos: [.mockEthAccount],
      allTokens: mockAllTokens,
      transactions: mockTransactions,
      gasEstimation: mockGasEstimation,
      makeErc20ApproveDataSuccess: true,
      setDataForUnapprovedTransactionSuccess: true
    )

    let prepareExpectation = expectation(description: "prepare")
    await store.prepare()
    store.$activeTransactionId
      .sink { id in
        defer { prepareExpectation.fulfill() }
        XCTAssertEqual(id, mockTransaction.id)
      }
      .store(in: &cancellables)
    await fulfillment(of: [prepareExpectation], timeout: 1)

    let editExpectation = expectation(description: "edit allowance")
    store.editAllowance(
      transaction: mockTransaction,
      spenderAddress: mockTransaction.txArgs[safe: 0] ?? "",
      amount: "0x0",
      completion: { success in
        if success {
          editExpectation.fulfill()
        }
      }
    )
    await fulfillment(of: [editExpectation], timeout: 1)
  }

  @MainActor func testPrepareFilSend() async {
    let mockAllTokens: [QoraiWallet.BlockchainToken] = [.mockFilToken]
    let mockTransaction: QoraiWallet.TransactionInfo = .mockFilUnapprovedSend
    let mockTransactions: [QoraiWallet.TransactionInfo] = [mockTransaction].map { tx in
      tx.txStatus = .unapproved
      return tx
    }
    let store = setupStore(
      accountInfos: [.mockFilAccount],
      allTokens: mockAllTokens,
      transactions: mockTransactions
    )
    let prepareExpectation = expectation(description: "prepare")
    await store.prepare()
    store.$activeTransactionId
      .sink { id in
        defer { prepareExpectation.fulfill() }
        XCTAssertEqual(id, mockTransaction.id)
      }
      .store(in: &cancellables)
    store.$gasValue
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, "0.000000155797727645")
      }
      .store(in: &cancellables)
    store.$gasSymbol
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, QoraiWallet.BlockchainToken.mockFilToken.symbol)
      }
      .store(in: &cancellables)
    store.$symbol
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, QoraiWallet.BlockchainToken.mockFilToken.symbol)
      }
      .store(in: &cancellables)
    store.$value
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, "1")
      }
      .store(in: &cancellables)

    await fulfillment(of: [prepareExpectation], timeout: 1)
  }

  private let isTxSubmittingMockTransaction: QoraiWallet.TransactionInfo = .previewConfirmedSend
    .then { $0.txStatus = .unapproved }
  private func setupStoreForTxSubmitting() async -> TransactionConfirmationStore {
    let store = setupStore(
      accountInfos: [.mockEthAccount],
      allTokens: [.previewToken],
      transactions: [isTxSubmittingMockTransaction],
      gasEstimation: .init()
    )
    await store.prepare()
    return store
  }

  /// Test `isTxSubmitting` happy path (unapproved -> approved -> submitted)
  @MainActor func testIsTxSubmittingHappyPath() async {
    let store = await setupStoreForTxSubmitting()
    XCTAssertFalse(store.isTxSubmitting)
    let error = await store.confirm(transaction: isTxSubmittingMockTransaction)
    XCTAssertNil(error)
    XCTAssertTrue(store.isTxSubmitting)
    // simulate transaction status moved to approved
    let mockTransactionApproved = isTxSubmittingMockTransaction.then {
      $0.txStatus = .approved
    }
    store.onTransactionStatusChanged(mockTransactionApproved)
    XCTAssertTrue(store.isTxSubmitting)  // waiting for submitted state
    // simulate transaction status moved to submitted
    let mockTransactionSubmitted = isTxSubmittingMockTransaction.then {
      $0.txStatus = .submitted
    }
    store.onTransactionStatusChanged(mockTransactionSubmitted)
    XCTAssertFalse(store.isTxSubmitting)
  }

  /// Test `isTxSubmitting` will correctly update to false when transaction moves to error tx status. qorai-browser#38375
  @MainActor func testIsTxSubmittingError() async {
    let store = await setupStoreForTxSubmitting()
    XCTAssertFalse(store.isTxSubmitting)
    let error = await store.confirm(transaction: isTxSubmittingMockTransaction)
    XCTAssertNil(error)
    XCTAssertTrue(store.isTxSubmitting)
    // simulate transaction status moved directly to error
    let mockTransactionSubmitted = isTxSubmittingMockTransaction.then {
      $0.txStatus = .error
    }
    store.onTransactionStatusChanged(mockTransactionSubmitted)
    XCTAssertFalse(store.isTxSubmitting)
  }

  func testPrepareBTCSend() async {
    let mockAllTokens: [QoraiWallet.BlockchainToken] = [.mockBTCToken]
    let mockTransaction: QoraiWallet.TransactionInfo = .mockBTCUnapprovedSend
    let store = setupStore(
      accountInfos: [.mockBtcAccount],
      allTokens: mockAllTokens,
      transactions: [mockTransaction]
    )
    let prepareExpectation = expectation(description: "prepare")
    await store.prepare()
    store.$activeTransactionId
      .sink { id in
        defer { prepareExpectation.fulfill() }
        XCTAssertEqual(id, mockTransaction.id)
      }
      .store(in: &cancellables)
    store.$gasValue
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, "0.00002544")
      }
      .store(in: &cancellables)
    store.$gasSymbol
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, QoraiWallet.BlockchainToken.mockBTCToken.symbol)
      }
      .store(in: &cancellables)
    store.$symbol
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, QoraiWallet.BlockchainToken.mockBTCToken.symbol)
      }
      .store(in: &cancellables)
    store.$value
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, "0.00005")
      }
      .store(in: &cancellables)

    await fulfillment(of: [prepareExpectation], timeout: 1)

  }

  func testPrepareZecSend() async {
    let mockAllTokens: [QoraiWallet.BlockchainToken] = [.mockZecToken]
    let mockTransaction: QoraiWallet.TransactionInfo = .mockZecUnapprovedSend
    let store = setupStore(
      accountInfos: [.mockZcashAccount],
      allTokens: mockAllTokens,
      transactions: [mockTransaction]
    )

    let prepareExpectation = expectation(description: "prepare")
    await store.prepare()
    store.$activeTransactionId
      .sink { id in
        defer { prepareExpectation.fulfill() }
        XCTAssertEqual(id, mockTransaction.id)
      }
      .store(in: &cancellables)
    store.$gasValue
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, "0.00100000")
      }
      .store(in: &cancellables)
    store.$gasSymbol
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, QoraiWallet.BlockchainToken.mockZecToken.symbol)
      }
      .store(in: &cancellables)
    store.$symbol
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, QoraiWallet.BlockchainToken.mockZecToken.symbol)
      }
      .store(in: &cancellables)
    store.$value
      .dropFirst()
      .sink { value in
        XCTAssertEqual(value, "0.01")
      }
      .store(in: &cancellables)

    await fulfillment(of: [prepareExpectation], timeout: 1)
  }
}

extension QoraiWallet.BlockchainToken {

  /// DAI token with contract address matching `QoraiWallet.TransactionInfo.previewConfirmedERC20Approve`
  fileprivate static let daiToken: QoraiWallet.BlockchainToken = .init(
    contractAddress: "0xad6d458402f60fd3bd25163575031acdce07538d",
    name: "DAI",
    logo: "",
    isCompressed: false,
    isErc20: true,
    isErc721: false,
    isErc1155: false,
    splTokenProgram: .unsupported,
    isNft: false,
    isSpam: false,
    symbol: "DAI",
    decimals: 18,
    visible: false,
    tokenId: "",
    coingeckoId: "",
    chainId: "",
    coin: .eth,
    isShielded: false
  )
}

extension XCTestCase {
  @MainActor func fulfillment(of expectations: [XCTestExpectation], timeout: TimeInterval) async {
    #if compiler(>=5.8)
    await fulfillment(of: expectations, timeout: timeout, enforceOrder: false)
    #else
    await withCheckedContinuation { continuation in
      waitForExpectations(timeout: timeout) { error in
        // `fulfillment(of:timeout:enforceOrder:) timeout will fail on the function
        // Verify we did not timeout here
        XCTAssertNil(error)
        continuation.resume()
      }
    }
    #endif
  }
}
