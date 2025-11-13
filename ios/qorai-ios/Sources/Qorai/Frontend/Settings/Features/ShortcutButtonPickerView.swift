// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiStrings
import QoraiWidgetsModels
import DesignSystem
import Preferences
import Strings
import SwiftUI

struct ShortcutButtonPickerView: View {
  @ObservedObject private var selectedShortcut = Preferences.General.toolbarShortcutButton
  @Environment(\.dismiss) var dismiss

  var body: some View {
    Form {
      Picker("", selection: $selectedShortcut.value) {
        Label(Strings.ShortcutButton.hideButtonTitle, qoraiSystemImage: "qora.eye.off")
          .tag(Int?.none)
        ForEach(WidgetShortcut.eligibleButtonShortcuts, id: \.self) { shortcut in
          Label(shortcut.displayString, qoraiSystemImage: shortcut.qoraiSystemImageName ?? "")
            .tag(Int?.some(shortcut.rawValue))
        }
      }
      .pickerStyle(.inline)
      .tint(Color(qoraiSystemName: .iconDefault))
      .foregroundStyle(Color(qoraiSystemName: .textPrimary))
      .listRowBackground(Color(uiColor: .secondaryQoraiGroupedBackground))
    }
    .onChange(of: selectedShortcut.value) { newValue in
      dismiss()
    }
    .navigationTitle(Strings.ShortcutButton.shortcutButtonTitle)
    .scrollContentBackground(.hidden)
    .background(Color(uiColor: .qoraiGroupedBackground))
  }
}
