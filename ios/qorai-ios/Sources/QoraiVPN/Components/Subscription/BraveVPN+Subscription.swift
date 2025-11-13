// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiStore
import GuardianConnect
import Preferences
import Shared

extension QoraiVPN {
  /// Type of the vpn subscription
  public enum SubscriptionType: Equatable {
    case monthly, yearly, other
  }

  /// Type of the active purchased vpn plan
  public static var activeSubscriptionType: SubscriptionType {
    guard let productId = Preferences.VPN.subscriptionProductId.value else {
      logAndStoreError("subscriptionName: failed to retrieve productId")
      return .other
    }

    switch productId {
    case QoraiStoreProduct.vpnMonthly.rawValue:
      return .monthly
    case QoraiStoreProduct.vpnYearly.rawValue:
      return .yearly
    default:
      return .other
    }
  }

  /// Name of the purchased vpn plan.
  public static var subscriptionName: String {
    guard let productId = Preferences.VPN.subscriptionProductId.value else {
      logAndStoreError("subscriptionName: failed to retrieve productId")
      return ""
    }

    switch productId {
    case QoraiStoreProduct.vpnMonthly.rawValue:
      return Strings.VPN.vpnSettingsMonthlySubName
    case QoraiStoreProduct.vpnYearly.rawValue:
      return Strings.VPN.vpnSettingsYearlySubName
    default:
      assertionFailure("Can't get product id")
      return ""
    }
  }
}
