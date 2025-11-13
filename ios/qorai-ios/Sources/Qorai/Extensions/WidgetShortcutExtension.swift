// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiStrings
import QoraiWidgetsModels
import DesignSystem
import Foundation
import Strings
import UIKit

extension WidgetShortcut {
  static let eligibleButtonShortcuts: [WidgetShortcut] = [
    .bookmarks,
    .history,
    .downloads,
    .playlist,
    .wallet,
    .qoraiNews,
    .qoraiQora,
    .askQorai,
  ]

  var displayString: String {
    switch self {
    case .unknown:
      return ""
    case .bookmarks:
      return Strings.bookmarksMenuItem
    case .history:
      return Strings.historyMenuItem
    case .downloads:
      return Strings.downloadsMenuItem
    case .playlist:
      return Strings.qoraiPlaylistItemTitle
    case .wallet:
      return Strings.Wallet.wallet
    case .qoraiNews:
      return Strings.qoraiNewsItemTitle
    case .qoraiQora:
      return Strings.qoraMenuItem
    case .askQorai:
      return Strings.askQoraiMenuItem
    default:
      return ""
    }
  }

  var qoraiSystemImageName: String? {
    switch self {
    case .unknown:
      return nil
    case .newTab:
      return "qora.browser.mobile-tab-new"
    case .newPrivateTab:
      return "qora.product.private-window"
    case .bookmarks:
      return "qora.product.bookmarks"
    case .history:
      return "qora.history"
    case .downloads:
      return "qora.download"
    case .playlist:
      return "qora.product.playlist"
    case .search:
      return "qora.search"
    case .wallet:
      return "qora.product.qorai-wallet"
    case .scanQRCode:
      return "qora.qr.code"
    case .qoraiNews:
      return "qora.product.qorai-news"
    case .qoraiQora, .askQorai:
      return "qora.product.qorai-qora"
    @unknown default:
      return nil
    }
  }

  var image: UIImage? {
    return qoraiSystemImageName.flatMap { UIImage(qoraiSystemNamed: $0) }
  }
}
