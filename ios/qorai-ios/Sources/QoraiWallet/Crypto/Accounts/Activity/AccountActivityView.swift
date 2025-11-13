// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiUI
import DesignSystem
import Strings
import SwiftUI
import UIKit

struct AccountActivityView: View {

  @ObservedObject var store: AccountActivityStore
  var cryptoStore: CryptoStore
  var keyringStore: KeyringStore

  @Binding var walletActionDestination: WalletActionDestination?

  @State private var didLoad: Bool = false
  @State private var isPresentingEditAccount: Bool = false
  @State private var isPresentingExportAccount: Bool = false

  var body: some View {
    ScrollView {
      VStack(spacing: 0) {
        headerSection

        rowsSection
      }
    }
    .navigationBarTitleDisplayMode(.inline)
    .navigationTitle(store.account.name)
    .toolbar {
      ToolbarItem(placement: .navigationBarTrailing) {
        Menu(
          content: {
            Button {
              isPresentingEditAccount = true
            } label: {
              Label(Strings.Wallet.editButtonTitle, qoraiSystemImage: "qora.edit.pencil")
            }
            if store.account.supportsAccountExport {
              Button {
                isPresentingExportAccount = true
              } label: {
                Label(Strings.Wallet.exportButtonTitle, qoraiSystemImage: "qora.key")
              }
            }
          },
          label: {
            Image(qoraiSystemName: "qora.more.horizontal")
              .foregroundColor(Color(qoraiSystemName: .iconInteractive))
          }
        )
      }
    }
    .background(
      VStack(spacing: 0) {
        Color(qoraiSystemName: .containerBackground)
          .frame(maxHeight: 200)
          .edgesIgnoringSafeArea(.top)
        Color(qoraiSystemName: .pageBackground)
          .edgesIgnoringSafeArea(.all)
      }
    )
    .background(
      Color.clear
        .sheet(isPresented: $isPresentingEditAccount) {
          AccountDetailsView(
            keyringStore: keyringStore,
            account: store.account,
            editMode: true
          )
        }
    )
    .background(
      Color.clear
        .sheet(isPresented: $isPresentingExportAccount) {
          NavigationView {
            AccountPrivateKeyView(
              keyringStore: keyringStore,
              account: store.account
            )
            .toolbar {
              ToolbarItem(placement: .navigationBarLeading) {
                Button {
                  isPresentingExportAccount = false
                } label: {
                  Text(Strings.cancelButtonTitle)
                    .foregroundColor(Color(.qoraiBlurpleTint))
                }
              }
            }
          }
        }
    )
    .onAppear {
      // Skip reload when popping detail view off stack (assets, nfts, transactions)
      guard !didLoad else { return }
      didLoad = true
      store.update()
    }
  }

  private var headerSection: some View {
    VStack(spacing: 0) {
      VStack(spacing: 8) {
        Blockie(address: store.account.blockieSeed)
          .frame(width: 44, height: 44)
          .clipShape(RoundedRectangle(cornerRadius: 4))
          .accessibilityHidden(true)
        VStack(spacing: 0) {
          Text(store.account.name)
            .font(.title2.weight(.semibold))
          if !store.account.address.isEmpty {
            AddressView(address: store.account.address) {
              Text(store.account.address.truncatedAddress)
                .font(.caption)
            }
          }
        }
      }

      Spacer().frame(height: 16)

      VStack {
        if store.isLoadingAccountFiat {
          Text(store.accountTotalFiat)
            .font(.title.weight(.medium))
            .redacted(reason: .placeholder)
            .shimmer(store.isLoadingAccountFiat)
        } else {
          Text(store.accountTotalFiat)
            .font(.title.weight(.medium))
        }
        Text(store.account.accountSupportDisplayString)
          .font(.caption)
      }

      Spacer().frame(height: 24)

      HStack(spacing: 24) {
        PortfolioHeaderButton(style: .buy) {
          walletActionDestination = .init(kind: .buy)
        }
        PortfolioHeaderButton(style: .send) {
          walletActionDestination = .init(kind: .send)
        }
        if store.isSwapSupported {
          PortfolioHeaderButton(style: .swap) {
            walletActionDestination = .init(kind: .swap)
          }
        }
        PortfolioHeaderButton(style: .deposit) {
          walletActionDestination = .init(kind: .deposit(query: nil), initialAccount: store.account)
        }
      }
    }
    .padding(.vertical, 24)
    .frame(maxWidth: .infinity)
    .background(
      Color(qoraiSystemName: .containerBackground)
    )
  }

  private var rowsSection: some View {
    VStack(spacing: 0) {
      NavigationLink(
        destination: {
          AssetsListDetailView(
            store: store,
            cryptoStore: cryptoStore,
            keyringStore: keyringStore
          )
        },
        label: {
          let assetsCount = store.userAssets.count
          RowView(
            iconQoraiSystemName: "qora.crypto.wallets",
            title: Strings.Wallet.assetsTitle,
            description: String.localizedStringWithFormat(
              assetsCount == 1
                ? Strings.Wallet.assetsSingularDescription : Strings.Wallet.assetsDescription,
              assetsCount
            )
          )
        }
      )
      if store.account.supportsNFT {
        Divider()
        NavigationLink(
          destination: {
            NFTGridDetailView(
              store: store,
              cryptoStore: cryptoStore,
              keyringStore: keyringStore
            )
          },
          label: {
            let nftCount = store.userNFTs.count
            RowView(
              iconQoraiSystemName: "qora.grid04",
              title: Strings.Wallet.nftsTitle,
              description: String.localizedStringWithFormat(
                nftCount == 1
                  ? Strings.Wallet.nftsSingularDescription : Strings.Wallet.nftsDescription,
                nftCount
              )
            )
          }
        )
      }
      Divider()
      NavigationLink(
        destination: {
          AccountTransactionListView(
            activityStore: store,
            networkStore: cryptoStore.networkStore
          )
        },
        label: {
          let transactionCount = store.transactionSections.flatMap(\.transactions).count
          RowView(
            iconQoraiSystemName: "qora.history",
            title: Strings.Wallet.transactionsTitle,
            description: String.localizedStringWithFormat(
              transactionCount == 1
                ? Strings.Wallet.transactionsSingularDescription
                : Strings.Wallet.transactionsDescription,
              transactionCount
            )
          )
        }
      )
      if WalletConstants.supportedCoinTypes(.dapps).contains(store.account.coin) {
        Divider()
        NavigationLink(
          destination: {
            DappsSettings(
              coin: store.account.coin,
              siteConnectionStore: cryptoStore.settingsStore.manageSiteConnectionsStore(
                keyringStore: keyringStore
              )
            )
          },
          label: {
            RowView(
              iconQoraiSystemName: "qora.lock.dots",
              title: Strings.Wallet.securityTitle,
              description: Strings.Wallet.accountSecurityDescription
            )
          }
        )
      }
    }
    .background(
      Color(qoraiSystemName: .containerBackground)
        .clipShape(RoundedRectangle(cornerRadius: 12))
    )
    .padding()
    .background(
      Color(qoraiSystemName: .pageBackground)
    )
  }

  private struct RowView: View {
    let iconQoraiSystemName: String
    let title: String
    let description: String

    var body: some View {
      HStack(spacing: 16) {
        Circle()
          .fill(Color(qoraiSystemName: .pageBackground))
          .frame(width: 40, height: 40)
          .overlay {
            Image(qoraiSystemName: iconQoraiSystemName)
              .foregroundColor(Color(qoraiSystemName: .iconDefault))
          }
        VStack(alignment: .leading) {
          Text(title)
            .font(.callout.weight(.semibold))
            .foregroundColor(Color(qoraiSystemName: .textPrimary))
          Text(description)
            .font(.footnote)
            .foregroundColor(Color(qoraiSystemName: .textSecondary))
        }
        Spacer()
        Image(systemName: "chevron.right")
          .font(.body.weight(.semibold))
          .foregroundColor(Color(.separator))
      }
      .padding(.vertical, 10)
      .padding(.horizontal, 16)
    }
  }
}

#if DEBUG
struct AccountActivityView_Previews: PreviewProvider {
  static var previews: some View {
    NavigationView {
      AccountActivityView(
        store: .previewStore,
        cryptoStore: .previewStore,
        keyringStore: .previewStore,
        walletActionDestination: .constant(.none)
      )
    }
    .previewColorSchemes()
  }
}
#endif

private struct AssetsListDetailView: View {

  @ObservedObject var store: AccountActivityStore
  var cryptoStore: CryptoStore
  var keyringStore: KeyringStore
  @State private var assetForDetails: QoraiWallet.BlockchainToken?

  var body: some View {
    AssetsListView(
      assets: store.userAssets,
      shouldShowContainerForBitcoin: false,
      currencyFormatter: store.currencyFormatter,
      selectedAsset: { asset in
        assetForDetails = asset
      }
    )
    .navigationTitle(Strings.Wallet.assetsTitle)
    .background(
      NavigationLink(
        isActive: Binding(
          get: { assetForDetails != nil },
          set: { if !$0 { assetForDetails = nil } }
        ),
        destination: {
          if let token = assetForDetails {
            AssetDetailView(
              assetDetailStore: cryptoStore.assetDetailStore(for: .blockchainToken(token)),
              keyringStore: keyringStore,
              networkStore: cryptoStore.networkStore
            )
            .onDisappear {
              cryptoStore.closeAssetDetailStore(for: .blockchainToken(token))
            }
          }
        },
        label: {
          EmptyView()
        }
      )
    )
  }
}

private struct NFTGridDetailView: View {

  @ObservedObject var store: AccountActivityStore
  var cryptoStore: CryptoStore
  var keyringStore: KeyringStore

  @State private var nftForDetails: QoraiWallet.BlockchainToken?

  @Environment(\.walletActionDestination)
  private var walletActionDestination: Binding<WalletActionDestination?>

  var body: some View {
    NFTsGridView(
      assets: store.userNFTs,
      selectedAsset: { nft in
        nftForDetails = nft
      }
    )
    .navigationTitle(Strings.Wallet.nftsTitle)
    .background(
      NavigationLink(
        isActive: Binding(
          get: { nftForDetails != nil },
          set: { if !$0 { nftForDetails = nil } }
        ),
        destination: {
          if let token = nftForDetails {
            NFTDetailView(
              keyringStore: keyringStore,
              nftDetailStore: cryptoStore.nftDetailStore(for: token, nftMetadata: nil, owner: nil),
              walletActionDestination: walletActionDestination
            ) { metadata in

            }
            .onDisappear {
              cryptoStore.closeNFTDetailStore(for: token)
            }
          }
        },
        label: {
          EmptyView()
        }
      )
    )
  }
}
