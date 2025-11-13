// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Foundation

#if DEBUG
/// A test wallet service that implements some basic functionality for the use of SwiftUI Previews.
///
/// - note: Do not use this directly, use ``NetworkStore.previewStore``
class MockQoraiWalletService: QoraiWalletQoraiWalletService {
  private var assets: [String: [QoraiWallet.BlockchainToken]] = [
    QoraiWallet.MainnetChainId: [.previewToken],
    QoraiWallet.SepoliaChainId: [.previewToken],
  ]
  private var defaultCurrency = CurrencyCode.usd
  private var defaultCryptocurrency = "eth"
  private var coin: QoraiWallet.CoinType = .eth

  func ankrSupportedChainIds(completion: @escaping ([String]) -> Void) {
    completion([])
  }

  func userAssets(
    chainId: String,
    coin: QoraiWallet.CoinType,
    completion: @escaping ([QoraiWallet.BlockchainToken]) -> Void
  ) {
    completion(assets[chainId] ?? [])
  }

  func allUserAssets(completion: @escaping ([QoraiWallet.BlockchainToken]) -> Void) {
    let allAssets = assets.values.flatMap { $0 }
    completion(Array(allAssets))
  }

  func addUserAsset(token: QoraiWallet.BlockchainToken, completion: @escaping (Bool) -> Void) {
    assets[token.chainId]?.append(token)
  }

  func removeUserAsset(token: QoraiWallet.BlockchainToken, completion: @escaping (Bool) -> Void) {
    assets[token.chainId]?.removeAll(where: { $0.contractAddress == token.contractAddress })
  }

  func setUserAssetVisible(
    token: QoraiWallet.BlockchainToken,
    visible: Bool,
    completion: @escaping (Bool) -> Void
  ) {
    let chainAssets = assets[token.chainId]
    if let index = chainAssets?.firstIndex(where: { $0.contractAddress == token.contractAddress }) {
      chainAssets?[index].visible = visible
    }
  }

  func importFromExternalWallet(
    type: QoraiWallet.ExternalWalletType,
    password: String,
    newPassword: String,
    completion: @escaping (Bool, String?) -> Void
  ) {
    completion(false, nil)
  }

  func defaultWallet(_ completion: @escaping (QoraiWallet.DefaultWallet) -> Void) {
    completion(.qoraiWallet)
  }

  func hasEthereumPermission(
    _ origin: URLOrigin,
    account: String,
    completion: @escaping (Bool, Bool) -> Void
  ) {
    completion(false, false)
  }

  func resetEthereumPermission(
    _ origin: URLOrigin,
    account: String,
    completion: @escaping (Bool) -> Void
  ) {
    completion(false)
  }

  func activeOrigin(completion: @escaping (QoraiWallet.OriginInfo) -> Void) {
    completion(.init())
  }

  func pendingSignMessageRequests(
    completion: @escaping ([QoraiWallet.SignMessageRequest]) -> Void
  ) {
    completion([])
  }

  func pendingAddSuggestTokenRequests(
    completion: @escaping ([QoraiWallet.AddSuggestTokenRequest]) -> Void
  ) {
    completion([])
  }

  func defaultBaseCurrency(completion: @escaping (String) -> Void) {
    completion(defaultCurrency.code)
  }

  func setDefaultBaseCurrency(_ currency: String) {
    defaultCurrency = CurrencyCode(code: currency)
  }

  func defaultBaseCryptocurrency(completion: @escaping (String) -> Void) {
    completion(defaultCryptocurrency)
  }

  func setDefaultBaseCryptocurrency(_ cryptocurrency: String) {
    defaultCryptocurrency = cryptocurrency
  }

  func isExternalWalletInstalled(
    type: QoraiWallet.ExternalWalletType,
    completion: @escaping (Bool) -> Void
  ) {
    completion(false)
  }

  func isExternalWalletInitialized(
    type: QoraiWallet.ExternalWalletType,
    completion: @escaping (Bool) -> Void
  ) {
    completion(false)
  }

  func addEthereumPermission(
    _ origin: URLOrigin,
    account: String,
    completion: @escaping (Bool) -> Void
  ) {
    completion(false)
  }

  func addObserver(_ observer: QoraiWalletQoraiWalletServiceObserver) {
  }

  func addTokenObserver(_ observer: QoraiWalletQoraiWalletServiceTokenObserver) {
  }

  func setDefaultWallet(_ defaultEthWallet: QoraiWallet.DefaultWallet) {
  }

  func notifySignMessageRequestProcessed(
    approved: Bool,
    id: Int32,
    hwSignature: QoraiWallet.EthereumSignatureBytes?,
    error: String?
  ) {
  }

  func notifySignMessageHardwareRequestProcessed(
    _ approved: Bool,
    id: Int32,
    signature: String,
    error: String
  ) {
  }

  func notifyAddSuggestTokenRequestsProcessed(approved: Bool, contractAddresses: [String]) {
  }

  func reset() {
  }

  func activeOrigin(_ completion: @escaping (String, String) -> Void) {
    completion("", "")
  }

  func notifyGetPublicKeyRequestProcessed(requestId: String, approved: Bool) {
  }

  func pendingGetEncryptionPublicKeyRequests() async -> [QoraiWallet.GetEncryptionPublicKeyRequest]
  {
    return []
  }

  func notifyDecryptRequestProcessed(requestId: String, approved: Bool) {
  }

  func pendingDecryptRequests() async -> [QoraiWallet.DecryptRequest] {
    return []
  }

  func showWalletTestNetworks(_ completion: @escaping (Bool) -> Void) {
    completion(false)
  }

  func selectedCoin(_ completion: @escaping (QoraiWallet.CoinType) -> Void) {
    completion(coin)
  }

  func setSelectedCoin(_ coin: QoraiWallet.CoinType) {
    self.coin = coin
  }

  func addPermission(_ accountId: QoraiWallet.AccountId, completion: @escaping (Bool) -> Void) {
    completion(false)
  }

  func hasPermission(
    accounts: [QoraiWallet.AccountId],
    completion: @escaping (Bool, [QoraiWallet.AccountId]) -> Void
  ) {
    completion(false, [])
  }

  func resetPermission(accountId: QoraiWallet.AccountId, completion: @escaping (Bool) -> Void) {
    completion(false)
  }

  func isBase58EncodedSolanaPubkey(_ key: String, completion: @escaping (Bool) -> Void) {
    completion(false)
  }

  func eTldPlusOne(
    fromOrigin origin: URLOrigin,
    completion: @escaping (QoraiWallet.OriginInfo) -> Void
  ) {
    completion(.init())
  }

  func webSitesWithPermission(coin: QoraiWallet.CoinType, completion: @escaping ([String]) -> Void)
  {
    completion([])
  }

  func resetWebSitePermission(
    coin: QoraiWallet.CoinType,
    formedWebsite: String,
    completion: @escaping (Bool) -> Void
  ) {
    completion(false)
  }

  func pendingSignSolTransactionsRequests(
    completion: @escaping ([QoraiWallet.SignSolTransactionsRequest]) -> Void
  ) {
    completion([])
  }

  func notifySignSolTransactionsRequestProcessed(
    approved: Bool,
    id: Int32,
    hwSignatures: [QoraiWallet.SolanaSignature],
    error: String?
  ) {
  }
  
  func pendingSignCardanoTransactionRequests(
    completion: @escaping ([QoraiWallet.SignCardanoTransactionRequest]) -> Void
  ) {
    completion([])
  }

  func notifySignCardanoTransactionRequestProcessed(
    approved: Bool,
    id: Int32,
    error: String?
  ) {
  }

  func base58Encode(addresses: [[NSNumber]], completion: @escaping ([String]) -> Void) {
    completion([])
  }

  func isPermissionDenied(coin: QoraiWallet.CoinType, completion: @escaping (Bool) -> Void) {
    completion(false)
  }

  func onOnboardingShown() {
  }

  func defaultEthereumWallet(completion: @escaping (QoraiWallet.DefaultWallet) -> Void) {
    completion(.qoraiWallet)
  }

  func defaultSolanaWallet(completion: @escaping (QoraiWallet.DefaultWallet) -> Void) {
    completion(.qoraiWallet)
  }

  func defaultCardanoWallet(completion: @escaping (QoraiWallet.DefaultWallet) -> Void) {
    completion(.qoraiWallet)
  }

  func setDefaultEthereumWallet(defaultWallet: QoraiWallet.DefaultWallet) {
  }

  func setDefaultSolanaWallet(defaultWallet: QoraiWallet.DefaultWallet) {
  }

  func setDefaultCardanoWallet(defaultWallet: QoraiWallet.DefaultWallet) {
  }

  func nftDiscoveryEnabled(completion: @escaping (Bool) -> Void) {
    completion(false)
  }

  func setNftDiscoveryEnabled(_ enabled: Bool) {
  }

  func privateWindowsEnabled(completion: @escaping (Bool) -> Void) {
    completion(false)
  }

  func isPrivateWindow(completion: @escaping (Bool) -> Void) {
  }

  func setPrivateWindowsEnabled(_ enabled: Bool) {
  }

  func chainId(forActiveOrigin coin: QoraiWallet.CoinType, completion: @escaping (String) -> Void) {
    completion(QoraiWallet.MainnetChainId)
  }

  func setChainIdForActiveOrigin(
    _ coin: QoraiWallet.CoinType,
    chainId: String,
    completion: @escaping (Bool) -> Void
  ) {
    completion(false)
  }

  func balanceScannerSupportedChains(completion: @escaping ([String]) -> Void) {
    completion([])
  }

  func discoverEthAllowances(completion: @escaping ([QoraiWallet.AllowanceInfo]) -> Void) {
    completion([])
  }

  func setAssetSpamStatus(
    token: QoraiWallet.BlockchainToken,
    status: Bool,
    completion: @escaping (Bool) -> Void
  ) {
    completion(false)
  }

  func simpleHashSpamNfTs(
    walletAddress: String,
    chainIds: [QoraiWallet.ChainId],
    cursor: String?,
    completion: @escaping ([QoraiWallet.BlockchainToken], String?) -> Void
  ) {
    completion([], nil)
  }

  func ensureSelectedAccountForChain(
    coin: QoraiWallet.CoinType,
    chainId: String,
    completion: @escaping (QoraiWallet.AccountId?) -> Void
  ) {
    completion(nil)
  }

  func networkForSelectedAccountOnActiveOrigin(
    completion: @escaping (QoraiWallet.NetworkInfo?) -> Void
  ) {
    completion(nil)
  }

  func setNetworkForSelectedAccountOnActiveOrigin(
    chainId: String,
    completion: @escaping (Bool) -> Void
  ) {
    completion(false)
  }

  func networkForAccountOnActiveOrigin(
    account: QoraiWallet.AccountId,
    completion: @escaping (QoraiWallet.NetworkInfo?) -> Void
  ) {
    completion(nil)
  }

  func setNetworkForAccountOnActiveOrigin(
    account: QoraiWallet.AccountId,
    chainId: String,
    completion: @escaping (Bool) -> Void
  ) {
    completion(false)
  }

  func convertFevmToFvmAddress(
    isMainnet: Bool,
    fevmAddresses: [String],
    completion: @escaping ([String: String]) -> Void
  ) {
    completion([:])
  }

  func pendingSignMessageErrors(completion: @escaping ([QoraiWallet.SignMessageError]) -> Void) {
    completion([])
  }

  func notifySignMessageErrorProcessed(errorId: String) {

  }

  func generateReceiveAddress(
    accountId: QoraiWallet.AccountId,
    completion: @escaping (String?, String?) -> Void
  ) {
    completion(nil, "Error Message")
  }

  func discoverAssetsOnAllSupportedChains(bypassRateLimit: Bool) {
  }

  func writeToClipboard(text: String, isSensitive: Bool) {
  }

  func transactionSimulationOptInStatus(
    completion: @escaping (QoraiWallet.BlowfishOptInStatus) -> Void
  ) {
    completion(.unset)
  }

  func setTransactionSimulationOptInStatus(_ status: QoraiWallet.BlowfishOptInStatus) {
  }
}
#endif
