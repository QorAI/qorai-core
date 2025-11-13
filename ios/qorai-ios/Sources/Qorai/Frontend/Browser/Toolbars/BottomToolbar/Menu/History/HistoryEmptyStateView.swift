// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiStrings
import Foundation
import Preferences
import Strings
import SwiftUI

struct HistoryEmptyStateView: View {
  var isSearching: Bool

  var body: some View {
    VStack(spacing: 16) {
      Image(qoraiSystemName: "qora.history")
        .font(.title)
        .imageScale(.large)
        .foregroundStyle(Color(qoraiSystemName: .iconSecondary))
      VStack {
        Text(
          isSearching
            ? Strings.History.historyEmptySearchTitle : Strings.History.historyEmptyStateTitle
        )
        .font(.headline)
        .foregroundStyle(Color(qoraiSystemName: .textSecondary))
        if !isSearching {
          Text(
            Preferences.Privacy.privateBrowsingOnly.value
              ? Strings.History.historyPrivateModeOnlyStateSubtitle
              : Strings.History.historyEmptyStateSubtitle
          )
          .font(.subheadline)
          .foregroundStyle(Color(qoraiSystemName: .textTertiary))
        }
      }
    }
  }
}

#if DEBUG
#Preview {
  HistoryEmptyStateView(isSearching: false)
}
#endif
