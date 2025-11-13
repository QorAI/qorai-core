// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Data
import Foundation

extension QoraiWalletBlockchainRegistry {

  /// Returns all the `BlockchainToken`s for each of the given networks
  @MainActor func allTokens(in networks: [QoraiWallet.NetworkInfo]) async -> [NetworkAssets] {
    await withTaskGroup(
      of: [NetworkAssets].self,
      body: { @MainActor group -> [NetworkAssets] in
        for (index, network) in networks.enumerated() {
          group.addTask { @MainActor in
            let allTokens = await self.allTokens(chainId: network.chainId, coin: network.coin)
            return [
              NetworkAssets(
                network: network,
                tokens: allTokens + [network.nativeToken],
                sortOrder: index
              )
            ]
          }
        }
        return await group.reduce([NetworkAssets](), { $0 + $1 })
          .sorted(by: { $0.sortOrder < $1.sortOrder })  // maintain sort order of networks
      }
    )
  }

  /// Returns all the `BlockchainToken`s for each of the given networks
  @MainActor func allTokens(
    in networks: [QoraiWallet.NetworkInfo],
    includingUserDeleted: Bool
  ) async -> [NetworkAssets] {
    await withTaskGroup(
      of: [NetworkAssets].self,
      body: { @MainActor group -> [NetworkAssets] in
        for (index, network) in networks.enumerated() {
          group.addTask { @MainActor in
            let allTokensFromRegistry =
              await self.allTokens(
                chainId: network.chainId,
                coin: network.coin
              )
            var allTokens = allTokensFromRegistry + [network.nativeToken]
            if !includingUserDeleted {
              let locallyDeletedTokens: [QoraiWallet.BlockchainToken] =
                WalletUserAsset.getAllUserDeletedUserAssets()?
                .map { $0.blockchainToken } ?? []
              allTokens = allTokens.filter({ token in
                !locallyDeletedTokens.contains {
                  $0.id.caseInsensitiveCompare(token.id) == .orderedSame
                }
              })
            }
            return [
              NetworkAssets(
                network: network,
                tokens: allTokens,
                sortOrder: index
              )
            ]
          }
        }
        return await group.reduce([NetworkAssets](), { $0 + $1 })
          .sorted(by: { $0.sortOrder < $1.sortOrder })  // maintain sort order of networks
      }
    )
  }

  /// Returns all buy-supported`BlockchainToken`s for each of the given network and a list
  /// on-ramp providers
  @MainActor func allBuyTokens(
    in networks: [QoraiWallet.NetworkInfo],
    for providers: [QoraiWallet.OnRampProvider]
  ) async -> [QoraiWallet.OnRampProvider: [QoraiWallet.BlockchainToken]] {
    await withTaskGroup(
      of: [QoraiWallet.OnRampProvider: [QoraiWallet.BlockchainToken]].self,
      body: { @MainActor group -> [QoraiWallet.OnRampProvider: [QoraiWallet.BlockchainToken]] in
        for provider in providers {
          group.addTask { @MainActor in
            var allTokens: [QoraiWallet.BlockchainToken] = []
            for network in networks {
              let allTokensForNetwork = await self.buyTokens(
                provider: provider,
                chainId: network.chainId
              )
              allTokens.append(contentsOf: allTokensForNetwork)
            }
            return [provider: allTokens]
          }
        }
        return await group.reduce([:], { $0.merging($1) { (_, new) in new } })
      }
    )
  }
}
