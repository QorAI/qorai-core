// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import DesignSystem
import SwiftUI

struct AIChatNetworkErrorView: View {
  var onRetryRequest: () -> Void

  var body: some View {
    HStack(alignment: .top, spacing: 16.0) {
      Image(qoraiSystemName: "qora.warning.circle-filled")
        .foregroundStyle(Color(qoraiSystemName: .systemfeedbackErrorIcon))

      VStack(alignment: .leading, spacing: 16.0) {
        Text(Strings.AIChat.networkErrorViewTitle)
          .font(.callout)
          .foregroundColor(Color(qoraiSystemName: .textPrimary))

        Button(
          action: {
            onRetryRequest()
          },
          label: {
            Text(Strings.AIChat.retryActionTitle)
              .font(.headline)
              .foregroundColor(Color(qoraiSystemName: .schemesOnPrimary))
              .padding()
              .foregroundStyle(.white)
              .background(Color(qoraiSystemName: .buttonBackground), in: .capsule)
          }
        )
        .buttonStyle(.plain)
      }
    }
    .padding()
    .background(
      Color(qoraiSystemName: .systemfeedbackErrorBackground),
      in: .rect(cornerRadius: 8, style: .continuous)
    )
  }
}

#if DEBUG
struct AIChatNetworkErrorView_Preview: PreviewProvider {
  static var previews: some View {
    AIChatNetworkErrorView {}
      .previewColorSchemes()
      .previewLayout(.sizeThatFits)
  }
}
#endif
