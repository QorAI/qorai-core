// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import SwiftUI

struct TransactionSummaryViewContainer: View {

  let parsedTransaction: ParsedTransaction

  var body: some View {
    switch parsedTransaction.details {
    case .ethSend(let details),
      .erc20Transfer(let details),
      .solSystemTransfer(let details),
      .solSplTokenTransfer(let details),
      .btcSend(let details),
      .zecSend(let details):
      SendTransactionSummaryView(
        sentFromAccountName: parsedTransaction.namedFromAddress,
        token: details.fromToken,
        nftMetadata: details.fromTokenMetadata,
        network: parsedTransaction.network,
        valueSent: details.fromAmount,
        fiatValueSent: details.fromFiat ?? "",
        status: parsedTransaction.transaction.txStatus,
        time: parsedTransaction.transaction.createdTime
      )
    case .filSend(let details):
      SendTransactionSummaryView(
        sentFromAccountName: parsedTransaction.namedFromAddress,
        token: details.sendToken,
        network: parsedTransaction.network,
        valueSent: details.sendAmount,
        fiatValueSent: details.sendFiat ?? "",
        status: parsedTransaction.transaction.txStatus,
        time: parsedTransaction.transaction.createdTime
      )
    case .ethSwap(let details):
      SwapTransactionSummaryView(
        swappedOnAccountName: parsedTransaction.namedFromAddress,
        fromToken: details.fromToken,
        toToken: details.toToken,
        network: parsedTransaction.network,
        fromValue: details.fromAmount,
        toValue: details.minBuyAmount,
        status: parsedTransaction.transaction.txStatus,
        time: parsedTransaction.transaction.createdTime
      )
    case .solSwapTransaction:
      SolanaSwapTransactionSummaryView(
        swappedOnAccountName: parsedTransaction.namedFromAddress,
        network: parsedTransaction.network,
        status: parsedTransaction.transaction.txStatus,
        time: parsedTransaction.transaction.createdTime
      )
    case .ethErc20Approve(let details):
      ApprovalTransactionSummaryView(
        fromAccountName: parsedTransaction.namedFromAddress,
        token: details.token,
        network: parsedTransaction.network,
        valueApproved: details.approvalAmount,
        fiatValueApproved: details.approvalFiat,
        status: parsedTransaction.transaction.txStatus,
        time: parsedTransaction.transaction.createdTime
      )
    case .erc721Transfer(let details):
      SendTransactionSummaryView(
        sentFromAccountName: parsedTransaction.namedFromAddress,
        token: details.fromToken,
        nftMetadata: details.nftMetadata,
        network: parsedTransaction.network,
        valueSent: nil,
        fiatValueSent: nil,
        status: parsedTransaction.transaction.txStatus,
        time: parsedTransaction.transaction.createdTime
      )
    case .solDappTransaction:
      SendTransactionSummaryView(
        sentFromAccountName: parsedTransaction.namedFromAddress,
        token: parsedTransaction.network.nativeToken,
        network: parsedTransaction.network,
        valueSent: nil,
        fiatValueSent: nil,
        status: parsedTransaction.transaction.txStatus,
        time: parsedTransaction.transaction.createdTime
      )
    case .other:
      SendTransactionSummaryView(
        sentFromAccountName: parsedTransaction.namedFromAddress,
        token: nil,
        network: parsedTransaction.network,
        valueSent: nil,
        fiatValueSent: nil,
        status: parsedTransaction.transaction.txStatus,
        time: parsedTransaction.transaction.createdTime
      )
    }
  }
}

struct SendTransactionSummaryView: View {

  let sentFromAccountName: String
  let token: QoraiWallet.BlockchainToken?
  let nftMetadata: QoraiWallet.NftMetadata?
  let network: QoraiWallet.NetworkInfo
  let valueSent: String?
  let fiatValueSent: String?
  let status: QoraiWallet.TransactionStatus
  let time: Date

  init(
    sentFromAccountName: String,
    token: QoraiWallet.BlockchainToken?,
    nftMetadata: QoraiWallet.NftMetadata? = nil,
    network: QoraiWallet.NetworkInfo,
    valueSent: String?,
    fiatValueSent: String?,
    status: QoraiWallet.TransactionStatus,
    time: Date
  ) {
    self.sentFromAccountName = sentFromAccountName
    self.nftMetadata = nftMetadata
    self.token = token
    self.network = network
    self.valueSent = valueSent
    self.fiatValueSent = fiatValueSent
    self.status = status
    self.time = time
  }

  private let primaryFont: Font = .callout.weight(.semibold)
  private let primaryTextColor = Color(qoraiSystemName: .textPrimary)
  private let secondaryFont: Font = .footnote
  private let secondaryTextColor = Color(qoraiSystemName: .textTertiary)

  @ScaledMetric private var length: CGFloat = 32
  private let maxLength: CGFloat = 48
  @ScaledMetric private var networkSymbolLength: CGFloat = 15
  private let maxNetworkSymbolLength: CGFloat = 30

  private var sendTitle: String {
    String.localizedStringWithFormat(
      Strings.Wallet.transactionSummaryIntentLabel,
      Strings.Wallet.sent
    )
  }

  var body: some View {
    VStack {
      HStack {  // header
        Text(time, style: .time)
        Image(qoraiSystemName: "qora.send")
          .imageScale(.small)
          .foregroundColor(Color(qoraiSystemName: .iconDefault))
        Text(sendTitle) + Text(" " + sentFromAccountName).bold()
      }
      .font(secondaryFont)
      .foregroundColor(secondaryTextColor)
      .frame(maxWidth: .infinity, alignment: .leading)

      HStack {
        Group {
          if let token {
            if token.isNft || token.isErc721 {
              NFTIconView(
                token: token,
                network: network,
                url: nftMetadata?.imageURL,
                shouldShowNetworkIcon: true,
                length: length,
                maxLength: maxLength,
                tokenLogoLength: networkSymbolLength,
                maxTokenLogoLength: maxNetworkSymbolLength
              )
            } else {
              AssetIconView(
                token: token,
                network: network,
                shouldShowNetworkIcon: true,
                length: length,
                maxLength: maxLength,
                networkSymbolLength: networkSymbolLength,
                maxNetworkSymbolLength: maxNetworkSymbolLength
              )
            }
          } else {
            GenericAssetIconView(
              length: length,
              maxLength: maxLength
            )
          }
        }
        .overlay(alignment: .topLeading) {
          if status.shouldShowTransactionStatus {
            TransactionStatusBubble(status: status)
          }
        }
        VStack(alignment: .leading) {
          Text(token?.name ?? "")
            .font(primaryFont)
            .foregroundColor(primaryTextColor)
          Text(token?.symbol ?? "")
            .font(secondaryFont)
            .foregroundColor(secondaryTextColor)
        }

        Spacer()

        if let valueSent {
          VStack(alignment: .trailing) {
            Group {
              if let symbol = token?.symbol {
                Text("-\(valueSent) \(symbol)")
                  .font(primaryFont)
                  .foregroundColor(primaryTextColor)
              } else {
                Text("-\(valueSent)")
              }
            }
            .font(primaryFont)
            .foregroundColor(primaryTextColor)
            Text(fiatValueSent ?? "")
              .font(secondaryFont)
              .foregroundColor(secondaryTextColor)
          }
          .multilineTextAlignment(.trailing)
        }
      }
    }
    .multilineTextAlignment(.leading)
    .padding(8)
    .frame(maxWidth: .infinity)
  }
}

struct SwapTransactionSummaryView: View {

  let swappedOnAccountName: String
  let fromToken: QoraiWallet.BlockchainToken?
  let toToken: QoraiWallet.BlockchainToken?
  let network: QoraiWallet.NetworkInfo
  let fromValue: String
  let toValue: String
  let status: QoraiWallet.TransactionStatus
  let time: Date

  init(
    swappedOnAccountName: String,
    fromToken: QoraiWallet.BlockchainToken?,
    toToken: QoraiWallet.BlockchainToken?,
    network: QoraiWallet.NetworkInfo,
    fromValue: String,
    toValue: String,
    status: QoraiWallet.TransactionStatus,
    time: Date
  ) {
    self.swappedOnAccountName = swappedOnAccountName
    self.fromToken = fromToken
    self.toToken = toToken
    self.network = network
    self.fromValue = fromValue
    self.toValue = toValue
    self.status = status
    self.time = time
  }

  private let primaryFont: Font = .callout.weight(.semibold)
  private let primaryTextColor = Color(qoraiSystemName: .textPrimary)
  private let secondaryFont: Font = .footnote
  private let secondaryTextColor = Color(qoraiSystemName: .textTertiary)

  @ScaledMetric private var length: CGFloat = 32
  private let maxLength: CGFloat = 48
  @ScaledMetric private var networkSymbolLength: CGFloat = 15
  private let maxNetworkSymbolLength: CGFloat = 30

  var body: some View {
    VStack {
      HStack {  // header
        Text(time, style: .time)
        Image(qoraiSystemName: "qora.currency.exchange")
          .imageScale(.small)
          .foregroundColor(Color(qoraiSystemName: .iconDefault))
        Text(Strings.Wallet.transactionSummarySwapOn) + Text(" " + swappedOnAccountName).bold()
      }
      .font(secondaryFont)
      .foregroundColor(secondaryTextColor)
      .frame(maxWidth: .infinity, alignment: .leading)

      HStack {
        StackedAssetIconsView(
          bottomToken: fromToken,
          topToken: toToken,
          network: network,
          length: length,
          maxLength: maxLength,
          networkSymbolLength: networkSymbolLength,
          maxNetworkSymbolLength: maxNetworkSymbolLength
        )
        .overlay(alignment: .topLeading) {
          if status.shouldShowTransactionStatus {
            TransactionStatusBubble(status: status)
          }
        }
        HStack {
          Text(fromToken?.symbol ?? "")
            .font(primaryFont)
          Image(qoraiSystemName: "qora.carat.right")
            .resizable()
            .aspectRatio(contentMode: .fit)
            .padding(4)
            .frame(width: 16, height: 16)
            .foregroundColor(Color(qoraiSystemName: .iconDefault))
            .background(Color(qoraiSystemName: .containerHighlight).clipShape(Circle()))
          Text(toToken?.symbol ?? "")
            .font(primaryFont)
        }
        .foregroundColor(primaryTextColor)

        Spacer()

        VStack(alignment: .trailing) {
          Text("-\(fromValue) \(fromToken?.symbol ?? "")")
            .font(secondaryFont)
            .foregroundColor(secondaryTextColor)
          Text("+\(toValue) \(toToken?.symbol ?? "")")
            .font(primaryFont)
            .foregroundColor(primaryTextColor)
        }
        .multilineTextAlignment(.trailing)
      }
    }
    .multilineTextAlignment(.leading)
    .padding(8)
    .frame(maxWidth: .infinity)
  }
}

struct SolanaSwapTransactionSummaryView: View {

  let swappedOnAccountName: String
  let network: QoraiWallet.NetworkInfo
  let status: QoraiWallet.TransactionStatus
  let time: Date

  init(
    swappedOnAccountName: String,
    network: QoraiWallet.NetworkInfo,
    status: QoraiWallet.TransactionStatus,
    time: Date
  ) {
    self.swappedOnAccountName = swappedOnAccountName
    self.network = network
    self.status = status
    self.time = time
  }

  private let primaryFont: Font = .callout.weight(.semibold)
  private let primaryTextColor = Color(qoraiSystemName: .textPrimary)
  private let secondaryFont: Font = .footnote
  private let secondaryTextColor = Color(qoraiSystemName: .textTertiary)

  @ScaledMetric private var length: CGFloat = 32
  private let maxLength: CGFloat = 48
  @ScaledMetric private var networkSymbolLength: CGFloat = 15
  private let maxNetworkSymbolLength: CGFloat = 30

  var body: some View {
    VStack {
      HStack {  // header
        Text(time, style: .time)
        Image(qoraiSystemName: "qora.currency.exchange")
          .imageScale(.small)
          .foregroundColor(Color(qoraiSystemName: .iconDefault))
        Text(Strings.Wallet.transactionSummarySwapOn) + Text(" " + swappedOnAccountName).bold()
      }
      .font(secondaryFont)
      .foregroundColor(secondaryTextColor)
      .frame(maxWidth: .infinity, alignment: .leading)

      HStack {
        StackedAssetIconsView(
          bottomToken: nil,
          topToken: nil,
          network: network,
          length: length,
          maxLength: maxLength,
          networkSymbolLength: networkSymbolLength,
          maxNetworkSymbolLength: maxNetworkSymbolLength
        )
        .overlay(alignment: .topLeading) {
          if status.shouldShowTransactionStatus {
            TransactionStatusBubble(status: status)
          }
        }
        HStack {
          Text(Strings.Wallet.transactionSummarySolanaSwap)
            .font(primaryFont)
        }
        .foregroundColor(primaryTextColor)

        Spacer()
      }
    }
    .multilineTextAlignment(.leading)
    .padding(.horizontal, 8)
    .padding(.vertical, 10)
    .frame(maxWidth: .infinity)
  }
}

struct ApprovalTransactionSummaryView: View {

  let fromAccountName: String
  let token: QoraiWallet.BlockchainToken?
  let network: QoraiWallet.NetworkInfo
  let valueApproved: String
  let fiatValueApproved: String
  let status: QoraiWallet.TransactionStatus
  let time: Date

  init(
    fromAccountName: String,
    token: QoraiWallet.BlockchainToken?,
    network: QoraiWallet.NetworkInfo,
    valueApproved: String,
    fiatValueApproved: String,
    status: QoraiWallet.TransactionStatus,
    time: Date
  ) {
    self.fromAccountName = fromAccountName
    self.token = token
    self.network = network
    self.valueApproved = valueApproved
    self.fiatValueApproved = fiatValueApproved
    self.status = status
    self.time = time
  }

  private let primaryFont: Font = .callout.weight(.semibold)
  private let primaryTextColor = Color(qoraiSystemName: .textPrimary)
  private let secondaryFont: Font = .footnote
  private let secondaryTextColor = Color(qoraiSystemName: .textTertiary)

  @ScaledMetric private var length: CGFloat = 32
  private let maxLength: CGFloat = 48
  @ScaledMetric private var networkSymbolLength: CGFloat = 15
  private let maxNetworkSymbolLength: CGFloat = 30

  private var approvedTitle: String {
    String.localizedStringWithFormat(
      Strings.Wallet.transactionSummaryIntentLabel,
      Strings.Wallet.transactionTypeApprove
    )
  }

  var body: some View {
    VStack {
      HStack {  // header
        Text(time, style: .time)
        Image(qoraiSystemName: "qora.check.normal")
          .imageScale(.small)
          .foregroundColor(Color(qoraiSystemName: .iconDefault))
        Text(approvedTitle) + Text(" " + fromAccountName).bold()
      }
      .font(secondaryFont)
      .foregroundColor(secondaryTextColor)
      .frame(maxWidth: .infinity, alignment: .leading)

      HStack {
        Group {
          if let token {
            AssetIconView(
              token: token,
              network: network,
              shouldShowNetworkIcon: true,
              length: length,
              maxLength: maxLength,
              networkSymbolLength: networkSymbolLength,
              maxNetworkSymbolLength: maxNetworkSymbolLength
            )
          } else {
            GenericAssetIconView(
              length: length,
              maxLength: maxLength
            )
          }
        }
        .overlay(alignment: .topLeading) {
          if status.shouldShowTransactionStatus {
            TransactionStatusBubble(status: status)
          }
        }
        VStack(alignment: .leading) {
          Text(token?.name ?? "")
            .font(primaryFont)
            .foregroundColor(primaryTextColor)
          Text(token?.symbol ?? "")
            .font(secondaryFont)
            .foregroundColor(secondaryTextColor)
        }

        Spacer()

        VStack(alignment: .trailing) {
          Text(valueApproved)
            .font(primaryFont)
            .foregroundColor(primaryTextColor)
          Text(fiatValueApproved)
            .font(secondaryFont)
            .foregroundColor(secondaryTextColor)
        }
        .multilineTextAlignment(.trailing)
      }
    }
    .multilineTextAlignment(.leading)
    .padding(8)
    .frame(maxWidth: .infinity)
  }
}

#if DEBUG
struct TransactionSummaryRow_Previews: PreviewProvider {
  static var previews: some View {
    VStack {
      Group {
        SendTransactionSummaryView(
          sentFromAccountName: "Account 1",
          token: .mockUSDCToken,
          network: .mockMainnet,
          valueSent: "37.8065",
          fiatValueSent: "$37.80",
          status: .unapproved,
          time: Date()
        )
        Divider()
        SendTransactionSummaryView(
          sentFromAccountName: "Account 1",
          token: .mockERC721NFTToken,
          network: .mockMainnet,
          valueSent: nil,
          fiatValueSent: nil,
          status: .submitted,
          time: Date()
        )
      }
      Divider()
      Group {
        SwapTransactionSummaryView(
          swappedOnAccountName: "Account 1",
          fromToken: .previewToken,
          toToken: .previewDaiToken,
          network: .mockMainnet,
          fromValue: "0.02",
          toValue: "189.301",
          status: .confirmed,
          time: Date()
        )
        Divider()
        SolanaSwapTransactionSummaryView(
          swappedOnAccountName: "Account 1",
          network: .mockMainnet,
          status: .error,
          time: Date()
        )
      }
      Divider()
      Group {
        ApprovalTransactionSummaryView(
          fromAccountName: "Account 1",
          token: .previewToken,
          network: .mockMainnet,
          valueApproved: "Unlimited",
          fiatValueApproved: "Unlimited",
          status: .submitted,
          time: Date()
        )
        Divider()
        ApprovalTransactionSummaryView(
          fromAccountName: "Account 1",
          token: .mockUSDCToken,
          network: .mockMainnet,
          valueApproved: "1",
          fiatValueApproved: "$1,500",
          status: .submitted,
          time: Date()
        )
      }
    }
    .previewLayout(.sizeThatFits)
  }
}
#endif

private struct TransactionStatusBubble: View {

  let status: QoraiWallet.TransactionStatus

  var body: some View {
    Circle()
      .fill(status.bubbleBackgroundColor)
      .frame(width: 12, height: 12)
      .overlay(
        Circle()
          .stroke(lineWidth: 1)
          .foregroundColor(Color(qoraiSystemName: .containerBackground))
      )
      .overlay {
        if status.shouldShowLoadingAnimation {
          ProgressView()
            .progressViewStyle(.qoraiCircular(size: .mini))
        }
      }
  }
}

extension QoraiWallet.TransactionStatus {
  /// If we should show transaction status bubble
  fileprivate var shouldShowTransactionStatus: Bool {
    switch self {
    case .approved, .confirmed, .signed:
      return false
    default:
      return true
    }
  }

  /// If we should show transaction status as loading
  fileprivate var shouldShowLoadingAnimation: Bool {
    switch self {
    case .unapproved, .approved, .submitted:
      return true
    default:
      return false
    }
  }

  /// Color of status bubble
  fileprivate var bubbleBackgroundColor: Color {
    switch self {
    case .confirmed, .approved:
      return Color(qoraiSystemName: .systemfeedbackSuccessBackground)
    case .rejected, .error, .dropped:
      return Color(qoraiSystemName: .systemfeedbackErrorIcon)
    case .unapproved:
      return Color(qoraiSystemName: .legacyInteractive8)
    case .submitted, .signed:
      return Color(qoraiSystemName: .blue40)
    @unknown default:
      return Color.clear
    }
  }
}

#if DEBUG
struct TransactionStatusBubble_Previews: PreviewProvider {
  static var previews: some View {
    TransactionStatusBubble(status: .unapproved)
      .previewLayout(.sizeThatFits)
  }
}
#endif
