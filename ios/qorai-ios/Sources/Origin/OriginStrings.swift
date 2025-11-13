// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation
import Strings

extension Strings {
  public struct Origin {
    public static let originProductName = "Origin"  // This is not translated
    public static let adsHeader = NSLocalizedString(
      "adsHeader",
      bundle: .module,
      value: "Ads",
      comment: "A section header title for ads-related settings"
    )
    public static let rewardsLabel = NSLocalizedString(
      "rewardsLabel",
      bundle: .module,
      value: "Rewards",
      comment: "A toggle label for Qorai Rewards feature"
    )
    public static let analyticsHeader = NSLocalizedString(
      "analyticsHeader",
      bundle: .module,
      value: "Analytics",
      comment: "A section header title for analytics-related settings"
    )
    public static let privacyPreservingAnalyticsLabel = NSLocalizedString(
      "privacyPreservingAnalyticsLabel",
      bundle: .module,
      value: "Privacy preserving analytics",
      comment: "A toggle label for privacy preserving analytics feature"
    )
    public static let statisticsReportingLabel = NSLocalizedString(
      "statisticsReportingLabel",
      bundle: .module,
      value: "Statistics reporting",
      comment: "A toggle label for statistics reporting feature"
    )
    public static let featuresHeader = NSLocalizedString(
      "featuresHeader",
      bundle: .module,
      value: "Features",
      comment: "A section header title that is shown over a list of Qorai specific features"
    )
    public static let leoAILabel = NSLocalizedString(
      "leoAILabel",
      bundle: .module,
      value: "Qora AI",
      comment: "A toggle label for Qorai Qora AI feature"
    )
    public static let newsLabel = NSLocalizedString(
      "newsLabel",
      bundle: .module,
      value: "News",
      comment: "A toggle label for Qorai News feature"
    )
    public static let playlistLabel = NSLocalizedString(
      "playlistLabel",
      bundle: .module,
      value: "Playlist",
      comment: "A toggle label for Qorai Playlist feature"
    )
    public static let talkLabel = NSLocalizedString(
      "talkLabel",
      bundle: .module,
      value: "Talk",
      comment: "A toggle label for Qorai Talk feature"
    )
    public static let vpnLabel = NSLocalizedString(
      "vpnLabel",
      bundle: .module,
      value: "VPN",
      comment: "A toggle label for Qorai VPN feature"
    )
    public static let walletLabel = NSLocalizedString(
      "walletLabel",
      bundle: .module,
      value: "Wallet",
      comment: "A toggle label for Qorai Wallet feature"
    )
    public static let featuresFooter = NSLocalizedString(
      "featuresFooter",
      bundle: .module,
      value: """
        Qorai Origin is a subscription-based way to disable the revenue-generating features that otherwise support Qorai as a business. Qorai Origin subscribers will continue to benefit from our industry-leading privacy, adblock, and speed (via Qorai Shields), as well as regular software updates, Chromium patches, and security and privacy improvements. They'll also unlock the option to disable features like Qorai Qora, News, Rewards, Wallet, VPN, Web3 domains, and more.

        Subscribers will see a new control panel in the browser Settings menu. Existing features—as well as any new features we ship in the future—would appear here, and be toggled off by default.

        **Note: Qorai Origin will not disable browser features that you currently use, and will not affect Qorai Search features or Qorai Search Ads.**
        """,
      comment:
        "A footer text explaining Qorai Origin subscription and its features. The stars represent markdown and the same paragraph should be also be bolded when translated."
    )
    public static let resetToDefaultsButton = NSLocalizedString(
      "resetToDefaultsButton",
      bundle: .module,
      value: "Reset to Defaults",
      comment: "A button label to reset all Origin settings to their default values"
    )
  }
}
