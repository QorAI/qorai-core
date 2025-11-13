// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiUI
import DesignSystem
import Foundation
import Strings
import Swift
import SwiftUI

struct TransactionDetailsView: View {

  @ObservedObject var transactionDetailsStore: TransactionDetailsStore
  @ObservedObject var networkStore: NetworkStore
  @State private var errorMessage: String?

  @Environment(\.sizeCategory) private var sizeCategory
  @Environment(\.openURL) private var openWalletURL
  @Environment(\.dismiss) private var dismiss

  var body: some View {
    ScrollView {
      LazyVStack(spacing: 16) {
        Text(Strings.Wallet.transactionDetailsTitle)
          .font(.title2.weight(.medium))
          .frame(maxWidth: .infinity, alignment: .leading)

        DetailsView(
          transaction: transactionDetailsStore.transaction,
          parsedTransaction: transactionDetailsStore.parsedTransaction
        )
        .padding(.bottom, 24 - 16)

        if let parsedTransaction = transactionDetailsStore.parsedTransaction {
          if !parsedTransaction.transaction.txHash.isEmpty {
            HStack {
              VStack(alignment: .leading) {
                rowTitle(Strings.Wallet.transactionDetailsTxHashTitle)
                // zwspOutput to avoid hyphen when wrapped
                Text(parsedTransaction.transaction.txHash.zwspOutput)
                  .font(.callout)
                  .foregroundColor(Color(qoraiSystemName: .textPrimary))
              }
              Spacer()
              WalletIconButton(qoraiSystemName: "qora.copy") {
                UIPasteboard.general.string = parsedTransaction.transaction.txHash
              }
              WalletIconButton(systemName: "arrow.up.forward.square") {
                if let txNetwork = self.networkStore.allChains.first(where: {
                  $0.chainId == transactionDetailsStore.transaction.chainId
                }),
                  let url = txNetwork.txBlockExplorerLink(
                    txHash: transactionDetailsStore.transaction.txHash,
                    for: txNetwork.coin
                  )
                {
                  openWalletURL(url)
                }
              }
            }
          }

          Divider()

          HStack {
            VStack(alignment: .leading) {
              rowTitle(Strings.Wallet.swapCryptoFromTitle)
              if !parsedTransaction.fromAccountInfo.address.isEmpty {
                AddressView(address: parsedTransaction.fromAccountInfo.address) {
                  // zwspOutput to avoid hyphen when wrapped
                  Text(parsedTransaction.fromAccountInfo.address.zwspOutput)
                    .font(.callout)
                    .foregroundColor(Color(qoraiSystemName: .textPrimary))
                  if isLocalAccount(
                    address: parsedTransaction.fromAccountInfo.address,
                    namedAddress: parsedTransaction.namedFromAddress
                  ) {  // only show named address if its actual name, not truncated address.
                    Text(parsedTransaction.namedFromAddress)
                      .font(.footnote)
                      .foregroundColor(Color(qoraiSystemName: .textTertiary))
                  }
                }
              } else {  // Show account name only (no address for Bitcoin).
                Text(parsedTransaction.namedFromAddress)
                  .font(.callout)
                  .foregroundColor(Color(qoraiSystemName: .textPrimary))
              }
            }
            Spacer()
            if !parsedTransaction.fromAccountInfo.address.isEmpty {
              WalletIconButton(qoraiSystemName: "qora.copy") {
                UIPasteboard.general.string = parsedTransaction.fromAccountInfo.address
              }
            }
          }

          Divider()

          HStack {
            VStack(alignment: .leading) {
              rowTitle(Strings.Wallet.swapCryptoToTitle)
              AddressView(address: parsedTransaction.toAddress) {
                // zwspOutput to avoid hyphen when wrapped
                Text(parsedTransaction.toAddress.zwspOutput)
                  .font(.callout)
                  .foregroundColor(Color(qoraiSystemName: .textPrimary))
                if isLocalAccount(
                  address: parsedTransaction.toAddress,
                  namedAddress: parsedTransaction.namedToAddress
                ) {  // only show named address if its actual name, not truncated address.
                  Text(parsedTransaction.namedToAddress)
                    .font(.footnote)
                    .foregroundColor(Color(qoraiSystemName: .textTertiary))
                }
              }
            }
            Spacer()
            WalletIconButton(qoraiSystemName: "qora.copy") {
              UIPasteboard.general.string = parsedTransaction.toAddress
            }
          }

          Divider()

          if let gasFee = parsedTransaction.gasFee {
            VStack(alignment: .leading) {
              rowTitle(Strings.Wallet.transactionFee)
              Text("\(gasFee.fee) \(parsedTransaction.network.nativeToken.symbol) ")
                .foregroundColor(Color(qoraiSystemName: .textPrimary))
                + Text("(\(gasFee.fiat))")
                .foregroundColor(Color(qoraiSystemName: .textTertiary))
                .font(.callout)
            }
            .frame(maxWidth: .infinity, alignment: .leading)
          }

          if transactionDetailsStore.transaction.isRetriable {
            Divider()

            WalletLoadingButton(
              isLoading: transactionDetailsStore.isLoadingTransactionAction,
              action: {
                handleTransactionFollowUpAction(.retry)
              },
              label: {
                Label(
                  TransactionFollowUpAction.retry.buttonTitle,
                  qoraiSystemImage: TransactionFollowUpAction.retry.qoraiSystemImage
                )
                .multilineTextAlignment(.center)
                .frame(maxWidth: .infinity)
              }
            )
            .buttonStyle(QoraiOutlineButtonStyle(size: .large))
          }
          if transactionDetailsStore.isCancelOrSpeedupAvailable {
            Divider()

            WalletLoadingButton(
              isLoading: transactionDetailsStore.isLoadingTransactionAction,
              action: {
                handleTransactionFollowUpAction(.speedUp)
              },
              label: {
                Label(
                  TransactionFollowUpAction.speedUp.buttonTitle,
                  qoraiSystemImage: TransactionFollowUpAction.speedUp.qoraiSystemImage
                )
                .multilineTextAlignment(.center)
                .frame(maxWidth: .infinity)
              }
            )
            .buttonStyle(QoraiFilledButtonStyle(size: .large))

            WalletLoadingButton(
              isLoading: transactionDetailsStore.isLoadingTransactionAction,
              action: {
                handleTransactionFollowUpAction(.cancel)
              },
              label: {
                Text(TransactionFollowUpAction.cancel.buttonTitle)
                  .multilineTextAlignment(.center)
                  .foregroundColor(Color(.qoraiBlurple))
                  .font(QoraiButtonSize.large.font)
                  .frame(maxWidth: .infinity)
              }
            )
          }
        }
      }
      .padding(.vertical, 24)
      .padding(.horizontal, 16)
    }
    .background(Color(qoraiSystemName: .containerBackground))
    .errorAlert(errorMessage: $errorMessage)
    .onAppear {
      transactionDetailsStore.update()
    }
  }

  private func handleTransactionFollowUpAction(_ action: TransactionFollowUpAction) {
    Task { @MainActor in
      guard let errorMessage = await transactionDetailsStore.handleTransactionFollowUpAction(action)
      else {
        dismiss()
        return
      }
      self.errorMessage = errorMessage
    }
  }

  private func isLocalAccount(address: String, namedAddress: String) -> Bool {
    if namedAddress.caseInsensitiveCompare(address) == .orderedSame
      || namedAddress.caseInsensitiveCompare(address.truncatedAddress) == .orderedSame
      || namedAddress.isEmpty
    {
      return false
    }
    return true
  }

  private func rowTitle(_ title: String) -> Text {
    Text(title)
      .font(.callout.weight(.semibold))
      .foregroundColor(Color(qoraiSystemName: .textTertiary))
  }
}

private struct DetailsView: View {

  let transaction: QoraiWallet.TransactionInfo
  let parsedTransaction: ParsedTransaction?

  var body: some View {
    VStack(spacing: 16) {
      if transaction.isSend {
        TransactionDetailsSendContent(
          transaction: transaction,
          parsedTransaction: parsedTransaction
        )
      } else if transaction.isApprove {
        TransactionDetailsApproveContent(
          transaction: transaction,
          parsedTransaction: parsedTransaction
        )
      } else if transaction.isSwap {
        TransactionDetailsSwapContent(
          transaction: transaction,
          parsedTransaction: parsedTransaction
        )
      }

      TransactionStatusBadgeView(
        status: parsedTransaction?.transaction.txStatus ?? transaction.txStatus
      )

      VStack(spacing: 4) {
        Text(transaction.createdTime, style: .date)
          .font(.callout)
          .foregroundColor(Color(qoraiSystemName: .textPrimary))
        Text(parsedTransaction?.network.chainName ?? "")
          .font(.footnote)
          .foregroundColor(Color(qoraiSystemName: .textSecondary))
      }
    }
    .padding(.horizontal)
    .padding(.vertical, 24)
    .frame(maxWidth: .infinity)
    .background(background)
    .cornerRadius(16)
    .clipShape(RoundedRectangle(cornerRadius: 16))
  }

  private var background: some View {
    Color(qoraiSystemName: .containerHighlight)
      .overlay {
        Color(qoraiSystemName: .containerBackground)
          .mask {
            Image("tx-details-lines", bundle: .module)
              .resizable()
              .aspectRatio(contentMode: .fill)
          }
      }
  }
}

private struct TransactionDetailsSendContent: View {

  var transaction: QoraiWallet.TransactionInfo
  var parsedTransaction: ParsedTransaction?

  /// Send value including symbol when available, or name for NFTs
  private var transactionValue: String {
    guard let parsedTransaction else { return "" }
    switch parsedTransaction.details {
    case .ethSend(let details),
      .erc20Transfer(let details),
      .solSystemTransfer(let details),
      .solSplTokenTransfer(let details),
      .btcSend(let details),
      .zecSend(let details):
      if let fromToken = details.fromToken {
        if fromToken.isNft || fromToken.isErc721 || fromToken.isErc1155 {
          return fromToken.name
        }
        return String(format: "%@ %@", details.fromAmount, fromToken.symbol)
      }
      return details.fromAmount
    case .filSend(let details):
      if let sendToken = details.sendToken {
        return String(format: "%@ %@", details.sendAmount, sendToken.symbol)
      }
      return details.sendAmount
    case .solDappTransaction(let details):
      if let symbol = details.symbol {
        return String(format: "%@ %@", details.fromAmount, symbol)
      }
      return details.fromAmount
    case .erc721Transfer(let details):
      if let token = details.fromToken {
        return token.name
      }
      return ""
    case .ethSwap, .solSwapTransaction, .ethErc20Approve, .other:
      // should not be used in this view...
      return ""
    }
  }

  /// Fiat value or symbol for NFTs
  private var transactionFiatValue: String? {
    guard let parsedTransaction else { return nil }
    switch parsedTransaction.details {
    case .ethSend(let details),
      .erc20Transfer(let details),
      .solSystemTransfer(let details),
      .solSplTokenTransfer(let details),
      .btcSend(let details):
      if let fromToken = details.fromToken,
        fromToken.isNft || fromToken.isErc721 || fromToken.isErc1155
      {
        return fromToken.symbol
      }
      return details.fromFiat
    case .filSend(let details):
      return details.sendFiat
    case .solDappTransaction, .erc721Transfer:
      return nil  // unknown fiat
    default:
      return nil
    }
  }

  private var tokenSent: QoraiWallet.BlockchainToken? {
    switch parsedTransaction?.details {
    case .ethSend(let details),
      .erc20Transfer(let details),
      .solSystemTransfer(let details),
      .solSplTokenTransfer(let details),
      .btcSend(let details):
      return details.fromToken
    case .filSend(let details):
      return details.sendToken
    case .erc721Transfer(let details):
      return details.fromToken
    case .solDappTransaction:
      return nil  // unknown token
    default:
      return nil
    }
  }

  private var nftMetadataUrl: URL? {
    switch parsedTransaction?.details {
    case .solSplTokenTransfer(let details):
      return details.fromTokenMetadata?.imageURL
    case .erc721Transfer(let details):
      return details.nftMetadata?.imageURL
    default:
      return nil
    }
  }

  @ScaledMetric private var nftLength: CGFloat = 128
  private let maxNFTLength: CGFloat = 160

  var body: some View {
    VStack(spacing: 4) {
      if let token = tokenSent, let network = parsedTransaction?.network {
        if token.isNft {
          NFTIconView(
            token: token,
            network: network,
            url: nftMetadataUrl,
            shouldShowNetworkIcon: false,
            length: nftLength,
            maxLength: maxNFTLength
          )
        } else {
          AssetIconView(
            token: token,
            network: network
          )
        }
      } else {
        GenericAssetIconView()
      }
      Text(Strings.Wallet.sent)
        .font(.callout.weight(.semibold))
        .foregroundColor(Color(qoraiSystemName: .textTertiary))
      Text(transactionValue)
        .font(.body.weight(.medium))
        .foregroundColor(Color(qoraiSystemName: .textPrimary))
      if let transactionFiatValue {
        Text(transactionFiatValue)
          .font(.footnote)
          .foregroundColor(Color(qoraiSystemName: .textSecondary))
      }
    }
  }
}

private struct TransactionDetailsApproveContent: View {

  var transaction: QoraiWallet.TransactionInfo
  var parsedTransaction: ParsedTransaction?

  private var approvalValue: String? {
    if case .ethErc20Approve(let details) = parsedTransaction?.details {
      if let token = details.token {
        return "\(details.approvalAmount) \(token.symbol)"
      }
      return details.approvalAmount
    }
    return nil
  }

  var body: some View {
    VStack(spacing: 8) {
      Circle()
        .fill(Color(qoraiSystemName: .containerBackground))
        .frame(width: 40, height: 40)
        .overlay {
          Image(qoraiSystemName: "qora.check.normal")
            .imageScale(.large)
            .padding()
        }
        .shadow(color: .black.opacity(0.07), radius: 2, x: 0, y: 1)
      Text(Strings.Wallet.transactionTypeApprove)
        .font(.callout.weight(.semibold))
        .foregroundColor(Color(qoraiSystemName: .textTertiary))
      if let approvalValue {
        Text(approvalValue)
          .font(.body.weight(.medium))
          .foregroundColor(Color(qoraiSystemName: .textPrimary))
      }
    }
  }
}

private struct TransactionDetailsSwapContent: View {

  var transaction: QoraiWallet.TransactionInfo
  var parsedTransaction: ParsedTransaction?

  @ScaledMetric(relativeTo: .body) private var assetIconLength: CGFloat = 32
  private let maxAssetIconLength: CGFloat = 64

  private var fromToken: QoraiWallet.BlockchainToken? {
    if case .ethSwap(let details) = parsedTransaction?.details {
      return details.fromToken
    }
    return nil
  }

  private var fromAmount: String? {
    if case .ethSwap(let details) = parsedTransaction?.details {
      return details.fromAmount
    }
    return nil
  }

  private var toToken: QoraiWallet.BlockchainToken? {
    if case .ethSwap(let details) = parsedTransaction?.details {
      return details.toToken
    }
    return nil
  }

  private var minBuyAmount: String? {
    if case .ethSwap(let details) = parsedTransaction?.details {
      return details.minBuyAmount
    }
    return nil
  }

  private var transactionFiatValue: String? {
    if case .ethSwap(let details) = parsedTransaction?.details {
      return details.fromFiat
    }
    return nil
  }

  private var isSolanaSwap: Bool {
    transaction.txType == .solanaSwap
  }

  var body: some View {
    VStack(spacing: 4) {
      Text(isSolanaSwap ? Strings.Wallet.transactionSummarySolanaSwap : Strings.Wallet.swap)
        .font(.callout.weight(.semibold))
        .foregroundColor(Color(qoraiSystemName: .textTertiary))
      if let parsedTransaction {
        if isSolanaSwap {
          HStack {
            GenericAssetIconView(
              backgroundColor: Color(qoraiSystemName: .neutral40),
              iconColor: Color.white,
              length: assetIconLength,
              maxLength: maxAssetIconLength
            )
            Image(qoraiSystemName: "qora.arrow.right")
            GenericAssetIconView(
              backgroundColor: Color(qoraiSystemName: .neutral20),
              iconColor: Color.black,
              length: assetIconLength,
              maxLength: maxAssetIconLength
            )
          }
        } else {
          VStack {
            HStack {
              if let fromToken {
                AssetIconView(
                  token: fromToken,
                  network: parsedTransaction.network,
                  length: assetIconLength,
                  maxLength: maxAssetIconLength
                )
              } else {
                GenericAssetIconView(length: assetIconLength, maxLength: maxAssetIconLength)
              }
              if let fromAmount {
                if let fromToken {
                  Text(verbatim: "\(fromAmount) \(fromToken.symbol)")
                } else {
                  Text(verbatim: fromAmount)
                }
              }
            }
            Image(qoraiSystemName: "qora.arrow.right")
            HStack {
              if let toToken {
                AssetIconView(
                  token: toToken,
                  network: parsedTransaction.network,
                  length: assetIconLength,
                  maxLength: maxAssetIconLength
                )
              } else {
                GenericAssetIconView(length: assetIconLength, maxLength: maxAssetIconLength)
              }
              if let minBuyAmount {
                if let toToken {
                  Text(verbatim: "\(minBuyAmount) \(toToken.symbol)")
                } else {
                  Text(verbatim: minBuyAmount)
                }
              }
            }
          }
          .font(.body.weight(.medium))
        }
      }
      if let transactionFiatValue {
        Text(transactionFiatValue)
          .font(.footnote)
          .foregroundColor(Color(qoraiSystemName: .textSecondary))
      }
    }
  }
}

private struct TransactionStatusBadgeView: View {

  let status: QoraiWallet.TransactionStatus

  var body: some View {
    HStack {
      if status.shouldShowLoadingStatus {
        ProgressView()
          .progressViewStyle(.qoraiCircular(size: .mini))
      } else if status.shouldShowSuccessStatus {
        Image(qoraiSystemName: "qora.check.circle-outline")
          .foregroundColor(Color(qoraiSystemName: .systemfeedbackSuccessIcon))
      } else if status.shouldShowErrorStatus {
        Image(qoraiSystemName: "qora.warning.circle-outline")
          .foregroundColor(Color(qoraiSystemName: .systemfeedbackErrorIcon))
      }
      Text(status.localizedDescription)
        .foregroundColor(status.badgeTextColor)
    }
    .font(.caption)
    .padding(.horizontal, 6)
    .padding(.vertical, 4)
    .background(
      RoundedRectangle(cornerRadius: 4)
        .fill(status.badgeBackgroundColor)
    )
  }
}

extension QoraiWallet.TransactionStatus {
  /// If we should show transaction status as loading
  fileprivate var shouldShowLoadingStatus: Bool {
    switch self {
    case .unapproved, .submitted:
      return true
    default:
      return false
    }
  }

  /// If we should show transaction status successful icon
  fileprivate var shouldShowSuccessStatus: Bool {
    switch self {
    case .approved, .confirmed, .signed:
      return true
    default:
      return false
    }
  }

  /// If we should show transaction status failure icon
  fileprivate var shouldShowErrorStatus: Bool {
    switch self {
    case .error, .dropped, .rejected:
      return true
    default:
      return false
    }
  }

  /// Color of status text on status badge
  fileprivate var badgeTextColor: Color {
    switch self {
    case .confirmed, .approved:
      return Color(qoraiSystemName: .systemfeedbackSuccessText)
    case .rejected, .error, .dropped:
      return Color(qoraiSystemName: .systemfeedbackErrorText)
    case .unapproved:
      return Color(qoraiSystemName: .textSecondary)
    case .submitted, .signed:
      return Color(qoraiSystemName: .systemfeedbackInfoText)
    @unknown default:
      return Color.clear
    }
  }

  /// Color of status badge
  fileprivate var badgeBackgroundColor: Color {
    switch self {
    case .confirmed, .approved:
      return Color(qoraiSystemName: .systemfeedbackSuccessBackground)
    case .rejected, .error, .dropped:
      return Color(qoraiSystemName: .systemfeedbackErrorBackground)
    case .unapproved:
      return Color(qoraiSystemName: .dividerStrong)
    case .submitted, .signed:
      return Color(qoraiSystemName: .systemfeedbackInfoBackground)
    @unknown default:
      return Color.clear
    }
  }
}
