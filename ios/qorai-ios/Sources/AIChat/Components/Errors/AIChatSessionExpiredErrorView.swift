// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import DesignSystem
import SwiftUI

struct AIChatSessionExpiredErrorView: View {
  var refreshSession: () -> Void

  var body: some View {
    HStack(alignment: .top, spacing: 0.0) {
      Image(qoraiSystemName: "qora.warning.triangle-filled")
        .foregroundStyle(Color(qoraiSystemName: .systemfeedbackWarningIcon))
        .padding([.bottom, .trailing])

      VStack(alignment: .leading, spacing: 0.0) {
        Text(Strings.AIChat.accountSessionExpiredDescription)
          .font(.callout)
          .foregroundColor(Color(qoraiSystemName: .systemfeedbackWarningText))
          .padding(.bottom)

        Button(
          action: {
            refreshSession()
          },
          label: {
            Text(Strings.AIChat.refreshCredentialsActionTitle)
              .font(.headline)
              .padding()
              .foregroundStyle(Color(qoraiSystemName: .schemesOnPrimary))
              .background(Color(qoraiSystemName: .buttonBackground), in: .capsule)
          }
        )
        .buttonStyle(.plain)
      }
    }
    .padding()
    .background(Color(qoraiSystemName: .systemfeedbackWarningBackground))
    .clipShape(RoundedRectangle(cornerRadius: 8.0, style: .continuous))
  }
}

#if DEBUG
struct AIChatSessionExpiredErrorView_Preview: PreviewProvider {
  static var previews: some View {
    AIChatSessionExpiredErrorView {
      print("Refresh Credentials")
    }
    .previewColorSchemes()
    .previewLayout(.sizeThatFits)
  }
}
#endif
