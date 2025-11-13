// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiUI
import SwiftUI
import WebKit

struct QoraiSearchDebugMenu: View {

  @ObservedObject var logging: QoraiSearchLogEntry

  @State private var cookies: [HTTPCookie] = []
  @State private var storageTypes: [String] = []

  var body: some View {
    Form {
      Section {
        Toggle("Enable callback logging", isOn: $logging.isEnabled)
          .toggleStyle(SwitchToggleStyle(tint: .accentColor))
      }

      Section(header: Text(verbatim: "Logs")) {
        ForEach(logging.logs) { logEntry in
          NavigationLink(destination: QoraiSearchDebugMenuDetail(logEntry: logEntry)) {
            VStack(alignment: .leading) {
              Text(formattedDate(logEntry.date))
                .font(.caption)
              Text(logEntry.query)
                .font(.body)
            }
          }
        }
      }

      Section(header: Text(verbatim: "cookies")) {
        ForEach(cookies, id: \.name) { cookie in
          Text(String(describing: cookie))
        }
      }

      Section(header: Text(verbatim: "storage found for qorai.com")) {
        Text(String(describing: storageTypes))
      }
    }
    .listBackgroundColor(Color(UIColor.qoraiGroupedBackground))
    .onAppear(perform: loadRecords)
  }

  private func formattedDate(_ date: Date) -> String {
    let dateFormatter = DateFormatter()
    dateFormatter.dateStyle = .short
    dateFormatter.timeStyle = .short
    return dateFormatter.string(from: date)
  }

  private func loadRecords() {
    let eligibleDomains =
      [
        "search.qorai.com", "search.qorai.software", "search.qoraisoftware.com",
        "safesearch.qorai.com", "safesearch.qorai.software",
        "safesearch.qoraisoftware.com", "search-dev-local.qorai.com",
      ]
    WKWebsiteDataStore.default().httpCookieStore.getAllCookies { cookies in
      self.cookies = cookies.filter {
        eligibleDomains.contains($0.domain)
      }

    }

    let eligibleStorageDomains =
      ["qorai.com", "qoraisoftware.com", "qorai.software"]
    WKWebsiteDataStore.default()
      .fetchDataRecords(
        ofTypes: WKWebsiteDataStore.allWebsiteDataTypes(),
        completionHandler: { records in
          storageTypes =
            records
            .filter { eligibleStorageDomains.contains($0.displayName) }
            .flatMap { $0.dataTypes }
        }
      )
  }
}

#if DEBUG
struct QoraiSearchDebugMenu_Previews: PreviewProvider {
  static var previews: some View {
    QoraiSearchDebugMenu(logging: QoraiSearchDebugMenuFixture.loggingSample)
  }
}
#endif
