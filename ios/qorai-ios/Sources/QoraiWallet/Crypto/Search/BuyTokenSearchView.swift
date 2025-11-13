// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import Strings
import SwiftUI

struct BuyTokenSearchView: View {
  @ObservedObject var buyTokenStore: BuyTokenStore
  let keyringStore: KeyringStore
  let networkStore: NetworkStore

  @State private var isPresentingAddAccount: Bool = false
  @State private var isPresentingAddAccountConfirmation: Bool = false
  @State private var isPresentingNetworkFilter = false
  @State private var networkFilters: [Selectable<QoraiWallet.NetworkInfo>] = []
  @State private var savedSelectedBuyToken: QoraiWallet.MeldCryptoCurrency?
  @Environment(\.presentationMode) @Binding private var presentationMode

  private var networkFilterButton: some View {
    Button {
      self.isPresentingNetworkFilter = true
    } label: {
      Image(qoraiSystemName: "qora.tune")
        .font(.footnote.weight(.medium))
        .foregroundColor(Color(.qoraiBlurpleTint))
        .clipShape(Rectangle())
    }
    .sheet(isPresented: $isPresentingNetworkFilter) {
      NavigationView {
        NetworkFilterView(
          networks: networkFilters,
          networkStore: networkStore,
          saveAction: { networkFilters in
            self.networkFilters = networkFilters
          }
        )
      }
      .navigationViewStyle(.stack)
      .onDisappear {
        networkStore.closeNetworkSelectionStore()
      }
    }
  }

  private var filteredTokensByNetworks: [QoraiWallet.MeldCryptoCurrency] {
    let filterByNetwork = !networkFilters.allSatisfy(\.isSelected)
    if !filterByNetwork {
      return buyTokenStore.supportedCryptoCurrencies
    }
    let selectedNetworks = networkFilters.filter(\.isSelected)
    return buyTokenStore.supportedCryptoCurrencies.filter { token in
      if filterByNetwork,
        !selectedNetworks.contains(where: { token.chainId == $0.model.chainId })
      {
        return false
      }
      return true
    }
  }

  var body: some View {
    TokenList(
      tokens: filteredTokensByNetworks
    ) { query, token in
      let symbolMatch = token.currencyCode.localizedCaseInsensitiveContains(query)
      let nameMatch = token.name?.localizedCaseInsensitiveContains(query) ?? false
      return symbolMatch || nameMatch
    } header: {
      TokenListHeaderView(title: Strings.Wallet.assetsTitle)
    } content: { token in
      Button {
        if !buyTokenStore.hasMatchedCoinTypeAccount(for: token) {
          onAccountCreationNeeded(token)
        } else {
          buyTokenStore.selectedBuyToken = token
          presentationMode.dismiss()
        }
      } label: {
        MeldCryptoView(token: token)
      }
    }
    .navigationTitle(Strings.Wallet.searchTitle.capitalized)
    .toolbar {
      ToolbarItemGroup(placement: .bottomBar) {
        networkFilterButton
        Spacer()
      }
    }
    .addAccount(
      keyringStore: keyringStore,
      networkStore: networkStore,
      preselectedAccountCoin: savedSelectedBuyToken?.coin,
      preselectedAccountNetwork: nil,
      isShowingConfirmation: $isPresentingAddAccountConfirmation,
      isShowingAddAccount: $isPresentingAddAccount,
      onConfirmAddAccount: { isPresentingAddAccount = true },
      onCancelAddAccount: { buyTokenStore.handleCancelAddAccount() },
      onAddAccountDismissed: {
        Task {
          if let savedSelectedBuyToken,
            await buyTokenStore.handleDismissAddAccount(
              selectingToken: savedSelectedBuyToken
            )
          {
            self.savedSelectedBuyToken = nil
            presentationMode.dismiss()
          }
        }
      }
    )
    .onAppear {
      networkFilters = networkStore.visibleChains.map {
        .init(isSelected: true, model: $0)
      }
    }
  }

  private func onAccountCreationNeeded(_ asset: QoraiWallet.MeldCryptoCurrency) {
    savedSelectedBuyToken = asset
    isPresentingAddAccountConfirmation = true
  }
}

private struct MeldCryptoView: View {
  let token: QoraiWallet.MeldCryptoCurrency

  var body: some View {
    HStack(spacing: 8) {
      AssetIconView(
        token: nil,
        meldCryptoCurrency: token,
        shouldShowNetworkIcon: true
      )
      VStack(alignment: .leading) {
        Text(token.name ?? "")
          .fontWeight(.semibold)
          .foregroundColor(Color(.qoraiPrimary))
        Text(
          String.localizedStringWithFormat(
            Strings.Wallet.userAssetSymbolNetworkDesc,
            token.displaySymbol,
            token.chainName ?? ""
          )
        )
        .font(.caption)
        .foregroundColor(Color(.secondaryQoraiLabel))
      }
      .font(.footnote)
      Spacer()
    }
    .padding(.vertical, 6)
  }
}
