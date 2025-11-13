// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore

class KeyringServiceObserver: QoraiWalletKeyringServiceObserver {

  var _walletReset: (() -> Void)?
  var _walletCreated: (() -> Void)?
  var _walletRestored: (() -> Void)?
  var _locked: (() -> Void)?
  var _unlocked: (() -> Void)?
  var _backedUp: (() -> Void)?
  var _accountsChanged: (() -> Void)?
  var _autoLockMinutesChanged: (() -> Void)?
  var _selectedWalletAccountChanged: ((_ account: QoraiWallet.AccountInfo) -> Void)?
  var _selectedDappAccountChanged:
    ((_ coin: QoraiWallet.CoinType, _ account: QoraiWallet.AccountInfo?) -> Void)?
  var _accountsAdded: ((_ addedAccounts: [QoraiWallet.AccountInfo]) -> Void)?

  init(
    keyringService: QoraiWalletKeyringService,
    _walletReset: (() -> Void)? = nil,
    _walletCreated: (() -> Void)? = nil,
    _walletRestored: (() -> Void)? = nil,
    _locked: (() -> Void)? = nil,
    _unlocked: (() -> Void)? = nil,
    _backedUp: (() -> Void)? = nil,
    _accountsChanged: (() -> Void)? = nil,
    _autoLockMinutesChanged: (() -> Void)? = nil,
    _selectedWalletAccountChanged: ((QoraiWallet.AccountInfo) -> Void)? = nil,
    _selectedDappAccountChanged: ((QoraiWallet.CoinType, QoraiWallet.AccountInfo?) -> Void)? = nil,
    _accountsAdded: (([QoraiWallet.AccountInfo]) -> Void)? = nil
  ) {
    self._walletReset = _walletReset
    self._walletCreated = _walletCreated
    self._walletRestored = _walletRestored
    self._locked = _locked
    self._unlocked = _unlocked
    self._backedUp = _backedUp
    self._accountsChanged = _accountsChanged
    self._autoLockMinutesChanged = _autoLockMinutesChanged
    self._selectedWalletAccountChanged = _selectedWalletAccountChanged
    self._selectedDappAccountChanged = _selectedDappAccountChanged
    self._accountsAdded = _accountsAdded
    keyringService.addObserver(self)
  }

  func walletReset() {
    _walletReset?()
  }
  func walletCreated() {
    _walletCreated?()
  }
  public func walletRestored() {
    _walletRestored?()
  }
  public func locked() {
    _locked?()
  }
  public func unlocked() {
    _unlocked?()
  }
  public func backedUp() {
    _backedUp?()
  }
  public func accountsChanged() {
    _accountsChanged?()
  }
  public func autoLockMinutesChanged() {
    _autoLockMinutesChanged?()
  }
  public func selectedWalletAccountChanged(account: QoraiWallet.AccountInfo) {
    _selectedWalletAccountChanged?(account)
  }
  public func selectedDappAccountChanged(
    coin: QoraiWallet.CoinType,
    account: QoraiWallet.AccountInfo?
  ) {
    _selectedDappAccountChanged?(coin, account)
  }
  public func accountsAdded(addedAccounts: [QoraiWallet.AccountInfo]) {
    _accountsAdded?(addedAccounts)
  }
}

class WalletServiceObserver: QoraiWalletQoraiWalletServiceObserver {

  var _onActiveOriginChanged: ((_ originInfo: QoraiWallet.OriginInfo) -> Void)?
  var _onDefaultEthereumWalletChanged: ((_ wallet: QoraiWallet.DefaultWallet) -> Void)?
  var _onDefaultSolanaWalletChanged: ((_ wallet: QoraiWallet.DefaultWallet) -> Void)?
  var _onDefaultCardanoWalletChanged: ((_ wallet: QoraiWallet.DefaultWallet) -> Void)?
  var _onDefaultBaseCurrencyChanged: ((_ currency: String) -> Void)?
  var _onDefaultBaseCryptocurrencyChanged: ((_ cryptocurrency: String) -> Void)?
  var _onNetworkListChanged: (() -> Void)?
  var _onDiscoverAssetsStarted: (() -> Void)?
  var _onDiscoverAssetsCompleted: ((_ discoveredAssets: [QoraiWallet.BlockchainToken]) -> Void)?
  var _onResetWallet: (() -> Void)?

  init(
    walletService: QoraiWalletQoraiWalletService,
    _onActiveOriginChanged: ((_ originInfo: QoraiWallet.OriginInfo) -> Void)? = nil,
    _onDefaultEthereumWalletChanged: ((_ wallet: QoraiWallet.DefaultWallet) -> Void)? = nil,
    _onDefaultSolanaWalletChanged: ((_ wallet: QoraiWallet.DefaultWallet) -> Void)? = nil,
    _onDefaultCardanoWalletChanged: ((_ wallet: QoraiWallet.DefaultWallet) -> Void)? = nil,
    _onDefaultBaseCurrencyChanged: ((_ currency: String) -> Void)? = nil,
    _onDefaultBaseCryptocurrencyChanged: ((_ cryptocurrency: String) -> Void)? = nil,
    _onNetworkListChanged: (() -> Void)? = nil,
    _onDiscoverAssetsStarted: (() -> Void)? = nil,
    _onDiscoverAssetsCompleted: ((_ discoveredAssets: [QoraiWallet.BlockchainToken]) -> Void)? =
      nil,
    _onResetWallet: (() -> Void)? = nil
  ) {
    self._onActiveOriginChanged = _onActiveOriginChanged
    self._onDefaultEthereumWalletChanged = _onDefaultEthereumWalletChanged
    self._onDefaultSolanaWalletChanged = _onDefaultSolanaWalletChanged
    self._onDefaultCardanoWalletChanged = _onDefaultCardanoWalletChanged
    self._onDefaultBaseCurrencyChanged = _onDefaultBaseCurrencyChanged
    self._onDefaultBaseCryptocurrencyChanged = _onDefaultBaseCryptocurrencyChanged
    self._onNetworkListChanged = _onNetworkListChanged
    self._onDiscoverAssetsStarted = _onDiscoverAssetsStarted
    self._onDiscoverAssetsCompleted = _onDiscoverAssetsCompleted
    self._onResetWallet = _onResetWallet
    walletService.addObserver(self)
  }

  func onActiveOriginChanged(originInfo: QoraiWallet.OriginInfo) {
    _onActiveOriginChanged?(originInfo)
  }

  func onDefaultEthereumWalletChanged(wallet: QoraiWallet.DefaultWallet) {
    _onDefaultEthereumWalletChanged?(wallet)
  }

  func onDefaultSolanaWalletChanged(wallet: QoraiWallet.DefaultWallet) {
    _onDefaultSolanaWalletChanged?(wallet)
  }

  func onDefaultCardanoWalletChanged(wallet: QoraiWallet.DefaultWallet) {
    _onDefaultCardanoWalletChanged?(wallet)
  }

  func onDefaultBaseCurrencyChanged(currency: String) {
    _onDefaultBaseCurrencyChanged?(currency)
  }

  func onDefaultBaseCryptocurrencyChanged(cryptocurrency: String) {
    _onDefaultBaseCryptocurrencyChanged?(cryptocurrency)
  }

  func onNetworkListChanged() {
    _onNetworkListChanged?()
  }

  func onDiscoverAssetsStarted() {
    _onDiscoverAssetsStarted?()
  }

  func onDiscoverAssetsCompleted(discoveredAssets: [QoraiWallet.BlockchainToken]) {
    _onDiscoverAssetsCompleted?(discoveredAssets)
  }

  func onResetWallet() {
    _onResetWallet?()
  }
}

class TxServiceObserver: QoraiWalletTxServiceObserver {
  var _onNewUnapprovedTx: ((_ txInfo: QoraiWallet.TransactionInfo) -> Void)?
  var _onUnapprovedTxUpdated: ((_ txInfo: QoraiWallet.TransactionInfo) -> Void)?
  var _onTransactionStatusChanged: ((_ txInfo: QoraiWallet.TransactionInfo) -> Void)?
  var _onTxServiceReset: (() -> Void)?

  init(
    txService: QoraiWalletTxService,
    _onNewUnapprovedTx: ((_: QoraiWallet.TransactionInfo) -> Void)? = nil,
    _onUnapprovedTxUpdated: ((_: QoraiWallet.TransactionInfo) -> Void)? = nil,
    _onTransactionStatusChanged: ((_: QoraiWallet.TransactionInfo) -> Void)? = nil,
    _onTxServiceReset: (() -> Void)? = nil
  ) {
    self._onNewUnapprovedTx = _onNewUnapprovedTx
    self._onUnapprovedTxUpdated = _onUnapprovedTxUpdated
    self._onTransactionStatusChanged = _onTransactionStatusChanged
    self._onTxServiceReset = _onTxServiceReset
    txService.addObserver(self)
  }

  func onNewUnapprovedTx(txInfo: QoraiWallet.TransactionInfo) {
    _onNewUnapprovedTx?(txInfo)
  }

  func onUnapprovedTxUpdated(txInfo: QoraiWallet.TransactionInfo) {
    _onUnapprovedTxUpdated?(txInfo)
  }

  func onTransactionStatusChanged(txInfo: QoraiWallet.TransactionInfo) {
    _onTransactionStatusChanged?(txInfo)
  }

  func onTxServiceReset() {
    _onTxServiceReset?()
  }
}

class JsonRpcServiceObserver: QoraiWalletJsonRpcServiceObserver {
  var _chainChangedEvent:
    ((_ chainId: String, _ coin: QoraiWallet.CoinType, _ origin: URLOrigin?) -> Void)?
  var _onAddEthereumChainRequestCompleted: ((_ chainId: String, _ error: String) -> Void)?

  init(
    rpcService: QoraiWalletJsonRpcService,
    _chainChangedEvent: (
      (_ chainId: String, _ coin: QoraiWallet.CoinType, _ origin: URLOrigin?) -> Void
    )? = nil,
    _onAddEthereumChainRequestCompleted: ((_ chainId: String, _ error: String) -> Void)? = nil
  ) {
    self._chainChangedEvent = _chainChangedEvent
    self._onAddEthereumChainRequestCompleted = _onAddEthereumChainRequestCompleted
    rpcService.addObserver(self)
  }

  func chainChangedEvent(chainId: String, coin: QoraiWallet.CoinType, origin: URLOrigin?) {
    _chainChangedEvent?(chainId, coin, origin)
  }

  func onAddEthereumChainRequestCompleted(chainId: String, error: String) {
    _onAddEthereumChainRequestCompleted?(chainId, error)
  }

}
