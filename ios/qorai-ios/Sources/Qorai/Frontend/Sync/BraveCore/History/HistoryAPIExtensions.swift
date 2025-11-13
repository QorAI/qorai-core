// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiShared
import CoreData
import Data
import Foundation
import ScreenTime
import Shared

extension QoraiHistoryAPI {

  // MARK: Internal

  func add(url: URL, title: String, dateAdded: Date) {
    let historyNode = HistoryNode(url: url, title: title, dateAdded: dateAdded)
    addHistory(historyNode)
  }

  func byFrequency(
    query: String,
    completion: @escaping ([HistoryNode]) -> Void
  ) -> HistoryCancellable? {
    if query.isEmpty {
      return nil
    }

    let options = HistorySearchOptions(
      maxCount: 200,
      duplicateHandling: .removeAll
    )

    return search(
      withQuery: query,
      options: options,
      completion: completion
    )
  }

  func update(_ historyNode: HistoryNode, customTitle: String?, dateAdded: Date?) {
    if let title = customTitle {
      historyNode.title = title
    }

    if let date = dateAdded {
      historyNode.dateAdded = date
    }
  }

  func deleteAll(completion: @escaping () -> Void) {
    var screenTimeHistory: STWebHistory?
    do {
      screenTimeHistory = try STWebHistory(bundleIdentifier: Bundle.main.bundleIdentifier!)
    } catch {
      assertionFailure("STWebHistory could not be initialized: \(error)")
    }

    DispatchQueue.main.async {
      self.removeAll {
        Domain.deleteNonBookmarkedAndClearSiteVisits {
          screenTimeHistory?.deleteAllHistory()
          completion()
        }
      }
    }
  }
}
