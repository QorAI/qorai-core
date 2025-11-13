// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation
import Shared
import UIKit
import Web

/// A helper class that aids in the creation of share sheets
class ShareExtensionHelper {
  /// URL and Tab to be shared
  private let selectedURL: URL
  private weak var selectedTab: (any TabState)?

  init(url: URL, tab: (any TabState)?) {
    self.selectedURL = url
    self.selectedTab = tab
  }

  /// Create a activity view controller with the given elements.
  /// - Parameters:
  ///   - selectedURL: The url or url content to share. May include an internal file or a link
  ///   - selectedTab: The provided tab is used for additional info such as a print renderer and title
  ///   - applicationActivities: The application activities to include in this share sheet.
  ///   - completionHandler: This will be triggered once the share sheet is dismissed and can be used to cleanup any lingering data
  /// - Returns: An `UIActivityViewController` prepped and ready to present.
  func createActivityViewController(
    applicationActivities: [UIActivity] = []
  ) -> UIActivityViewController {
    let printInfo = UIPrintInfo(dictionary: nil)
    printInfo.jobName = selectedURL.absoluteString
    printInfo.outputType = .general

    var activityItems: [Any] = [
      printInfo
    ]

    if let tab = selectedTab {
      // Adds the ability to "Print" or "Markup" the page using this custom renderer
      // Without this, the "Print" or "Markup feature would not exist"
      activityItems.append(TabPrintPageRenderer(tab: tab))
    }

    if let title = selectedTab?.title {
      // Makes sure the share sheet shows the same title as the tab
      // Also adds a title to several places, such as the Subject field in Mail
      activityItems.append(URLActivityItemProvider(title: title, url: selectedURL))
    } else {
      activityItems.append(selectedURL)
    }

    let activityViewController = UIActivityViewController(
      activityItems: activityItems,
      applicationActivities: applicationActivities
    )

    return activityViewController
  }
}

extension BasicMenuActivity.ActivityType {
  static let copyCleanLink: Self = .init(
    id: "CopyCleanLink",
    title: Strings.copyCleanLink,
    qoraiSystemImage: "qora.copy.clean"
  )
  static let sendURL: Self = .init(
    id: "SendURL",
    title: Strings.OpenTabs.sendWebsiteShareActionTitle,
    qoraiSystemImage: "qora.smartphone.laptop"
  )
  static let toggleReaderMode: Self = .init(
    id: "ToggleReaderMode",
    title: Strings.toggleReaderMode,
    qoraiSystemImage: "qora.product.speedreader"
  )
  static let translatePage: Self = .init(
    id: "TranslatePage",
    title: Strings.translatePage,
    qoraiSystemImage: "qora.product.translate"
  )
  static let findInPage: Self = .init(
    id: "FindInPage",
    title: Strings.findInPage,
    qoraiSystemImage: "qora.search"
  )
  static let pageZoom: Self = .init(
    id: "PageZoom",
    title: Strings.PageZoom.settingsTitle,
    qoraiSystemImage: "qora.font.size"
  )
  static let addFavourites: Self = .init(
    id: "AddFavourites",
    title: Strings.addToFavorites,
    qoraiSystemImage: "qora.widget.generic"
  )
  static let requestDesktopSite: Self = .init(
    id: "ToggleUserAgent",
    title: Strings.appMenuViewDesktopSiteTitleString,
    qoraiSystemImage: "qora.monitor"
  )
  static let addSourceNews: Self = .init(
    id: "AddSourceNews",
    title: Strings.QoraiNews.addSourceShareTitle,
    qoraiSystemImage: "qora.rss"
  )
  static let createPDF: Self = .init(
    id: "CreatePDF",
    title: Strings.createPDF,
    qoraiSystemImage: "qora.file.new"
  )
  static let addSearchEngine: Self = .init(
    id: "AddSearchEngine",
    title: Strings.CustomSearchEngine.customEngineNavigationTitle,
    qoraiSystemImage: "qora.search.zoom-in"
  )
  static let displaySecurityCertificate: Self = .init(
    id: "DisplaySecurityCertificate",
    title: Strings.displayCertificate,
    qoraiSystemImage: "qora.lock.plain"
  )
  static let reportBrokenSite: Self = .init(
    id: "ReportBrokenSite",
    title: Strings.Shields.reportABrokenSite,
    qoraiSystemImage: "qora.warning.triangle-outline"
  )
}
