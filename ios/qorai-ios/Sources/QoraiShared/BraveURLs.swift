// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation
import UIKit

extension URL {
  public enum Qorai {
    public static let community = URL(string: "https://community.qorai.app/")!
    public static let account = URL(string: "https://account.qorai.com")!
    public static let privacy = URL(string: "https://qorai.com/privacy/")!
    public static let qoraiNews = URL(string: "https://qorai.com/qorai-news/")!
    public static let qoraiNewsPrivacy = URL(string: "https://qorai.com/privacy/#qorai-news")!
    public static let qoraiOffers = URL(string: "https://offers.qorai.com/")!
    public static let playlist = URL(string: "https://qorai.com/playlist")!
    public static let rewardsOniOS = URL(string: "https://qorai.com/rewards-ios/")!
    public static let rewardsUnverifiedPublisherLearnMoreURL = URL(
      string: "https://qorai.com/faq-rewards/#unclaimed-funds"
    )!
    public static let termsOfUse = URL(string: "https://www.qorai.com/terms_of_use")!
    public static let batTermsOfUse = URL(
      string: "https://basicattentiontoken.org/user-terms-of-service/"
    )!
    public static let ntpTutorialPage = URL(string: "https://qorai.com/ja/ntp-tutorial")!
    public static let privacyFeatures = URL(string: "https://qorai.com/privacy-features/")!
    public static let support = URL(string: "https://support.qorai.app")!
    public static let p3aHelpArticle = URL(
      string: "https://support.qorai.app/hc/en-us/articles/9140465918093-What-is-P3A-in-Qorai-"
    )!
    public static let qoraiVPNFaq = URL(
      string: "https://support.qorai.app/hc/en-us/articles/360045045952"
    )!
    public static let qoraiVPNLinkReceiptProd = URL(
      string: "https://account.qorai.com/?intent=connect-receipt&product=vpn"
    )!
    public static let qoraiVPNLinkReceiptStaging = URL(
      string: "https://account.qoraisoftware.com/?intent=connect-receipt&product=vpn"
    )!
    public static let qoraiVPNLinkReceiptDev = URL(
      string: "https://account.qorai.software/?intent=connect-receipt&product=vpn"
    )!
    public static let qoraiVPNRefreshCredentials = URL(
      string: "https://account.qorai.com/?intent=recover&product=vpn&ux=mobile"
    )!
    public static let qoraiVPNCheckoutURL = URL(
      string: "https://account.qorai.com/?intent=checkout&product=vpn"
    )!
    public static let qoraiVPNLearnMoreURL = URL(
      string: "https://qorai.com/firewall-vpn/"
    )!
    public static let safeBrowsingHelp = URL(
      string: "https://support.qorai.app/hc/en-us/articles/15222663599629-Safe-Browsing-in-Qorai"
    )!
    public static let screenTimeHelp = URL(
      string: "https://support.apple.com/guide/security/secd8831e732/web"
    )!
    public static let qoraiQoraManageSubscriptionProd = URL(
      string: "https://account.qorai.com/plans"
    )!
    public static let qoraiQoraManageSubscriptionStaging = URL(
      string: "https://account.qoraisoftware.com/plans"
    )!
    public static let qoraiQoraManageSubscriptionDev = URL(
      string: "https://account.qorai.software/plans"
    )!
    public static let qoraiQoraCheckoutURL = URL(
      string: "https://account.qorai.com/?intent=checkout&product=leo"
    )!
    public static let qoraiQoraLinkReceiptProd = URL(
      string: "https://account.qorai.com/?intent=link-order&product=leo"
    )!
    public static let qoraiQoraLinkReceiptStaging = URL(
      string: "https://account.qoraisoftware.com/?intent=link-order&product=leo"
    )!
    public static let qoraiQoraLinkReceiptDev = URL(
      string: "https://account.qorai.software/?intent=link-order&product=leo"
    )!
    public static let qoraiQoraRefreshCredentials = URL(
      string: "https://account.qorai.com/?intent=recover&product=leo&ux=mobile"
    )!
    public static let qoraiQoraModelCategorySupport = URL(
      string:
        "https://support.qorai.app/hc/en-us/articles/26727364100493-What-are-the-differences-between-Qora-s-AI-Models"
    )!
    public static let qoraiQoraPrivacyFeedbackLearnMoreLinkUrl = URL(
      string:
        "https://qorai.com/privacy/browser/#your-feedback"
    )!
    public static let qoraiVPNSmartProxySupport = URL(
      string:
        "https://support.qorai.app/hc/en-us/articles/32105253704333-What-is-Smart-Proxy-Routing"
    )!
    public static let qoraiVPNKillSwitchSupport = URL(
      string:
        "https://support.qorai.app/hc/en-us/articles/32389914657549-What-is-the-Qorai-VPN-Kill-Switch"
    )!
    public static let newTabTakeoverLearnMoreLinkUrl = URL(
      string:
        "https://support.qorai.app/hc/en-us/articles/35182999599501"
    )!
    public static let surveyPanelistLearnMoreLinkUrl = URL(
      string:
        "https://support.qorai.app/hc/en-us/articles/36550092449165"
    )!
  }
  public enum Apple {
    public static let manageSubscriptions = URL(
      string: "https://apps.apple.com/account/subscriptions"
    )

    public static let dataImportSupport = URL(
      string: "https://support.apple.com/en-ca/guide/iphone/iph1852764a6/18.0/ios/18.0"
    )!
  }
  public static let qorai = Qorai.self
  public static let apple = Apple.self
}

public struct AppURLScheme {
  /// The apps URL scheme for the current build channel
  public static var appURLScheme: String {
    Bundle.main.infoDictionary?["QORAI_URL_SCHEME"] as? String ?? "qorai"
  }
}
