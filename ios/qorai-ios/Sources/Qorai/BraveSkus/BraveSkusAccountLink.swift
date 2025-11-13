// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

import AIChat
import QoraiStore
import Foundation
import Preferences
import Web
import WebKit
import os.log

extension QoraiStoreProduct {
  /// The key to use when storing the receipt in WebKit's LocalStorage
  var localStorageKey: String {
    switch self {
    case .vpnMonthly, .vpnYearly: return "qoraiVpn.receipt"
    case .qoraMonthly, .qoraYearly: return "qoraiQora.receipt"
    }
  }
}

/// A class for linking Product Purchases with a Qorai Account
class QoraiSkusAccountLink {
  /// An enum representing the Skus Environment
  private enum Environment: String, CaseIterable {
    /// The skus development environment
    case development

    /// The skus staging environment
    case staging

    /// The skus production environment
    case production

    /// The host/domain for the environment
    var host: String {
      switch self {
      case .development: return "account.qorai.software"
      case .staging: return "account.qoraisoftware.com"
      case .production: return "account.qorai.com"
      }
    }
  }

  @MainActor
  static func injectLocalStorage(tab: some TabState) async {
    if let vpnSubscriptionProductId = Preferences.VPN.subscriptionProductId.value,
      let product = QoraiStoreProduct(rawValue: vpnSubscriptionProductId)
    {
      await QoraiSkusAccountLink.injectLocalStorage(tab: tab, product: product)
    }

    if let aiChatSubscriptionProductId = Preferences.AIChat.subscriptionProductId.value,
      let product = QoraiStoreProduct(rawValue: aiChatSubscriptionProductId)
    {
      await QoraiSkusAccountLink.injectLocalStorage(tab: tab, product: product)
    }
  }

  /// Injects Skus product order receipt information into WebKit's LocalStorage for use by the `Environment.host` page
  /// - Parameter webView: The web-view whose LocalStorage to inject the product order information
  /// - Parameter product: The product whose receipt information to inject
  @MainActor
  @discardableResult private static func injectLocalStorage(
    tab: some TabState,
    product: QoraiStoreProduct
  ) async -> Bool {
    // The WebView has no URL so do nothing
    guard let url = tab.visibleURL else {
      return false
    }

    // The URL must have a scheme and host
    guard let components = URLComponents(url: url, resolvingAgainstBaseURL: false),
      let scheme = components.scheme,
      let host = components.host
    else {
      return false
    }

    // Validate the scheme and host is the correct page to inject sensitive purchase information
    // Purchase information must only be injected into a secure page and must only be injected into
    // one of the Qorai account pages as determined by `Environment.host`
    if scheme != "https" || !Environment.allCases.map({ $0.host }).contains(host) {
      return false
    }

    do {
      // Retrieve the LocalStorage Key and Receipt to inject
      let storageKey = product.localStorageKey
      let receipt = try QoraiSkusSDK.receipt(for: product)

      // Inject the receipt into LocalStorage
      try await tab.evaluateJavaScript(
        functionName: "localStorage.setItem",
        args: [storageKey, receipt],
        contentWorld: .defaultClient
      )

      // Qorai-Qora requires Order-ID to be injected into LocalStorage.
      if let orderId = Preferences.AIChat.subscriptionOrderId.value {
        try await tab.evaluateJavaScript(
          functionName: "localStorage.setItem",
          args: ["qoraiQora.orderId", orderId],
          contentWorld: .defaultClient
        )
      }

      return true
    } catch {
      Logger.module.error(
        "[QoraiSkusAccountLink] - Error Injecting SkusSDK receipt into LocalStorage: \(error)"
      )
    }

    return false
  }
}
