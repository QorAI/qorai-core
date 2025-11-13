// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiShared
import Data
import Shared
import SwiftUI

extension PrivacyReportsView {
  struct PrivacyHubVPNAlertsSection: View {
    @Environment(\.pixelLength) private var pixelLength

    let lastVPNAlerts: [QoraiVPNAlert]

    private(set) var onDismiss: () -> Void

    var body: some View {
      VStack(alignment: .leading) {
        Text(Strings.PrivacyHub.vpnAlertsHeader.uppercased())
          .font(.footnote.weight(.medium))
          .fixedSize(horizontal: false, vertical: true)

        ForEach(lastVPNAlerts) { alert in
          VPNAlertCell(vpnAlert: alert)
            .background(Color(.qoraiBackground))
            .clipShape(RoundedRectangle(cornerRadius: 12, style: .continuous))
        }

        NavigationLink(
          destination:
            AllVPNAlertsView(onDismiss: onDismiss)
        ) {
          HStack {
            Text(Strings.PrivacyHub.allVPNAlertsButtonText)
            Image(systemName: "arrow.right")
          }
          .frame(maxWidth: .infinity)
        }
        .padding(.vertical, 12)
        .frame(maxWidth: .infinity)
        .foregroundColor(Color(.qoraiLabel))
        .overlay(
          RoundedRectangle(cornerRadius: 25)
            .stroke(Color(.qoraiLabel), lineWidth: pixelLength)
        )
      }
    }
  }
}

#if DEBUG
struct PrivacyHubVPNAlertsSection_Previews: PreviewProvider {
  static var previews: some View {
    PrivacyReportsView.PrivacyHubVPNAlertsSection(lastVPNAlerts: [], onDismiss: {})
  }
}
#endif
