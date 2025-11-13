// Copyright 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiShields
import Foundation
import Shared
import WebKit

enum DomainUserScript: CaseIterable {
  case qoraiSearchHelper
  case qoraiTalkHelper
  case qoraiSkus
  case qoraiPlaylistFolderSharingHelper

  /// Initialize this script with a URL
  init?(for url: URL) {
    // First we look for an exact domain match
    if let host = url.host,
      let found = Self.allCases.first(where: { $0.associatedDomains.contains(host) })
    {
      self = found
      return
    }

    // If no matches, we look for a baseDomain (eTLD+1) match.
    if let baseDomain = url.baseDomain,
      let found = Self.allCases.first(where: { $0.associatedDomains.contains(baseDomain) })
    {
      self = found
      return
    }

    return nil
  }

  /// The domains associated with this script.
  var associatedDomains: Set<String> {
    switch self {
    case .qoraiSearchHelper:
      return Set([
        "search.qorai.com", "search.qorai.software",
        "search.qoraisoftware.com", "safesearch.qorai.com",
        "safesearch.qorai.software", "safesearch.qoraisoftware.com",
        "search-dev-local.qorai.com",
      ])
    case .qoraiTalkHelper:
      return Set([
        "talk.qorai.com",
        "talk.qoraisoftware.com",
        "talk.qorai.software",
      ])
    case .qoraiPlaylistFolderSharingHelper:
      return Set(["playlist.qoraisoftware.com", "playlist.qorai.com"])
    case .qoraiSkus:
      return Set([
        "account.qorai.com",
        "account.qoraisoftware.com",
        "account.qorai.software",
      ])
    }
  }
}
