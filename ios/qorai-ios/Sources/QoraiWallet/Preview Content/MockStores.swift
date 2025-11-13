// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiShared
import QoraiUI
import Foundation

#if DEBUG

extension WalletStore {
  static var previewStore: WalletStore {
    .init(
      keyringService: MockKeyringService(),
      rpcService: MockJsonRpcService(),
      walletService: MockQoraiWalletService(),
      assetRatioService: MockAssetRatioService(),
      swapService: MockSwapService(),
      blockchainRegistry: MockBlockchainRegistry(),
      txService: MockTxService(),
      ethTxManagerProxy: MockEthTxManagerProxy(),
      solTxManagerProxy: QoraiWallet.TestSolanaTxManagerProxy.previewProxy,
      ipfsApi: TestIpfsAPI(),
      walletP3A: TestQoraiWalletP3A(),
      bitcoinWalletService: QoraiWallet.TestBitcoinWalletService(),
      zcashWalletService: QoraiWallet.TestZCashWalletService(),
      meldIntegrationService: QoraiWallet.TestMeldIntegrationService()
    )
  }
}

extension CryptoStore {
  static var previewStore: CryptoStore {
    .init(
      keyringService: MockKeyringService(),
      rpcService: MockJsonRpcService(),
      walletService: MockQoraiWalletService(),
      assetRatioService: MockAssetRatioService(),
      swapService: MockSwapService(),
      blockchainRegistry: MockBlockchainRegistry(),
      txService: MockTxService(),
      ethTxManagerProxy: MockEthTxManagerProxy(),
      solTxManagerProxy: QoraiWallet.TestSolanaTxManagerProxy.previewProxy,
      ipfsApi: TestIpfsAPI(),
      walletP3A: TestQoraiWalletP3A(),
      bitcoinWalletService: QoraiWallet.TestBitcoinWalletService.previewBitcoinWalletService,
      zcashWalletService: QoraiWallet.TestZCashWalletService.previewZCashWalletService,
      meldIntegrationService: QoraiWallet.TestMeldIntegrationService.previewMeldIntegrationService
    )
  }
}

extension NetworkStore {
  static var previewStore: NetworkStore {
    .init(
      keyringService: MockKeyringService(),
      rpcService: MockJsonRpcService(),
      walletService: MockQoraiWalletService(),
      swapService: MockSwapService(),
      userAssetManager: TestableWalletUserAssetManager()
    )
  }

  static var previewStoreWithCustomNetworkAdded: NetworkStore {
    let keyringService = MockKeyringService()
    let rpcService = MockJsonRpcService()
    let walletService = MockQoraiWalletService()
    let swapService = MockSwapService()
    let userAssetManager = TestableWalletUserAssetManager()
    rpcService.addChain(
      .init(
        chainId: "0x100",
        chainName: "MockChain",
        blockExplorerUrls: ["https://mockchainscan.com"],
        iconUrls: [],
        activeRpcEndpointIndex: 0,
        rpcEndpoints: [URL(string: "https://rpc.mockchain.com")!],
        symbol: "MOCK",
        symbolName: "MOCK",
        decimals: 18,
        coin: .eth,
        supportedKeyrings: [QoraiWallet.KeyringId.default.rawValue].map(NSNumber.init(value:))
      )
    ) { _, _, _ in }

    let store = NetworkStore(
      keyringService: keyringService,
      rpcService: rpcService,
      walletService: walletService,
      swapService: swapService,
      userAssetManager: userAssetManager
    )
    return store
  }
}

extension KeyringStore {
  static var previewStore: KeyringStore {
    .init(
      keyringService: MockKeyringService(),
      walletService: MockQoraiWalletService(),
      rpcService: MockJsonRpcService(),
      walletP3A: TestQoraiWalletP3A()
    )
  }
  static var previewStoreWithWalletCreated: KeyringStore {
    let store = KeyringStore.previewStore
    store.createWallet(password: "password")
    store.allAccounts = [.previewAccount, .mockSolAccount]
    return store
  }
}

extension BuyTokenStore {
  static var previewStore: BuyTokenStore {
    .init(
      keyringService: MockKeyringService(),
      walletService: QoraiWallet.TestQoraiWalletService.previewWalletService,
      bitcoinWalletService: QoraiWallet.TestBitcoinWalletService.previewBitcoinWalletService,
      zcashWalletService: QoraiWallet.TestZCashWalletService.previewZCashWalletService,
      meldIntegrationService: QoraiWallet.TestMeldIntegrationService.previewMeldIntegrationService,
      prefilledToken: .previewToken
    )
  }
}

extension SendTokenStore {
  static var previewStore: SendTokenStore {
    .init(
      keyringService: MockKeyringService(),
      rpcService: MockJsonRpcService(),
      walletService: MockQoraiWalletService(),
      txService: MockTxService(),
      blockchainRegistry: MockBlockchainRegistry(),
      assetRatioService: MockAssetRatioService(),
      ethTxManagerProxy: MockEthTxManagerProxy(),
      solTxManagerProxy: QoraiWallet.TestSolanaTxManagerProxy.previewProxy,
      bitcoinWalletService: QoraiWallet.TestBitcoinWalletService.previewBitcoinWalletService,
      zcashWalletService: QoraiWallet.TestZCashWalletService.previewZCashWalletService,
      prefilledToken: .previewToken,
      ipfsApi: TestIpfsAPI(),
      userAssetManager: TestableWalletUserAssetManager()
    )
  }
}

extension AssetDetailStore {
  static var previewStore: AssetDetailStore {
    .init(
      assetRatioService: MockAssetRatioService(),
      keyringService: MockKeyringService(),
      rpcService: MockJsonRpcService(),
      walletService: MockQoraiWalletService(),
      txService: MockTxService(),
      blockchainRegistry: MockBlockchainRegistry(),
      solTxManagerProxy: QoraiWallet.TestSolanaTxManagerProxy.previewProxy,
      ipfsApi: TestIpfsAPI(),
      swapService: MockSwapService(),
      bitcoinWalletService: QoraiWallet.TestBitcoinWalletService.previewBitcoinWalletService,
      zcashWalletService: QoraiWallet.TestZCashWalletService.previewZCashWalletService,
      meldIntegrationService: QoraiWallet.TestMeldIntegrationService.previewMeldIntegrationService,
      userAssetManager: TestableWalletUserAssetManager(),
      assetDetailType: .blockchainToken(.previewToken)
    )
  }
}

extension SwapTokenStore {
  static var previewStore: SwapTokenStore {
    .init(
      keyringService: MockKeyringService(),
      blockchainRegistry: MockBlockchainRegistry(),
      rpcService: MockJsonRpcService(),
      swapService: MockSwapService(),
      txService: MockTxService(),
      walletService: MockQoraiWalletService(),
      ethTxManagerProxy: MockEthTxManagerProxy(),
      solTxManagerProxy: QoraiWallet.TestSolanaTxManagerProxy.previewProxy,
      userAssetManager: TestableWalletUserAssetManager(),
      prefilledToken: nil
    )
  }
}

extension UserAssetsStore {
  static var previewStore: UserAssetsStore {
    .init(
      blockchainRegistry: MockBlockchainRegistry(),
      rpcService: MockJsonRpcService(),
      keyringService: MockKeyringService(),
      assetRatioService: MockAssetRatioService(),
      walletService: MockQoraiWalletService(),
      ipfsApi: TestIpfsAPI(),
      userAssetManager: TestableWalletUserAssetManager()
    )
  }
}

extension AccountActivityStore {
  static var previewStore: AccountActivityStore {
    .init(
      account: .previewAccount,
      isWalletPanel: false,
      keyringService: MockKeyringService(),
      walletService: MockQoraiWalletService(),
      rpcService: MockJsonRpcService(),
      assetRatioService: MockAssetRatioService(),
      swapService: MockSwapService(),
      txService: MockTxService(),
      blockchainRegistry: MockBlockchainRegistry(),
      solTxManagerProxy: QoraiWallet.TestSolanaTxManagerProxy.previewProxy,
      ipfsApi: TestIpfsAPI(),
      bitcoinWalletService: QoraiWallet.TestBitcoinWalletService.previewBitcoinWalletService,
      zcashWalletService: QoraiWallet.TestZCashWalletService.previewZCashWalletService,
      userAssetManager: TestableWalletUserAssetManager()
    )
  }
}

extension TransactionConfirmationStore {
  static var previewStore: TransactionConfirmationStore {
    .init(
      assetRatioService: MockAssetRatioService(),
      rpcService: MockJsonRpcService(),
      txService: MockTxService(),
      blockchainRegistry: MockBlockchainRegistry(),
      walletService: MockQoraiWalletService(),
      ethTxManagerProxy: MockEthTxManagerProxy(),
      keyringService: {
        let service = MockKeyringService()
        service.createWallet(password: "password") { _ in }
        return service
      }(),
      solTxManagerProxy: QoraiWallet.TestSolanaTxManagerProxy.previewProxy,
      bitcoinWalletService: QoraiWallet.TestBitcoinWalletService.previewBitcoinWalletService,
      zcashWalletService: QoraiWallet.TestZCashWalletService.previewZCashWalletService,
      ipfsApi: TestIpfsAPI(),
      userAssetManager: TestableWalletUserAssetManager()
    )
  }
}

extension TransactionStatusStore {
  static var previewStore: TransactionStatusStore {
    .init(
      activeTxStatus: .submitted,
      activeTxParsed: .init(),
      txProviderError: nil,
      keyringService: MockKeyringService(),
      rpcService: MockJsonRpcService(),
      txService: MockTxService(),
      followUpAction: .none
    )
  }
}

extension SettingsStore {
  static var previewStore: SettingsStore {
    .init(
      keyringService: MockKeyringService(),
      walletService: MockQoraiWalletService(),
      rpcService: MockJsonRpcService(),
      txService: MockTxService(),
      ipfsApi: TestIpfsAPI(),
      keychain: TestableKeychain()
    )
  }
}

extension TabDappStore {
  static var previewStore: TabDappStore {
    .init()
  }
}

extension TransactionsActivityStore {
  static let preview: TransactionsActivityStore = .init(
    keyringService: MockKeyringService(),
    rpcService: MockJsonRpcService(),
    walletService: MockQoraiWalletService(),
    assetRatioService: MockAssetRatioService(),
    blockchainRegistry: MockBlockchainRegistry(),
    txService: MockTxService(),
    solTxManagerProxy: QoraiWallet.TestSolanaTxManagerProxy.previewProxy,
    ipfsApi: TestIpfsAPI(),
    userAssetManager: TestableWalletUserAssetManager()
  )
}

extension AccountsStore {
  static var previewStore: AccountsStore {
    .init(
      keyringService: MockKeyringService(),
      rpcService: MockJsonRpcService(),
      walletService: MockQoraiWalletService(),
      assetRatioService: MockAssetRatioService(),
      bitcoinWalletService: QoraiWallet.TestBitcoinWalletService.previewBitcoinWalletService,
      zcashWalletService: QoraiWallet.TestZCashWalletService.previewZCashWalletService,
      userAssetManager: TestableWalletUserAssetManager()
    )
  }
}

extension DepositTokenStore {
  static var previewStore: DepositTokenStore {
    .init(
      keyringService: QoraiWallet.TestKeyringService(),
      rpcService: MockJsonRpcService(),
      walletService: QoraiWallet.TestQoraiWalletService(),
      blockchainRegistry: QoraiWallet.TestBlockchainRegistry.previewBlockchainRegistry,
      prefilledToken: nil,
      prefilledAccount: nil,
      userAssetManager: TestableWalletUserAssetManager(),
      bitcoinWalletService: QoraiWallet.TestBitcoinWalletService.previewBitcoinWalletService,
      zcashWalletService: QoraiWallet.TestZCashWalletService.previewZCashWalletService
    )
  }
}

extension QoraiWallet.TestSolanaTxManagerProxy {
  static var previewProxy: QoraiWallet.TestSolanaTxManagerProxy {
    let solTxManagerProxy = QoraiWallet.TestSolanaTxManagerProxy()
    solTxManagerProxy._makeSystemProgramTransferTxData = { _, _, _, completion in
      completion(.init(), .success, "")
    }
    solTxManagerProxy._makeTokenProgramTransferTxData = { _, _, _, _, _, _, completion in
      completion(.init(), .success, "")
    }
    solTxManagerProxy._solanaTxFeeEstimation = { _, _, completion in
      let feeEstimation = QoraiWallet.SolanaFeeEstimation(
        baseFee: UInt64(0),
        computeUnits: UInt32(0),
        feePerComputeUnit: UInt64(0)
      )
      completion(feeEstimation, .success, "")
    }

    return solTxManagerProxy
  }
}

extension QoraiWallet.TestEthTxManagerProxy {
  static var previewProxy: QoraiWallet.TestEthTxManagerProxy {
    return QoraiWallet.TestEthTxManagerProxy()
  }
}

extension QoraiWallet.TestQoraiWalletService {
  static var previewWalletService: QoraiWallet.TestQoraiWalletService {
    return QoraiWallet.TestQoraiWalletService()
  }
}

extension QoraiWallet.TestAssetRatioService {
  static var previewAssetRatioService: QoraiWallet.TestAssetRatioService {
    let assetRatioService = QoraiWallet.TestAssetRatioService()
    assetRatioService._buyUrlV1 = { _, _, _, _, _, _, completion in
      completion("", nil)
    }

    return assetRatioService
  }
}

extension QoraiWallet.TestBlockchainRegistry {
  static var previewBlockchainRegistry: QoraiWallet.TestBlockchainRegistry {
    return QoraiWallet.TestBlockchainRegistry()
  }
}

extension QoraiWallet.TestBitcoinWalletService {
  static var previewBitcoinWalletService: QoraiWallet.TestBitcoinWalletService {
    return QoraiWallet.TestBitcoinWalletService()
  }
}

extension QoraiWallet.TestZCashWalletService {
  static var previewZCashWalletService: QoraiWallet.TestZCashWalletService {
    return QoraiWallet.TestZCashWalletService()
  }
}

extension QoraiWallet.TestMeldIntegrationService {
  static var previewMeldIntegrationService: QoraiWallet.TestMeldIntegrationService {
    return QoraiWallet.TestMeldIntegrationService()
  }
}

#endif
