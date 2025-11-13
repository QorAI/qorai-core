// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Combine
import Data
import Foundation
import Preferences

public class AssetStore: Identifiable, ObservableObject, Equatable, WalletObserverStore {
  @Published var token: QoraiWallet.BlockchainToken
  @Published var isVisible: Bool {
    didSet {
      Task { @MainActor in
        await assetManager.updateUserAsset(
          for: token,
          visible: isVisible,
          isSpam: token.isSpam,
          isDeletedByUser: false
        )
      }
    }
  }
  var network: QoraiWallet.NetworkInfo
  public var id: String { token.id }

  private let rpcService: QoraiWalletJsonRpcService
  private let ipfsApi: IpfsAPI
  private let assetManager: WalletUserAssetManagerType
  private(set) var isRemovable: Bool

  var isObserving: Bool = false

  init(
    rpcService: QoraiWalletJsonRpcService,
    network: QoraiWallet.NetworkInfo,
    token: QoraiWallet.BlockchainToken,
    ipfsApi: IpfsAPI,
    userAssetManager: WalletUserAssetManagerType,
    isRemovable: Bool,
    isVisible: Bool
  ) {
    self.rpcService = rpcService
    self.network = network
    self.token = token
    self.ipfsApi = ipfsApi
    self.assetManager = userAssetManager
    self.isRemovable = isRemovable
    self.isVisible = isVisible
  }

  public static func == (lhs: AssetStore, rhs: AssetStore) -> Bool {
    lhs.token == rhs.token && lhs.isVisible == rhs.isVisible
  }

  @MainActor func fetchERC721Metadata() async -> QoraiWallet.NftMetadata? {
    return await rpcService.fetchNFTMetadata(
      for: token,
      ipfsApi: ipfsApi
    )
  }
}

public class UserAssetsStore: ObservableObject, WalletObserverStore {
  @Published private(set) var assetStores: [AssetStore] = []
  @Published var isSearchingToken: Bool = false
  @Published var networkFilters: [Selectable<QoraiWallet.NetworkInfo>] = [] {
    didSet {
      guard !oldValue.isEmpty else { return }  // initial assignment to `networkFilters`
      update()
    }
  }
  @Published var isAddingAsset: Bool = false

  private let blockchainRegistry: QoraiWalletBlockchainRegistry
  private let rpcService: QoraiWalletJsonRpcService
  private let keyringService: QoraiWalletKeyringService
  private let assetRatioService: QoraiWalletAssetRatioService
  private let walletService: QoraiWalletQoraiWalletService
  private let ipfsApi: IpfsAPI
  private let assetManager: WalletUserAssetManagerType
  private var allTokens: [QoraiWallet.BlockchainToken] = []
  private var timer: Timer?
  private var keyringServiceObserver: KeyringServiceObserver?
  private var walletServiceObserver: WalletServiceObserver?
  private var updateTask: Task<(), Never>?

  var isObserving: Bool {
    keyringServiceObserver != nil && walletServiceObserver != nil
  }

  public init(
    blockchainRegistry: QoraiWalletBlockchainRegistry,
    rpcService: QoraiWalletJsonRpcService,
    keyringService: QoraiWalletKeyringService,
    assetRatioService: QoraiWalletAssetRatioService,
    walletService: QoraiWalletQoraiWalletService,
    ipfsApi: IpfsAPI,
    userAssetManager: WalletUserAssetManagerType
  ) {
    self.blockchainRegistry = blockchainRegistry
    self.rpcService = rpcService
    self.keyringService = keyringService
    self.assetRatioService = assetRatioService
    self.walletService = walletService
    self.ipfsApi = ipfsApi
    self.assetManager = userAssetManager

    self.setupObservers()
  }

  func tearDown() {
    keyringServiceObserver = nil
    walletServiceObserver = nil
  }

  func setupObservers() {
    guard !isObserving else { return }
    self.keyringServiceObserver = KeyringServiceObserver(
      keyringService: keyringService,
      _walletCreated: { [weak self] in
        self?.update()
      }
    )
    self.walletServiceObserver = WalletServiceObserver(
      walletService: walletService,
      _onNetworkListChanged: { [weak self] in
        Task { @MainActor [self] in
          // A network was added or removed, update our network filters for the change.
          guard let rpcService = self?.rpcService else { return }
          self?.networkFilters = await rpcService.allNetworksForSupportedCoins().map { network in
            let existingSelectionValue = self?.networkFilters.first(where: {
              $0.model.chainId == network.chainId
            })?.isSelected
            return .init(isSelected: existingSelectionValue ?? true, model: network)
          }
        }
      }
    )
    assetManager.addUserAssetDataObserver(self)
  }

  func update() {
    self.updateTask?.cancel()
    self.updateTask = Task { @MainActor in
      // setup network filters if not currently setup
      if self.networkFilters.isEmpty {
        self.networkFilters = await self.rpcService.allNetworksForSupportedCoins().map {
          .init(isSelected: true, model: $0)
        }
      }
      let networks: [QoraiWallet.NetworkInfo] = self.networkFilters.filter(\.isSelected).map(
        \.model
      )
      let allUserAssetsExcludeDeleted = await assetManager.getAllUserAssetsInNetworkAssets(
        networks: networks,
        includingUserDeleted: false
      )
      let allHiddenAssets = await assetManager.getUserAssets(
        networks: networks,
        visible: false
      )
      let allTokens = await self.blockchainRegistry.allTokens(
        in: networks,
        includingUserDeleted: false
      )
      // Filter `allTokens` to remove any tokens existing in `allUserAssets`. This is possible for ERC721 tokens in the registry without a `tokenId`, which requires the user to add as a custom token
      let allUserTokens = allUserAssetsExcludeDeleted.flatMap(\.tokens)
      let updatedAllTokens: [NetworkAssets] = allTokens.map { assetsForNetwork in
        NetworkAssets(
          network: assetsForNetwork.network,
          tokens: assetsForNetwork.tokens.filter { token in
            !allUserTokens.contains(where: { $0.id == token.id })
          },
          sortOrder: assetsForNetwork.sortOrder
        )
      }
      let allHiddenTokens: [QoraiWallet.BlockchainToken] = allHiddenAssets.flatMap(\.tokens)

      let visibleIds: [String] =
        allUserAssetsExcludeDeleted
        .flatMap(\.tokens)
        .filter { asset in
          !allHiddenTokens.contains { hiddenToken in
            hiddenToken.id.caseInsensitiveCompare(asset.id) == .orderedSame
          }
        }
        .map(\.id)
      assetStores = (allUserAssetsExcludeDeleted + updatedAllTokens)
        .sorted(by: { $0.sortOrder < $1.sortOrder })
        .flatMap { assetsForNetwork in
          assetsForNetwork.tokens.map { token in
            var isRemovable: Bool {
              if token.contractAddress.isEmpty {
                return false
              }
              if token.isErc721 || token.isErc1155 || token.isNft {
                return true
              }
              return !allTokens.flatMap(\.tokens).contains(where: {
                $0.contractAddress(in: assetsForNetwork.network).caseInsensitiveCompare(
                  token.contractAddress
                ) == .orderedSame
              })
            }
            return AssetStore(
              rpcService: rpcService,
              network: assetsForNetwork.network,
              token: token,
              ipfsApi: self.ipfsApi,
              userAssetManager: assetManager,
              isRemovable: isRemovable,
              isVisible: visibleIds.contains(where: {
                $0.caseInsensitiveCompare(token.id) == .orderedSame
              })
            )
          }
        }
    }
  }

  @MainActor func addUserAsset(
    _ token: QoraiWallet.BlockchainToken
  ) async -> Bool {
    isAddingAsset = true
    let success = await assetManager.addUserAsset(token, isAutoDiscovery: false)
    isAddingAsset = false
    if success {
      update()
    }
    return success
  }

  @MainActor func removeUserAsset(
    token: QoraiWallet.BlockchainToken
  ) async -> Bool {
    guard
      let storeToRemoveIndex = assetStores.firstIndex(where: {
        $0.token.id == token.id
      }),
      let storeToRemove = assetStores[safe: storeToRemoveIndex]
    else {
      return false
    }
    // `assetStores` updates
    assetStores.remove(at: storeToRemoveIndex)
    // asset manager updates
    let success = await assetManager.removeUserAsset(token)
    // if asset manager udpates failed, add the token back to `assetStores`
    if !success {
      assetStores.insert(storeToRemove, at: storeToRemoveIndex)
    }
    return success
  }

  func tokenInfo(
    address: String,
    chainId: String,
    completion: @escaping (QoraiWallet.BlockchainToken?) -> Void
  ) {
    // First check user's visible assets
    if let assetStore = assetStores.first(where: {
      $0.token.contractAddress.caseInsensitiveCompare(address) == .orderedSame
    }) {
      completion(assetStore.token)
    }  // else check full tokens list
    else if let token = allTokens.first(where: {
      $0.contractAddress.caseInsensitiveCompare(address) == .orderedSame
    }) {
      completion(token)
    }  // else use network request to get token info
    else if address.isETHAddress {  // only Eth networks supported, require ethereum address
      timer?.invalidate()
      timer = Timer.scheduledTimer(
        withTimeInterval: 0.25,
        repeats: false,
        block: { [weak self] _ in
          guard let self = self else { return }
          self.isSearchingToken = true
          self.rpcService.ethTokenInfo(
            contractAddress: address,
            chainId: chainId,
            completion: { token, status, error in
              self.isSearchingToken = false
              completion(token)
            }
          )
        }
      )
    }
  }

  @MainActor func isDuplicate(
    address: String,
    tokenId: String,
    network: QoraiWallet.NetworkInfo,
    isNFT: Bool
  ) async -> Bool {
    let allUserAssetsExcludeDeleted = await assetManager.getAllUserAssetsInNetworkAssets(
      networks: [network],
      includingUserDeleted: false
    )
    let allTokens = await self.blockchainRegistry.allTokens(
      in: [network],
      includingUserDeleted: false
    )
    var existedInUserAsset = false
    var existedInTokenRegistry = false
    if !isNFT || network.coin != .eth {
      existedInUserAsset =
        allUserAssetsExcludeDeleted.flatMap(\.tokens).first(where: {
          $0.contractAddress.caseInsensitiveCompare(address) == .orderedSame
        }) != nil
      existedInTokenRegistry =
        allTokens.flatMap(\.tokens).first(where: {
          $0.contractAddress.caseInsensitiveCompare(address) == .orderedSame
        }) != nil
    } else {
      var tokenIdToHex = "0x"
      if let tokenIdValue = Int16(tokenId) {
        tokenIdToHex = "0x\(String(format: "%02x", tokenIdValue))"
      }
      existedInUserAsset =
        allUserAssetsExcludeDeleted.flatMap(\.tokens).first(where: {
          $0.contractAddress.caseInsensitiveCompare(address) == .orderedSame
            && $0.tokenId == tokenIdToHex
        }) != nil
      existedInTokenRegistry =
        allTokens.flatMap(\.tokens).first(where: {
          $0.contractAddress.caseInsensitiveCompare(address) == .orderedSame
            && $0.tokenId == tokenIdToHex
        }) != nil
    }
    return existedInUserAsset || existedInTokenRegistry
  }

  @MainActor func networkInfo(
    by chainId: String,
    coin: QoraiWallet.CoinType
  ) async -> QoraiWallet.NetworkInfo? {
    let allNetworks = await rpcService.allNetworks()
    return allNetworks.first {
      $0.coin == coin && $0.chainId.caseInsensitiveCompare(chainId) == .orderedSame
    }
  }

  @MainActor func allAssets() async -> [AssetViewModel] {
    let allNetworks = await rpcService.allNetworksForSupportedCoins()
    let allUserAssets = await assetManager.getAllUserAssetsInNetworkAssets(
      networks: allNetworks,
      includingUserDeleted: false
    )
    // Filter `allTokens` to remove any tokens existing in `allUserAssets`. This is possible for ERC721 tokens in the registry without a `tokenId`, which requires the user to add as a custom token
    let allUserTokens = allUserAssets.flatMap(\.tokens)
    let allBlockchainTokens = await blockchainRegistry.allTokens(in: allNetworks)
      .map { assetsForNetwork in
        NetworkAssets(
          network: assetsForNetwork.network,
          tokens: assetsForNetwork.tokens.filter { token in
            !allUserTokens.contains(where: { $0.id == token.id })
          },
          sortOrder: assetsForNetwork.sortOrder
        )
      }

    return (allUserAssets + allBlockchainTokens).flatMap { networkAssets in
      networkAssets.tokens.map { token in
        AssetViewModel(
          groupType: .none,
          token: token,
          network: networkAssets.network,
          price: "",
          history: [],
          balanceForAccounts: [:],
          btcBalances: [:]
        )
      }
    }
  }

  @MainActor func allNFTMetadata() async -> [String: QoraiWallet.NftMetadata] {
    let allNetworks = await rpcService.allNetworksForSupportedCoins()
    let allUserAssets = await assetManager.getAllUserAssetsInNetworkAssets(
      networks: allNetworks,
      includingUserDeleted: true
    )
    // Filter `allTokens` to remove any tokens existing in `allUserAssets`. This is possible for ERC721 tokens in the registry without a `tokenId`, which requires the user to add as a custom token
    let allUserTokens = allUserAssets.flatMap(\.tokens)

    // NFT metadata only exists for custom NFT added by users. ERC721 tokens from token registry do not have metadata
    return await rpcService.fetchNFTMetadata(
      tokens: allUserTokens.filter { $0.isErc721 || $0.isNft },
      ipfsApi: ipfsApi
    )
  }
}

extension UserAssetsStore: WalletUserAssetDataObserver {
  public func cachedBalanceRefreshed() {
  }

  public func userAssetUpdated() {
    update()
  }
}
