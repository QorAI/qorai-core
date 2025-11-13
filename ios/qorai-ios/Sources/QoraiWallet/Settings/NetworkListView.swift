// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiUI
import Preferences
import Strings
import SwiftUI

struct NetworkListView: View {
  @ObservedObject var networkStore: NetworkStore
  @State private var isPresentingNetworkDetails: NetworkModel?
  @Environment(\.presentationMode) @Binding private var presentationMode
  @Environment(\.sizeCategory) private var sizeCategory

  private struct CustomNetworkDetails: Identifiable {
    var isEditMode: Bool
    var network: QoraiWallet.NetworkInfo?
    var id: String {
      "\(isEditMode)"
    }
  }

  private func removeNetwork(_ network: QoraiWallet.NetworkInfo) {
    Task { @MainActor in
      await networkStore.removeCustomNetwork(network)
    }
  }

  private var customNetworks: [QoraiWallet.NetworkInfo] {
    networkStore.customChains
  }

  private var allNetworks: [QoraiWallet.NetworkInfo] {
    networkStore.allChains.filter {
      if $0.chainId == QoraiWallet.BitcoinTestnet {
        return Preferences.Wallet.isBitcoinTestnetEnabled.value
      } else if $0.chainId == QoraiWallet.ZCashTestnet {
        return Preferences.Wallet.isZcashTestnetEnabled.value
      }
      return true
    }
  }

  @ViewBuilder func networkRow(_ network: QoraiWallet.NetworkInfo) -> some View {
    Button {
      isPresentingNetworkDetails = .init(
        mode: .edit(network)
      )
    } label: {
      HStack {
        VStack(alignment: .leading, spacing: 4) {
          Text(network.chainName)
            .foregroundColor(Color(.qoraiLabel))
            .font(.callout.weight(isDefaultNetwork(network) ? .bold : .regular))
          Group {
            Text(network.chainId)
            if let rpcEndpoint = network.rpcEndpoints[
              safe: Int(network.activeRpcEndpointIndex)
            ]?.absoluteString {
              Text(rpcEndpoint)
            }
          }
          .foregroundColor(Color(.secondaryQoraiLabel))
          .font(.footnote)
        }
        Spacer()
        HStack {
          Button {
            if networkStore.isHiddenChain(network) {
              Task { @MainActor in
                await networkStore.removeHiddenNetwork(
                  coin: network.coin,
                  for: network.chainId
                )
              }
            } else {
              Task { @MainActor in
                await networkStore.addHiddenNetwork(
                  coin: network.coin,
                  for: network.chainId
                )
              }
            }
          } label: {
            Image(
              qoraiSystemName: networkStore.isHiddenChain(network)
                ? "qora.eye.off" : "qora.eye.on"
            )
            .font(.callout.weight(.semibold))
            .foregroundColor(
              isDefaultNetwork(network)
                ? Color(.qoraiDisabled) : Color(.qoraiLabel)
            )
          }
          .disabled(isDefaultNetwork(network))
          Rectangle()
            .fill(
              Color(uiColor: WalletV2Design.dividerSubtle)
            )
            .frame(width: 1)
            .padding(.vertical, 16)
          Menu {
            VStack {
              Button {
                isPresentingNetworkDetails = .init(
                  mode: .edit(network)
                )
              } label: {
                Text(Strings.Wallet.editButtonTitle)
              }
              if networkStore.isCustomChain(network)
                && !isDefaultNetwork(network)
              {
                Button {
                  removeNetwork(network)
                } label: {
                  Text(Strings.Wallet.delete)
                }
              }
              if !isDefaultNetwork(network) {
                Button {
                  Task { @MainActor in
                    await networkStore.updateDefaultNetwork(network)
                  }
                } label: {
                  Text(Strings.Wallet.setDefaultNetwork)
                }
              }
            }
            .foregroundColor(Color(.qoraiLabel))
          } label: {
            Image(
              qoraiSystemName: "qora.more.vertical"
            )
            .font(.callout.weight(.semibold))
            .foregroundColor(Color(.qoraiLabel))
          }
        }
      }
    }
  }

  var body: some View {
    List {
      ForEach(WalletConstants.supportedCoinTypes()) { coin in
        Section {
          let networks = allNetworks.filter { $0.coin == coin }
          ForEach(networks) { network in
            networkRow(network)
              .padding(.vertical, 6)
              .listRowBackground(
                Color(.secondaryQoraiGroupedBackground)
              )
          }
        } header: {
          Text(coin.localizedTitle)
        }
      }
    }
    .listStyle(.insetGrouped)
    .listBackgroundColor(Color(UIColor.qoraiGroupedBackground))
    .navigationTitle(Strings.Wallet.transactionDetailsNetworkTitle)
    .navigationBarTitleDisplayMode(.inline)
    .toolbar {
      ToolbarItemGroup(placement: .confirmationAction) {
        Button {
          isPresentingNetworkDetails = .init()
        } label: {
          Label(Strings.Wallet.addCustomNetworkBarItemTitle, systemImage: "plus")
            .foregroundColor(Color(.qoraiBlurpleTint))
        }
      }
    }
    .sheet(item: $isPresentingNetworkDetails) { detailsModel in
      NavigationView {
        NetworkDetailsView(
          networkStore: networkStore,
          model: detailsModel
        )
      }
      .navigationViewStyle(StackNavigationViewStyle())
    }
    .task {
      await networkStore.updateChainList()
    }
  }

  private func isDefaultNetwork(
    _ network: QoraiWallet.NetworkInfo
  ) -> Bool {
    guard let defaultNetwork = networkStore.defaultNetworks[network.coin]
    else {
      return false
    }
    return defaultNetwork.chainId == network.chainId
  }
}

#if DEBUG
struct CustomNetworkListView_Previews: PreviewProvider {
  static var previews: some View {
    NavigationView {
      NetworkListView(networkStore: .previewStore)
    }
    NavigationView {
      NetworkListView(networkStore: .previewStoreWithCustomNetworkAdded)
    }
  }
}
#endif
