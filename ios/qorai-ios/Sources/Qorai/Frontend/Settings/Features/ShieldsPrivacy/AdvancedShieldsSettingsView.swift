// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiNews
import QoraiUI
import Preferences
import Strings
import SwiftUI

struct AdvancedShieldsSettingsView: View {
  @ObservedObject private var settings: AdvancedShieldsSettings
  @State private var showManageWebsiteData = false

  var openURLAction: ((URL) -> Void)?

  init(settings: AdvancedShieldsSettings) {
    self.settings = settings
  }

  var body: some View {
    Form {
      DefaultShieldsSectionView(settings: settings)
      ClearDataSectionView(settings: settings)

      Section {
        Button {
          showManageWebsiteData = true
        } label: {
          // Hack to show the disclosure
          NavigationLink(
            destination: { EmptyView() },
            label: {
              LabelView(
                title: Strings.manageWebsiteDataTitle,
                subtitle: nil
              )
              .frame(maxWidth: .infinity, alignment: .leading)
              .contentShape(.rect)
            }
          )
        }
        .buttonStyle(.plain)
        .sheet(isPresented: $showManageWebsiteData) {
          ManageWebsiteDataView()
        }

        NavigationLink {
          PrivacyReportSettingsView()
        } label: {
          LabelView(
            title: Strings.PrivacyHub.privacyReportsTitle,
            subtitle: nil
          )
        }
      }.listRowBackground(Color(.secondaryQoraiGroupedBackground))

      OtherPrivacySettingsSectionView(settings: settings)
    }
    .scrollContentBackground(.hidden)
    .background(Color(UIColor.qoraiGroupedBackground))
    .listStyle(.insetGrouped)
    .navigationTitle(Strings.qoraiShieldsAndPrivacy)
    .environment(
      \.openURL,
      .init(handler: { [openURLAction] url in
        openURLAction?(url)
        return .handled
      })
    )
  }
}
