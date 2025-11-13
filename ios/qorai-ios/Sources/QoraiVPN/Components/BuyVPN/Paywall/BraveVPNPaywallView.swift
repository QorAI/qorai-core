// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiStore
import QoraiStrings
import QoraiUI
import DesignSystem
import Preferences
import StoreKit
import SwiftUI
import os.log

public struct QoraiVPNPaywallView: View {
  @ObservedObject var iapObserverManager: QoraiVPNIAPObserverManager
  @ObservedObject private var freeTrialUsed = Preferences.VPN.freeTrialUsed

  private let openVPNAuthenticationInNewTab: () -> Void
  private let installVPNProfile: () -> Void
  private var openDirectCheckoutInNewTab: () -> Void
  private var openLearnMoreInNewTab: () -> Void

  @State private var selectedTierType: QoraiVPNSubscriptionTier = .yearly
  @State private var availableTierTypes: [QoraiVPNSubscriptionTier] = [.yearly, .monthly]
  @State private var isShowingPurchaseAlert = false
  @State private var iapRestoreTimer: Task<Void, Error>?

  @Environment(\.presentationMode) @Binding private var presentationMode
  @Environment(\.sizeCategory) private var sizeCategory
  @Environment(\.horizontalSizeClass) private var horizontalSizeClass
  @Environment(\.verticalSizeClass) private var verticalSizeClass
  @Environment(\.pixelLength) private var pixelLength
  @Environment(\.allowExternalPurchaseLinks) private var allowExternalPurchaseLinks

  public init(
    openVPNAuthenticationInNewTab: @escaping (() -> Void),
    openDirectCheckoutInNewTab: @escaping () -> Void,
    openLearnMoreInNewTab: @escaping () -> Void,
    installVPNProfile: @escaping () -> Void
  ) {
    self.iapObserverManager = QoraiVPNIAPObserverManager(iapObserver: QoraiVPN.iapObserver)
    self.openVPNAuthenticationInNewTab = openVPNAuthenticationInNewTab
    self.openDirectCheckoutInNewTab = openDirectCheckoutInNewTab
    self.openLearnMoreInNewTab = openLearnMoreInNewTab
    self.installVPNProfile = installVPNProfile
  }

  public var body: some View {
    VStack(spacing: 0) {
      ScrollView {
        Group {
          if sizeCategory.isAccessibilityCategory
            || (horizontalSizeClass == .compact && verticalSizeClass == .regular)
          {
            verticalContentView
              .padding(.horizontal, 16)
          } else {
            horizontalContentView
              .padding(24.0)
          }
        }
      }
      paywallActionContainerView
    }
    .navigationTitle(Strings.VPN.vpnName)
    .navigationBarTitleDisplayMode(.inline)
    .background(
      Color(qoraiSystemName: .primitivePrimary10)
        .edgesIgnoringSafeArea(.all)
    )
    .alert(isPresented: $isShowingPurchaseAlert) {
      Alert(
        title: Text(Strings.VPN.vpnErrorPurchaseFailedTitle),
        message: Text(
          Strings.VPN.vpnErrorPurchaseFailedBody
        ),
        dismissButton: .default(Text(Strings.OKString))
      )
    }
    .onChange(of: iapObserverManager.paymentStatus) { status in
      if case .failure(let error) = status {
        resetTheRestoreTimerIfNecessary()

        if case .transactionError(let err) = error, err?.code == SKError.paymentCancelled {
          return
        }

        isShowingPurchaseAlert = true
      } else if case .success(let receiptValidationRequired) = status {
        resetTheRestoreTimerIfNecessary()

        if receiptValidationRequired {
          Task {
            do {
              _ = try await QoraiVPN.validateReceiptData()
            } catch {
              Logger.module.error("Error validating receipt: \(error)")
            }
          }
        }

        presentationMode.dismiss()
        installVPNProfile()
      }
    }
    .onDisappear {
      iapRestoreTimer?.cancel()
    }
  }

  private var horizontalContentView: some View {
    HStack {
      VStack(alignment: .leading, spacing: 34) {
        QoraiVPNPremiumUpsellView()
        QoraiVPNPoweredBrandView()
        Spacer()
      }
      VStack(spacing: 8.0) {
        tierSelection
        QoraiVPNSubscriptionActionView(
          refreshCredentials: {
            refreshCredential()
          },
          redeedPromoCode: {
            redeemPromoCode()
          },
          learnMore: {
            openLearnMoreInNewTab()
          }
        )
      }
    }
  }

  private var verticalContentView: some View {
    VStack(spacing: 8.0) {
      QoraiVPNPremiumUpsellView()
        .padding(.top, 24.0)
        .padding(.bottom, 8.0)
      separatorView
        .padding(.horizontal, -16.0)
      QoraiVPNPoweredBrandView()
        .padding()
      tierSelection
      QoraiVPNSubscriptionActionView(
        refreshCredentials: {
          refreshCredential()
        },
        redeedPromoCode: {
          redeemPromoCode()
        },
        learnMore: {
          openLearnMoreInNewTab()
        }
      )
      .padding(.bottom, 8.0)
    }
  }

  private var separatorView: some View {
    Color(qoraiSystemName: .primitivePrimary25)
      .frame(height: pixelLength)
  }

  private var tierSelection: some View {
    VStack {
      if availableTierTypes.contains(.yearly) {
        QoraiVPNPremiumTierSelectionView(
          originalProduct: QoraiVPNProductInfo.yearlySubProduct,
          discountedProduct: QoraiVPNProductInfo.monthlySubProduct,
          type: .yearly,
          selectedTierType: $selectedTierType
        )
      }

      if availableTierTypes.contains(.monthly) {
        QoraiVPNPremiumTierSelectionView(
          originalProduct: QoraiVPNProductInfo.monthlySubProduct,
          discountedProduct: nil,
          type: .monthly,
          selectedTierType: $selectedTierType
        )
      }

      Text(Strings.VPN.paywallDisclaimer)
        .multilineTextAlignment(.leading)
        .font(.footnote)
        .frame(maxWidth: .infinity, alignment: .leading)
        .fixedSize(horizontal: false, vertical: true)
        .foregroundStyle(Color(qoraiSystemName: .primitiveBlurple95))
        .padding([.horizontal], 16.0)
        .padding([.top], 12.0)
    }
  }

  private var standardPaywallActionView: some View {
    Button {
      addPaymentForSubcription(type: selectedTierType)
    } label: {
      HStack {
        if iapObserverManager.paymentStatus == .ongoing {
          ProgressView()
            .tint(Color.white)
            .padding()
        } else {
          Text(
            freeTrialUsed.value
              ? Strings.VPN.activateSubscriptionAction.capitalized
              : Strings.VPN.freeTrialPeriodAction.capitalized
          )
          .font(.headline)
          .foregroundColor(Color(.white))
          .padding()
        }
      }
      .frame(maxWidth: .infinity)
      .background(
        LinearGradient(
          colors: [
            Color(qoraiSystemName: .primitiveBrandsRorange2),
            Color(qoraiSystemName: .primitiveBrandsRorange3),
          ],
          startPoint: .top,
          endPoint: .bottom
        ),
        in: .rect(cornerRadius: 12, style: .continuous)
      )
    }
    .disabled(iapObserverManager.paymentStatus == .ongoing)
    .padding(16)
    .overlay(alignment: .top) {
      separatorView
    }
  }

  private var externalPurchasesAllowedActionView: some View {
    VStack(spacing: 16) {
      VStack(spacing: 0) {
        Text(Strings.Paywall.startTrialTitle)
          .font(.callout.weight(.semibold))
        Text(Strings.Paywall.startTrialSubtitle)
          .font(.footnote)
      }
      .multilineTextAlignment(.center)
      VStack {
        Button {
          addPaymentForSubcription(type: selectedTierType)
        } label: {
          HStack {
            Text(Strings.Paywall.appStoreCheckoutOptionTitle)
              .font(.callout.weight(.semibold))
              .multilineTextAlignment(.leading)
            Spacer()
            Text(Strings.Paywall.appStoreCheckoutOptionSubtitle)
              .font(.footnote)
              .multilineTextAlignment(.trailing)
          }
          .opacity(iapObserverManager.paymentStatus == .ongoing ? 0 : 1)
          .overlay {
            if iapObserverManager.paymentStatus == .ongoing {
              ProgressView()
                .tint(Color.white)
                .padding()
            }
          }
          .frame(maxWidth: .infinity)
          .padding(12)
          .frame(minHeight: 52)
          .background(
            Color(qoraiSystemName: .primitiveBlurple35),
            in: .rect(cornerRadius: 12, style: .continuous)
          )
        }
        .disabled(iapObserverManager.paymentStatus == .ongoing)
        Button {
          openDirectCheckoutInNewTab()
        } label: {
          HStack {
            Text(Strings.Paywall.qoraiAccountCheckoutOptionTitle)
              .font(.callout.weight(.semibold))
              .multilineTextAlignment(.leading)
            Spacer()
            Text(
              LocalizedStringKey(
                String.localizedStringWithFormat(
                  Strings.Paywall.qoraiAccountCheckoutOptionSubtitle,
                  ExternalPurchaseLinksSupport.discountCode,
                  ExternalPurchaseLinksSupport.discountAmount.formatted(.percent)
                )
              )
            )
            .multilineTextAlignment(.trailing)
            .font(.footnote)
          }
          .frame(maxWidth: .infinity)
          .padding(12)
          .frame(minHeight: 52)
          .background(
            LinearGradient(
              colors: [
                Color(qoraiSystemName: .primitiveBrandsRorange2),
                Color(qoraiSystemName: .primitiveBrandsRorange3),
              ],
              startPoint: .top,
              endPoint: .bottom
            ),
            in: .rect(cornerRadius: 12, style: .continuous)
          )
        }
      }
    }
    .foregroundStyle(Color.white)
    .frame(maxWidth: .infinity)
    .padding(16)
    .background(
      LinearGradient(
        colors: [
          Color(qoraiSystemName: .primitiveBlurple20),
          Color(qoraiSystemName: .primitiveBlurple10),
        ],
        startPoint: .top,
        endPoint: .bottom
      )
      .shadow(.drop(color: Color(qoraiSystemName: .primitiveBlurple5), radius: 16)),
      in: .rect(
        topLeadingRadius: 16,
        bottomLeadingRadius: 0,
        bottomTrailingRadius: 0,
        topTrailingRadius: 16,
        style: .continuous
      )
    )
    .dynamicTypeSize(DynamicTypeSize.xSmall..<DynamicTypeSize.accessibility1)
    .fixedSize(horizontal: false, vertical: true)
  }

  @ViewBuilder private var paywallActionContainerView: some View {
    if allowExternalPurchaseLinks {
      externalPurchasesAllowedActionView
    } else {
      standardPaywallActionView
    }
  }

  private func addPaymentForSubcription(type: QoraiVPNSubscriptionTier) {
    iapObserverManager.paymentStatus = .ongoing

    var subscriptionProduct: SKProduct?
    switch type {
    case .yearly:
      subscriptionProduct = QoraiVPNProductInfo.yearlySubProduct
    case .monthly:
      subscriptionProduct = QoraiVPNProductInfo.monthlySubProduct
    }

    guard let subscriptionProduct = subscriptionProduct else {
      Logger.module.error("Failed to retrieve \(type.rawValue) subcription product")
      iapObserverManager.paymentStatus = .failure(nil)
      return
    }

    let payment = SKPayment(product: subscriptionProduct)
    SKPaymentQueue.default().add(payment)
  }

  public func restorePurchase() {
    iapObserverManager.paymentStatus = .ongoing

    SKPaymentQueue.default().restoreCompletedTransactions()

    if iapRestoreTimer != nil {
      iapRestoreTimer?.cancel()
      iapRestoreTimer = nil
    }

    // Adding 30 seconds time-out for restore
    iapRestoreTimer = Task.delayed(bySeconds: 30.0) { @MainActor in
      try Task.checkCancellation()

      iapObserverManager.paymentStatus = .failure(nil)

      // Show Alert for failure of restore
      isShowingPurchaseAlert = true
    }
  }

  private func resetTheRestoreTimerIfNecessary() {
    if iapRestoreTimer != nil {
      iapRestoreTimer?.cancel()
      iapRestoreTimer = nil
    }
  }

  private func refreshCredential() {
    presentationMode.dismiss()
    openVPNAuthenticationInNewTab()
  }

  private func redeemPromoCode() {
    // Open the redeem code sheet
    SKPaymentQueue.default().presentCodeRedemptionSheet()
  }
}

#if DEBUG
#Preview("External Purchases") {
  QoraiVPNPaywallView(
    openVPNAuthenticationInNewTab: {},
    openDirectCheckoutInNewTab: {},
    openLearnMoreInNewTab: {},
    installVPNProfile: {}
  )
  .environment(\.allowExternalPurchaseLinks, true)
}
#Preview("Standard Purchases") {
  QoraiVPNPaywallView(
    openVPNAuthenticationInNewTab: {},
    openDirectCheckoutInNewTab: {},
    openLearnMoreInNewTab: {},
    installVPNProfile: {}
  )
  .environment(\.allowExternalPurchaseLinks, false)
}
#endif
