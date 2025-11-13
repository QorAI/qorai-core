// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiUI
import Preferences
import SwiftUI

struct DappsSettings: View {
  var coin: QoraiWallet.CoinType
  @ObservedObject var siteConnectionStore: ManageSiteConnectionsStore
  @ObservedObject var defaultWallet: Preferences.Option<Int>
  @ObservedObject var allowProviderAccess: Preferences.Option<Bool>
  @State private var filterText: String = ""
  @State private var isShowingConfirmAlert: Bool = false

  init(
    coin: QoraiWallet.CoinType,
    siteConnectionStore: ManageSiteConnectionsStore
  ) {
    self.coin = coin
    self.siteConnectionStore = siteConnectionStore
    switch coin {
    case .eth:
      self.defaultWallet = Preferences.Wallet.defaultEthWallet
      self.allowProviderAccess = Preferences.Wallet.allowEthProviderAccess
    case .sol:
      self.defaultWallet = Preferences.Wallet.defaultSolWallet
      self.allowProviderAccess = Preferences.Wallet.allowSolProviderAccess
    default:
      assertionFailure("Not supported coin type.")
      self.defaultWallet = Preferences.Wallet.defaultEthWallet
      self.allowProviderAccess = Preferences.Wallet.allowEthProviderAccess
    }
  }

  private var defaultWalletTitle: String {
    switch coin {
    case .eth:
      return Strings.Wallet.web3PreferencesDefaultEthWallet
    case .sol:
      return Strings.Wallet.web3PreferencesDefaultSolWallet
    default:
      return ""
    }
  }

  private var allowProviderAccessTitle: String {
    switch coin {
    case .eth:
      return Strings.Wallet.web3PreferencesAllowEthProviderAccess
    case .sol:
      return Strings.Wallet.web3PreferencesAllowSolProviderAccess
    default:
      return ""
    }
  }

  private var visibleSiteConnections: [SiteConnection] {
    siteConnectionStore.siteConnections.filter(by: coin, text: filterText)
  }

  var body: some View {
    List {
      Section(
        header: Text(Strings.Wallet.dappsSettingsGeneralSectionTitle)
          .foregroundColor(Color(.secondaryQoraiLabel))
      ) {
        Group {
          HStack {
            Text(defaultWalletTitle)
              .foregroundColor(Color(.qoraiLabel))
            Spacer()
            Menu {
              Picker("", selection: $defaultWallet.value) {
                ForEach(Preferences.Wallet.WalletType.allCases) { walletType in
                  Text(walletType.name)
                    .tag(walletType)
                }
              }
              .pickerStyle(.inline)
            } label: {
              let wallet = Preferences.Wallet.WalletType(rawValue: defaultWallet.value) ?? .none
              Text(wallet.name)
                .foregroundColor(Color(.qoraiBlurpleTint))
            }
          }
          Toggle(allowProviderAccessTitle, isOn: $allowProviderAccess.value)
            .foregroundColor(Color(.qoraiLabel))
            .toggleStyle(SwitchToggleStyle(tint: Color(.qoraiBlurpleTint)))
        }
        .listRowBackground(Color(.secondaryQoraiGroupedBackground))
      }
      Section(
        header: Text(Strings.Wallet.dappsSettingsConnectedSitesSectionTitle)
      ) {
        Group {
          if visibleSiteConnections.isEmpty {
            Text(Strings.Wallet.dappsSettingsConnectedSitesSectionEmpty)
              .foregroundColor(Color(.secondaryQoraiLabel))
              .font(.footnote)
              .multilineTextAlignment(.leading)
              .padding(.vertical, 6)
          } else {
            ForEach(visibleSiteConnections) { siteConnection in
              NavigationLink(
                destination: SiteConnectionDetailView(
                  siteConnection: siteConnection,
                  siteConnectionStore: siteConnectionStore
                )
              ) {
                SiteRow(
                  siteConnection: siteConnection
                )
                .swipeActions(edge: .trailing) {
                  Button(role: .destructive) {
                    withAnimation {
                      siteConnectionStore.removeAllPermissions(from: [siteConnection])
                    }
                  } label: {
                    Label(Strings.Wallet.delete, systemImage: "trash")
                  }
                }
              }
            }
            .onDelete { indexes in
              let visibleSiteConnections = siteConnectionStore.siteConnections
              let siteConnectionsToRemove = indexes.map { visibleSiteConnections[$0] }
              withAnimation {
                siteConnectionStore.removeAllPermissions(from: siteConnectionsToRemove)
              }
            }
          }
        }
        .listRowBackground(Color(.secondaryQoraiGroupedBackground))
      }
    }
    .listStyle(InsetGroupedListStyle())
    .listBackgroundColor(Color(UIColor.qoraiGroupedBackground))
    .navigationTitle(
      String.localizedStringWithFormat(Strings.Wallet.dappsSettingsNavTitle, coin.localizedTitle)
    )
    .navigationBarTitleDisplayMode(.inline)
    .searchable(
      text: $filterText,
      placement: .navigationBarDrawer(displayMode: .always),
      prompt: Text(Strings.Wallet.manageSiteConnectionsFilterPlaceholder)
    )
    .toolbar {
      ToolbarItemGroup(placement: .bottomBar) {
        Spacer()
        Button {
          isShowingConfirmAlert = true
        } label: {
          Text(Strings.Wallet.manageSiteConnectionsRemoveAll)
            .foregroundColor(
              siteConnectionStore.siteConnections.isEmpty ? Color(.qoraiDisabled) : .red
            )
        }
        .disabled(siteConnectionStore.siteConnections.isEmpty)
      }
    }
    .onAppear(perform: siteConnectionStore.fetchSiteConnections)
    .alert(isPresented: $isShowingConfirmAlert) {
      Alert(
        title: Text(Strings.Wallet.warningAlertConfirmation),
        message: Text(
          String.localizedStringWithFormat(
            Strings.Wallet.dappsSettingsRemoveAllWarning,
            visibleSiteConnections.count,
            visibleSiteConnections.count == 1
              ? Strings.Wallet.dappsSettingsWebsiteSingular
              : Strings.Wallet.dappsSettingsWebsitePlural
          )
        ),
        primaryButton: Alert.Button.destructive(
          Text(Strings.Wallet.manageSiteConnectionsConfirmAlertRemove),
          action: removeAll
        ),
        secondaryButton: Alert.Button.cancel(Text(Strings.CancelString))
      )
    }
  }

  func removeAll() {
    siteConnectionStore.removeAllPermissions(from: visibleSiteConnections)
    filterText = ""
  }
}

private struct SiteRow: View {

  let siteConnection: SiteConnection

  private var connectedAddresses: String {
    let account = Strings.Wallet.manageSiteConnectionsAccountSingular
    let accounts = Strings.Wallet.manageSiteConnectionsAccountPlural
    return String.localizedStringWithFormat(
      Strings.Wallet.manageSiteConnectionsAccount,
      siteConnection.connectedAddresses.count,
      siteConnection.connectedAddresses.count == 1 ? account : accounts
    )
  }

  var body: some View {
    VStack(alignment: .leading, spacing: 4) {
      Text(verbatim: siteConnection.url)
        .foregroundColor(Color(.qoraiLabel))
        .font(.headline)
      HStack {
        Text(connectedAddresses)
          .font(.subheadline)
          .foregroundColor(Color(.secondaryQoraiLabel))
        accountBlockies
      }
      .frame(maxWidth: .infinity, alignment: .leading)
    }
    .padding(.vertical, 6)
  }

  @ViewBuilder private var accountBlockies: some View {
    if siteConnection.connectedAddresses.isEmpty {
      EmptyView()
    } else {
      MultipleAccountBlockiesView(
        accountAddresses: siteConnection.connectedAddresses
      )
    }
  }
}

private struct SiteConnectionDetailView: View {

  let siteConnection: SiteConnection
  @ObservedObject var siteConnectionStore: ManageSiteConnectionsStore

  @Environment(\.presentationMode) @Binding private var presentationMode

  @State private var isShowingConfirmAlert = false

  var body: some View {
    List {
      Section(
        header: Text(
          String.localizedStringWithFormat(
            Strings.Wallet.manageSiteConnectionsDetailHeader,
            siteConnection.coin.localizedTitle
          )
        )
      ) {
        ForEach(siteConnection.connectedAddresses, id: \.self) { address in
          AccountView(
            address: address,
            seed: address,
            name: siteConnectionStore.accountInfo(for: address)?.name ?? ""
          )
          .swipeActions(edge: .trailing) {
            Button(role: .destructive) {
              withAnimation(.default) {
                if let url = URL(string: siteConnection.url) {
                  siteConnectionStore.removePermissions(
                    for: siteConnection.coin,
                    from: [address],
                    url: url
                  )
                }
              }
            } label: {
              Label(Strings.Wallet.delete, systemImage: "trash")
            }
          }
        }
        .onDelete { indexSet in
          let addressesToRemove = indexSet.map({ siteConnection.connectedAddresses[$0] })
          withAnimation(.default) {
            if let url = URL(string: siteConnection.url) {
              siteConnectionStore.removePermissions(
                for: siteConnection.coin,
                from: addressesToRemove,
                url: url
              )
            }
          }
        }
        .listRowBackground(Color(.secondaryQoraiGroupedBackground))
      }
    }
    .listStyle(.insetGrouped)
    .listBackgroundColor(Color(UIColor.qoraiGroupedBackground))
    .navigationBarTitleDisplayMode(.inline)
    .toolbar {
      ToolbarItem(placement: .principal) {
        Text(
          URLFormatter.formatURLOrigin(
            forDisplayOmitSchemePathAndTrivialSubdomains: siteConnection.url
          )
        )
        .lineLimit(1)
        .truncationMode(.head)
        .fontWeight(.medium)
        .foregroundColor(Color(qoraiSystemName: .textPrimary))
      }
      ToolbarItemGroup(placement: .bottomBar) {
        Spacer()
        Button {
          isShowingConfirmAlert = true
        } label: {
          Text(Strings.Wallet.manageSiteConnectionsRemoveAll)
            .foregroundColor(
              siteConnectionStore.siteConnections.isEmpty ? Color(.qoraiDisabled) : .red
            )
        }
      }
    }
    .alert(isPresented: $isShowingConfirmAlert) {
      Alert(
        title: Text(Strings.Wallet.manageSiteConnectionsConfirmAlertTitle),
        message: Text(Strings.Wallet.manageSiteConnectionsDetailConfirmAlertMessage),
        primaryButton: Alert.Button.destructive(
          Text(Strings.Wallet.manageSiteConnectionsConfirmAlertRemove),
          action: {
            siteConnectionStore.removeAllPermissions(from: [siteConnection])
          }
        ),
        secondaryButton: Alert.Button.cancel(Text(Strings.CancelString))
      )
    }
  }
}
