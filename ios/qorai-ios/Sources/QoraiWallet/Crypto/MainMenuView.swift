// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import Preferences
import Strings
import SwiftUI

struct MainMenuView: View {

  let selectedTab: CryptoTab
  @Binding var isShowingSettings: Bool
  @Binding var isShowingBackup: Bool
  @Binding var isShowingAddAccount: Bool
  let keyringStore: KeyringStore

  @ObservedObject private var isShowingBalances = Preferences.Wallet.isShowingBalances
  @ObservedObject private var isShowingGraph = Preferences.Wallet.isShowingGraph
  @ObservedObject private var isShowingNFTs = Preferences.Wallet.isShowingNFTsTab

  @Environment(\.presentationMode) @Binding private var presentationMode
  @Environment(\.openURL) private var openWalletURL

  @ScaledMetric var rowHeight: CGFloat = 52
  @State private var viewHeight: CGFloat = 0

  var body: some View {
    ScrollView {
      LazyVStack(spacing: 0) {
        Button {
          presentationMode.dismiss()
          keyringStore.lock()
        } label: {
          MenuRowView(
            iconQoraiSystemName: "qora.lock",
            title: Strings.Wallet.lockWallet
          )
        }
        .frame(height: rowHeight)

        Button {
          isShowingBackup = true
        } label: {
          MenuRowView(
            iconQoraiSystemName: "qora.safe",
            title: Strings.Wallet.backUpWallet
          )
        }
        .frame(height: rowHeight)

        Button {
          isShowingSettings = true
          presentationMode.dismiss()
        } label: {
          MenuRowView(
            iconQoraiSystemName: "qora.settings",
            title: Strings.Wallet.walletSettings
          )
        }
        .frame(height: rowHeight)

        if selectedTab == .portfolio {
          Divider()
          portfolioSettings
        } else if selectedTab == .accounts {
          Divider()
          accountsMenuItems
        }

        Divider()
        Button {
          openWalletURL(WalletConstants.qoraiWalletSupportURL)
        } label: {
          MenuRowView(
            iconQoraiSystemName: "qora.help.outline",
            title: Strings.Wallet.helpCenter,
            accessoryContent: {
              Image(qoraiSystemName: "qora.launch")
                .imageScale(.large)
                .foregroundColor(Color(qoraiSystemName: .buttonBackground))
            }
          )
        }
        .frame(height: rowHeight)
      }
      .padding(.vertical, 8)
      .readSize { size in
        self.viewHeight = size.height
      }
    }
    .background(Color(qoraiSystemName: .containerBackground))
    .presentationDetents([
      .height(viewHeight)
    ])
  }

  @ViewBuilder private var portfolioSettings: some View {
    MenuRowView(
      iconQoraiSystemName: "qora.eye.on",
      title: Strings.Wallet.balances,
      accessoryContent: {
        Toggle(isOn: $isShowingBalances.value) {
          EmptyView()
        }
        .tint(Color(qoraiSystemName: .buttonBackground))
      }
    )
    .frame(height: rowHeight)

    MenuRowView(
      iconQoraiSystemName: "qora.graph",
      title: Strings.Wallet.graph,
      accessoryContent: {
        Toggle(isOn: $isShowingGraph.value) {
          EmptyView()
        }
        .tint(Color(qoraiSystemName: .buttonBackground))
      }
    )
    .frame(height: rowHeight)

    MenuRowView(
      iconQoraiSystemName: "qora.nft",
      title: Strings.Wallet.nftsTab,
      accessoryContent: {
        Toggle(isOn: $isShowingNFTs.value) {
          EmptyView()
        }
        .tint(Color(qoraiSystemName: .buttonBackground))
      }
    )
    .frame(height: rowHeight)
  }

  @ViewBuilder private var accountsMenuItems: some View {
    Button {
      self.isShowingAddAccount = true
    } label: {
      MenuRowView(
        iconQoraiSystemName: "qora.plus.add",
        title: Strings.Wallet.addAccountTitle
      )
    }
    .frame(height: rowHeight)
  }
}

#if DEBUG
struct MainMenuView_Previews: PreviewProvider {
  static var previews: some View {
    Color.white
      .sheet(
        isPresented: .constant(true),
        content: {
          MainMenuView(
            selectedTab: .portfolio,
            isShowingSettings: .constant(false),
            isShowingBackup: .constant(false),
            isShowingAddAccount: .constant(false),
            keyringStore: .previewStoreWithWalletCreated
          )
        }
      )
  }
}
#endif

private struct MenuRowView<AccessoryContent: View>: View {

  let iconQoraiSystemName: String
  let title: String
  let accessoryContent: () -> AccessoryContent

  init(
    iconQoraiSystemName: String,
    title: String,
    accessoryContent: @escaping () -> AccessoryContent = { EmptyView() }
  ) {
    self.iconQoraiSystemName = iconQoraiSystemName
    self.title = title
    self.accessoryContent = accessoryContent
  }

  var body: some View {
    HStack(spacing: 12) {
      Image(qoraiSystemName: iconQoraiSystemName)
        .imageScale(.medium)
        .foregroundColor(Color(qoraiSystemName: .iconDefault))
      Text(title)
        .foregroundColor(Color(qoraiSystemName: .textPrimary))
      Spacer()
      accessoryContent()
    }
    .font(.callout.weight(.semibold))
    .padding(.horizontal)
  }
}
