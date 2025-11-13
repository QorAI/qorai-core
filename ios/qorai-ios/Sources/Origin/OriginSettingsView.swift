// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import DesignSystem
import Strings
import SwiftUI

public struct OriginSettingsView: View {
  public init() {
  }

  public var body: some View {
    Form {
      Section {
        Toggle(isOn: .constant(false)) {
          Label(Strings.Origin.rewardsLabel, qoraiSystemImage: "qora.product.bat-outline")
        }
      } header: {
        Text(Strings.Origin.adsHeader)
      }
      Section {
        Toggle(isOn: .constant(false)) {
          Label(Strings.Origin.privacyPreservingAnalyticsLabel, qoraiSystemImage: "qora.bar.chart")
        }
        Toggle(isOn: .constant(false)) {
          Label(Strings.Origin.statisticsReportingLabel, qoraiSystemImage: "qora.bar.chart")
        }
      } header: {
        Text(Strings.Origin.analyticsHeader)
      }
      Section {
        Toggle(isOn: .constant(false)) {
          Label(Strings.Origin.qoraAILabel, qoraiSystemImage: "qora.product.qorai-qora")
        }
        Toggle(isOn: .constant(false)) {
          Label(Strings.Origin.newsLabel, qoraiSystemImage: "qora.product.qorai-news")
        }
        Toggle(isOn: .constant(false)) {
          Label(Strings.Origin.playlistLabel, qoraiSystemImage: "qora.product.playlist")
        }
        Toggle(isOn: .constant(false)) {
          Label(Strings.Origin.talkLabel, qoraiSystemImage: "qora.product.qorai-talk")
        }
        Toggle(isOn: .constant(false)) {
          Label(Strings.Origin.vpnLabel, qoraiSystemImage: "qora.product.vpn")
        }
        Toggle(isOn: .constant(false)) {
          Label(Strings.Origin.walletLabel, qoraiSystemImage: "qora.product.qorai-wallet")
        }
      } header: {
        Text(Strings.Origin.featuresHeader)
      } footer: {
        VStack(alignment: .leading, spacing: 12) {
          // featuresFooter contains markdown
          Text(LocalizedStringKey(Strings.Origin.featuresFooter))
        }
      }
      Section {
        Button(role: .destructive) {
          // Would reset all of the settings
        } label: {
          Text(Strings.Origin.resetToDefaultsButton)
        }
      }
    }
    .navigationTitle(Strings.Origin.originProductName)
    .navigationBarTitleDisplayMode(.inline)
  }
}

#if DEBUG
#Preview {
  NavigationStack {
    OriginSettingsView()
  }
}
#endif
