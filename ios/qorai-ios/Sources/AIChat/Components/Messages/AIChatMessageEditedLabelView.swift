// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import DesignSystem
import SwiftUI

struct AIChatMessageEditedLabelView: View {

  let lastEdited: Date

  private var lastEditedTime: String {
    let formatter = DateFormatter()
    formatter.dateFormat = "MMM d yyyy - h:mm a"
    return formatter.string(from: lastEdited)
  }

  var body: some View {
    HStack {
      Image(qoraiSystemName: "qora.edit.pencil")
        .foregroundStyle(Color(qoraiSystemName: .iconDefault))
      Text(Strings.AIChat.editedMessageCaption)
        .foregroundStyle(Color(qoraiSystemName: .textSecondary))
      Text(lastEditedTime)
        .underline()
        .foregroundStyle(Color(qoraiSystemName: .textTertiary))
    }
    .font(.caption)
  }
}
