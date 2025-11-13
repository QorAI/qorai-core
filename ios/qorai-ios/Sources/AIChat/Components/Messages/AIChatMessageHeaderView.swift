// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import DesignSystem
import SwiftUI

struct AIChatMessageHeaderView: View {

  let isUser: Bool
  let isEdited: Bool

  var body: some View {
    HStack {
      if isUser {
        Image(qoraiSystemName: "qora.user.circle")
          .renderingMode(.template)
          .foregroundStyle(Color(qoraiSystemName: .iconDefault))
          .padding(8.0)
          .background(Color(qoraiSystemName: .containerHighlight), in: Circle())

        Text(Strings.AIChat.youMessageTitle)
          .font(.headline)
          .foregroundStyle(Color(qoraiSystemName: .textTertiary))
      } else {
        AIChatProductIcon(containerShape: Circle(), padding: 6.0)
          .font(.callout)

        Text(Strings.AIChat.qoraAssistantNameTitle)
          .font(.headline)
          .foregroundStyle(Color(qoraiSystemName: .textTertiary))
      }

      if isEdited {
        Spacer()

        AIChatEditedBadgeView()
      }
    }
  }
}
