// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import DesignSystem
import Strings
import SwiftUI

/// List header for displaying text with `...` menu to copy address.
struct CopyAddressHeader: View {

  let displayText: String
  let address: String

  init(
    displayText: String,
    address: String
  ) {
    self.displayText = displayText
    self.address = address
  }

  var body: some View {
    HStack {
      Text(displayText)
      Spacer()
      if !address.isEmpty {
        addressMenu(for: address)
      }
    }
  }

  private func addressMenu(for addressString: String) -> some View {
    Menu(
      content: {
        Text(addressString.zwspOutput)
        Button {
          UIPasteboard.general.string = addressString
        } label: {
          Label(
            Strings.Wallet.copyAddressButtonTitle,
            qoraiSystemImage: "qora.copy.plain-text"
          )
        }
      },
      label: {
        Image(qoraiSystemName: "qora.more.horizontal")
          .padding(6)
          .clipShape(Rectangle())
      }
    )
  }
}
