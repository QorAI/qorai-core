// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import DesignSystem
import SwiftUI

struct AIChatContextLimitErrorView: View {
  var newChatStarted: () -> Void

  var body: some View {
    HStack(alignment: .top, spacing: 0.0) {
      Image(qoraiSystemName: "qora.warning.circle-filled")
        .foregroundStyle(Color(qoraiSystemName: .systemfeedbackErrorIcon))
        .padding([.bottom, .trailing])

      VStack(alignment: .leading, spacing: 0.0) {
        Text(Strings.AIChat.contextLimitErrorTitle)
          .font(.callout)
          .foregroundColor(Color(qoraiSystemName: .textPrimary))
          .padding(.bottom)

        Button(
          action: {
            newChatStarted()
          },
          label: {
            Text(Strings.AIChat.newChatActionTitle)
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
    .background(Color(qoraiSystemName: .systemfeedbackErrorBackground))
    .clipShape(RoundedRectangle(cornerRadius: 8.0, style: .continuous))
  }
}

#if DEBUG
struct AIChatContextLimitErrorView_Preview: PreviewProvider {
  static var previews: some View {
    AIChatContextLimitErrorView {
      print("New Chat")
    }
    .previewColorSchemes()
    .previewLayout(.sizeThatFits)
  }
}
#endif
