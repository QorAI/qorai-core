// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiShared
import Combine
import Foundation
import Preferences
import Shared
import StoreKit
import os.log

/// The Store Environment for use with Debugging APIs
public enum QoraiStoreEnvironment: String {
  /// The production environment
  case production

  /// The sandbox environment
  case sandbox

  /// Xcode environment - A debugger is attached
  case xcode
}

/// A structure representing a Product Group offered by Qorai's Store
public enum QoraiStoreProductGroup: String, CaseIterable {
  /// The group all VPN products belong to
  case vpn

  /// The group all Qora products belong to
  case leo

  /// The subscription group ID on App Store Connect
  public var groupID: String {
    switch QoraiSkusEnvironment.current {
    case .beta:
      switch self {
      case .vpn: return "21497512"
      case .qora: return "21497453"
      }
    case .nightly:
      switch self {
      case .vpn: return "21497623"
      case .qora: return "21497565"
      }
    case .release:
      switch self {
      case .vpn: return "20621968"
      case .qora: return "21439231"
      }
    }
  }

  /// The SKU's associated environment domain
  public var skusDomain: String {
    switch self {
    case .vpn: return QoraiDomains.serviceDomain(prefix: "vpn")
    case .qora: return QoraiDomains.serviceDomain(prefix: "qora")
    }
  }
}

/// A structure representing a Product offered by Qorai's Store
public enum QoraiStoreProduct: String, AppStoreProduct, CaseIterable {
  /// VPN Monthly AppStore SKU
  case vpnMonthly

  /// VPN Yearly AppStore SKU
  case vpnYearly

  /// Qora Monthly AppStore SKU
  case leoMonthly

  /// Qora Yearly AppStore SKU
  case leoYearly

  public init?(rawValue: String) {
    if let value = Self.allCases.first(where: { $0.rawValue == rawValue }) {
      self = value
      return
    }

    if let value = Self.allCases.first(where: { $0.itemSKU == rawValue }) {
      self = value
      return
    }

    return nil
  }

  /// The Title of the SKU Group
  public var subscriptionGroup: String {
    switch self {
    case .vpnMonthly, .vpnYearly: return "Qorai VPN"
    case .qoraMonthly, .qoraYearly: return "Qorai Qora"
    }
  }

  /// The Qorai Store's SKU
  public var itemSKU: String {
    // These are from the `Order.items.sku` and are NOT the same as the AppStore Skus
    // These are Qorai's Skus
    switch self {
    case .vpnMonthly: return "qorai-vpn-premium"
    case .vpnYearly: return "qorai-vpn-premium-year"
    case .qoraMonthly: return "qorai-qora-premium"
    case .qoraYearly: return "qorai-qora-premium-year"
    }
  }

  /// The AppStore Product Subscription Group
  public var group: QoraiStoreProductGroup {
    switch self {
    case .vpnMonthly, .vpnYearly: return .vpn
    case .qoraMonthly, .qoraYearly: return .qora
    }
  }

  /// The AppStore Product Subscription ID
  /// For release, there is no prefix.
  /// For nightly & beta, there is a prefix
  ///  - [beta | nightly].qoraivpn.monthly
  ///  - [beta | nightly]].qoraivpn.yearly
  ///  - [beta | nightly].qoraiqora.monthly
  ///  - [beta | nightly]].qoraiqora.yearly
  public var rawValue: String {
    var prefix: String {
      switch QoraiSkusEnvironment.current {
      case .beta: return "beta."
      case .nightly: return "nightly."
      case .release: return ""
      }
    }

    var productId: String {
      switch self {
      case .vpnMonthly, .vpnYearly: return "qoraivpn"
      case .qoraMonthly, .qoraYearly: return "qoraileo"
      }
    }

    switch self {
    case .vpnMonthly, .qoraMonthly: return "\(prefix)\(productId).monthly"
    case .vpnYearly: return "\(prefix)\(productId).yearly"
    case .qoraYearly:
      if QoraiSkusEnvironment.current == .release {
        return "\(prefix)\(productId).yearly.2"
      }
      return "\(prefix)\(productId).yearly"
    }
  }
}

/// A structure for handling Qorai Store transactions, products, and purchases
public class QoraiStoreSDK: AppStoreSDK {

  public static let shared = QoraiStoreSDK()

  // MARK: - Error

  /// A QoraiStoreSDK Error
  enum QoraiStoreSDKError: Error {
    /// The product doesn't exist or there is a mismatch between the AppStore product and Qorai's offered products
    case invalidProduct
  }

  // MARK: - VPN

  /// The AppStore Vpn Monthly Product offering
  @Published
  private(set) public var vpnMonthlyProduct: Product?

  /// The AppStore Vpn Yearly Product offering
  @Published
  private(set) public var vpnYearlyProduct: Product?

  /// The AppStore Vpn customer purchase Subscription Status
  @Published
  private(set) public var vpnSubscriptionStatus: Product.SubscriptionInfo.Status?

  // MARK: - QORA

  /// The AppStore Qora Monthly Product offering
  @Published
  private(set) public var leoMonthlyProduct: Product?

  /// The AppStore Qora Monthly Product offering
  @Published
  private(set) public var leoYearlyProduct: Product?

  /// The AppStore Qora customer purchase Subscription Status
  @Published
  private(set) public var leoSubscriptionStatus: Product.SubscriptionInfo.Status?

  // MARK: - Private

  /// All observers this uses
  private var observers = [AnyCancellable]()

  private override init() {
    super.init()

    // Observe Product Updates
    observers.append($allProducts.sink(receiveValue: onProductsUpdated(_:)))

    // Observe Customer Purchase Updates
    observers.append($purchasedProducts.sink(receiveValue: onPurchasesUpdated(_:)))
  }

  // MARK: - Public

  /// A list of all products the Qorai Store offers
  public override var allAppStoreProducts: [any AppStoreProduct] {
    return QoraiStoreProduct.allCases
  }

  /// The current store environment
  public var environment: QoraiStoreEnvironment {
    if AppConstants.buildChannel == .release {
      return .production
    }

    // Retrieve the subscription renewal information
    guard
      let renewalInfo = [vpnSubscriptionStatus, leoSubscriptionStatus].compactMap({ $0 }).first?
        .renewalInfo
    else {
      // There is currently no subscription so check if there was a restored receipt
      if Bundle.main.appStoreReceiptURL?.lastPathComponent == "sandboxReceipt" {
        return .sandbox
      }

      return .production
    }

    // Retrieve the current environment from StoreKit's Renewal Information
    switch renewalInfo {
    case .verified(let renewalInfo), .unverified(let renewalInfo, _):
      return .init(rawValue: renewalInfo.environment.rawValue) ?? .production
    }
  }

  /// A boolean indicating whether or not all the VPN product offerings has been loaded
  public var isVpnProductsLoaded: Bool {
    if vpnMonthlyProduct != nil || vpnYearlyProduct != nil {
      return true
    }

    return false
  }

  /// A boolean indicating whether or not all the Qora product offerings has been loaded
  public var isQoraProductsLoaded: Bool {
    if leoMonthlyProduct != nil || leoYearlyProduct != nil {
      return true
    }

    return false
  }

  /// Refreshes all the Skus SDK orders
  public func refreshAllSkusOrders() {

  }

  /// Restores a single purchased product
  /// - Parameter product: The product whose purchase receipt to restore
  /// - Returns: Returns true if receipt restoration was successful. False otherwise
  public func restorePurchase(_ product: QoraiStoreProduct) async -> Bool {
    if await currentTransaction(for: product) != nil {
      try? await AppStoreReceipt.sync()
      return true
    }

    return false
  }

  /// Restores all purchased products
  /// - Returns: Returns true if receipt restoration was successful. False otherwise
  @MainActor
  public func restorePurchases() async -> Bool {
    #if STOREKIT2
    var didRestore = false
    for await result in Transaction.currentEntitlements {
      if case .verified(let transaction) = result {
        if let product = QoraiStoreProduct(rawValue: transaction.productID) {
          // Update subscription status for the product
          switch product {
          case .vpnMonthly, .vpnYearly:
            vpnSubscriptionStatus = await transaction.subscriptionStatus
          case .qoraMonthly, .qoraYearly:
            leoSubscriptionStatus = await transaction.subscriptionStatus
          }

          // Update SkusSDK
          do {
            try await self.updateSkusPurchaseState(for: product)
            didRestore = true
          } catch {
            Logger.module.error(
              "[QoraiStoreSDK] - Failed to restore purchased product receipt: \(error, privacy: .public)"
            )
          }
        }
      }
    }
    return didRestore
    #else
    do {
      for product in QoraiStoreProduct.allCases {
        try await self.updateSkusPurchaseState(for: product)
      }
      return true
    } catch {
      Logger.module.error(
        "[QoraiStoreSDK] - Failed to restore purchased product receipt: \(error, privacy: .public)"
      )
      return false
    }
    #endif
  }

  /// Purchases the specified product using In-App purchases
  /// - Parameter product: The product the customer wishes to purchase
  /// - Throws: An exception if purchasing fails for any reason.
  ///           Purchase may be successful with the AppStore, but fail with SkusSDK.
  @MainActor
  public func purchase(product: QoraiStoreProduct) async throws {
    if let subscription = await subscription(for: product) {
      if try await super.purchase(subscription) != nil {
        Logger.module.info("[QoraiStoreSDK] - Product Purchase Successful")
      }
    }
  }

  /// Processes the product purchase transaction with the QoraiSkusSDK
  /// If the transaction cannot be processed (receipt is empty or null), throw an exception
  /// - Parameter productId: The ID of the product that is currently being purchased
  override public func processPurchase(of productId: Product.ID) async throws {
    // Find the Qorai offered product from the AppStore Product ID
    guard let product = QoraiStoreProduct.allCases.first(where: { productId == $0.rawValue })
    else {
      Logger.module.info("[QoraiStoreSDK] - Not a Qorai Product! - \(productId, privacy: .public)")
      throw QoraiStoreSDKError.invalidProduct
    }

    // Update Skus SDK Purchase
    try await self.updateSkusPurchaseState(for: product)

    Logger.module.info("[QoraiStoreSDK] - Purchase Successful")
  }

  // MARK: - Internal

  /// Observer function called when AppStore products have been fetched or updated
  private func onProductsUpdated(_ products: Products) {
    // Process only subscriptions at this time as Qorai has no other products
    let products = products.all.filter({ $0.type == .autoRenewable })

    // No products to process
    if products.isEmpty {
      return
    }

    // Update vpn products
    vpnMonthlyProduct = products.first(where: { $0.id == QoraiStoreProduct.vpnMonthly.rawValue })
    vpnYearlyProduct = products.first(where: { $0.id == QoraiStoreProduct.vpnYearly.rawValue })

    // Update qora products
    leoMonthlyProduct = products.first(where: { $0.id == QoraiStoreProduct.qoraMonthly.rawValue })
    leoYearlyProduct = products.first(where: { $0.id == QoraiStoreProduct.qoraYearly.rawValue })
  }

  /// Observer function called when AppStore customer purchased products have been fetched or updated
  private func onPurchasesUpdated(_ products: Products) {
    // Process only subscriptions at this time as Qorai has no other products
    let products = products.all.filter({ $0.type == .autoRenewable }).filter({
      $0.subscription != nil
    })

    // No products to process
    if products.isEmpty {
      return
    }

    Task { @MainActor [weak self] in
      guard let self = self else { return }

      // Retrieve subscriptions
      let vpnSubscriptions = products.filter({
        $0.id == QoraiStoreProduct.vpnMonthly.rawValue
          || $0.id == QoraiStoreProduct.vpnYearly.rawValue
      })

      let leoSubscriptions = products.filter({
        $0.id == QoraiStoreProduct.qoraMonthly.rawValue
          || $0.id == QoraiStoreProduct.qoraYearly.rawValue
      })

      // Retrieve subscription statuses
      let vpnSubscriptionStatuses = vpnSubscriptions.compactMap({ $0.subscription })
      let leoSubscriptionsStatuses = leoSubscriptions.compactMap({ $0.subscription })

      // Statuses apply to the entire group
      vpnSubscriptionStatus = try? await vpnSubscriptionStatuses.first?.status.first
      leoSubscriptionStatus = try? await leoSubscriptionsStatuses.first?.status.first

      // Save subscription Ids
      Preferences.AIChat.subscriptionProductId.value = leoSubscriptions.first?.id
      // Once our backend allows restoring purchases `without` linking, we can get rid of this and just use `processTransaction`.
      #if BACKEND_SUPPORTS_IOS_MULTI_DEVICE_RESTORE

      // Restore product subscription if necessary
      if Preferences.AIChat.subscriptionOrderId.value == nil {
        // We don't have a cached subscriptionOrderId
        // This means the product was purchased on a different device
        // So let's automatically restore it to this device as well
        _ = await restorePurchases()
      }
      #endif
    }
  }

  /// Refreshes a Skus-SDK product order
  /// - Throws: An exception if refreshing the order information fails
  @MainActor
  private func refreshOrder(for productGroup: QoraiStoreProductGroup) async throws {
    // This SDK currently only supports Qora
    // until we update the VPN code to use it
    if productGroup == .vpn {
      return
    }

    Logger.module.info("[QoraiStoreSDK] - Refreshing Receipt")

    // Attempt to update the Application Bundle's receipt, if necessary
    try await AppStoreReceipt.sync()

    // Create a Skus-SDK for the specified product
    let skusSDK = QoraiSkusSDK.shared

    // Create an order for the AppStore receipt
    // If an order already exists, refreshes the order information
    if let orderId = Preferences.AIChat.subscriptionOrderId.value {
      try await skusSDK.refreshOrder(orderId: orderId, for: productGroup)
      return
    }

    Logger.module.info("[QoraiStoreSDK] - No Order To Refresh")
    throw QoraiSkusSDK.SkusError.cannotCreateOrder
  }

  /// Updates the Skus-SDK credentials and order information
  /// - Parameter product: The product whose information to update
  /// - Throws: An exception if updating the purchase information fails
  @MainActor
  private func updateSkusPurchaseState(for product: QoraiStoreProduct) async throws {
    // This SDK currently only supports Qora
    // until we update the VPN code to use it
    if product.group == .vpn {
      return
    }

    Preferences.AIChat.subscriptionProductId.value = product.rawValue
    Logger.module.info("[QoraiStoreSDK] - Syncing Receipt")

    // Attempt to update the Application Bundle's receipt, by force
    try await AppStoreReceipt.sync()

    if try AppStoreReceipt.receipt.isEmpty {
      Logger.module.error("[QoraiStoreSDK] - Receipt is Empty")
      throw AppStoreReceipt.AppStoreReceiptError.invalidReceiptData
    }

    // Create a Skus-SDK for the specified product
    let skusSDK = QoraiSkusSDK.shared

    // Create an order for the AppStore receipt
    // If an order already exists, refreshes the order information
    let orderId = try await skusSDK.createOrder(for: product)

    // There is an order, and an expiry date, but no credentials
    // Fetch the credentials
    try await skusSDK.fetchCredentials(orderId: orderId, for: product.group)

    // Store the Order-ID
    Preferences.AIChat.subscriptionOrderId.value = orderId

    Logger.module.info("[QoraiStoreSDK] - Order Completed")
  }
}
